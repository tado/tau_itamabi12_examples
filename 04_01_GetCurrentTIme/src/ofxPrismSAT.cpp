/**
***     ARTSAT Project
***
***     Copyright (C) 2011 - 2011 HORIGUCHI Junshi.
***     Version    openFrameworks
***     Homepage   http://iridium.jp/
***     E-mail     zap00365@nifty.com
***
***     This source code is for Xcode.
***     Xcode 4.0 (LLVM compiler 2.0)
***
***     ofxPrismSAT.cpp
**/

#include "ofxPrismSAT.h"
#include "ofxXmlSettings.h"
#include "ofxPrismSAT_table.hpp"

#define SAT_ID                  ("norad://33493")
#define URL_SCHEDULE            ("http://www.space.t.u-tokyo.ac.jp/gs/schedule.aspx?sat=PRISM&date=")
#define URL_DATA                ("http://www.space.t.u-tokyo.ac.jp/gs/report.aspx?id=")
#define URL_TIME                ("%YYYY%MM%DD")
#define TABLE_SCHEDULE          ("_schedule_")
#define TABLE_DATA              ("_data_")
#define PARSE_SCHEDULE          ("%YYYY/%M/%D %h:%mm:%ss")
#define PARSE_AOSLOS            ("%YYYY/%M/%Dnbsp;nbsp;%h:%mm:%ss")
#define PARSE_RTC               ("%YYYY/%MM/%DD %hh:%mm:%ss")
#define MARKER_AOS              ("AOS")
#define MARKER_LOS              ("LOS")
#define PARAMETER_ID            ("?id=")

/*public */ofxPrismSAT::ofxPrismSAT(void)
{
    SetID(SAT_ID);
}

/*public virtual */ofxPrismSAT::~ofxPrismSAT(void)
{
    CloseSQL();
}

/*public virtual */ ofxSATError ofxPrismSAT::GetTLE(TLERec* result) const
{
    ofxSQLiteSelect select(NULL);
    ofxSATError error(SATERROR_OK);
    
    if ((error = PrepareSQL()) == SATERROR_OK) {
        if (result != NULL) {
            select = GetSQL()->select("tle1,tle2").from(TABLE_SCHEDULE).order("date", "desc").execute();
            if (select.begin().hasNext()) {
                strlcpy(result->line[0], select.getString(0).c_str(), sizeof(result->line[0]));
                strlcpy(result->line[1], select.getString(1).c_str(), sizeof(result->line[1]));
            }
            else {
                error = SATERROR_NO_RESULT;
            }
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    return error;
}

/*public virtual */ ofxSATError ofxPrismSAT::GetTLETime(ofxSATTime* result) const
{
    ofxSQLiteSelect select(NULL);
    ofxSATError error(SATERROR_OK);
    
    if ((error = PrepareSQL()) == SATERROR_OK) {
        if (result != NULL) {
            select = GetSQL()->select("date").from(TABLE_SCHEDULE).order("date", "desc").execute();
            if (select.begin().hasNext()) {
                error = result->Parse(SQL_TIME, select.getString());
            }
            else {
                error = SATERROR_NO_RESULT;
            }
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    return error;
}

/*public virtual */ofxSATError ofxPrismSAT::GetAvailableTime(std::vector<ofxSATTime>* result) const
{
    ofxSQLiteSelect select(NULL);
    TableRec const* table;
    std::vector<ofxSATTime> cache;
    ofxSATTime time;
    ofxSATError error(SATERROR_OK);
    
    if ((error = PrepareSQL()) == SATERROR_OK) {
        if (result != NULL) {
            if ((table = GetTableBySensor(SENSOR_TIME_RTC)) != NULL) {
                select = GetSQL()->select(table->sql).from(TABLE_DATA).order(table->sql, "asc").execute();
                for (select.begin(); select.hasNext(); select.next()) {
                    if ((error = DecodeData(select, table->format, &time, sizeof(time))) == SATERROR_OK) {
                        cache.push_back(time);
                    }
                    else {
                        break;
                    }
                }
                if (error == SATERROR_OK) {
                    *result = cache;
                }
            }
            else {
                error = SATERROR_FAILED;
            }
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    return error;
}

/*public virtual */ofxPrismSAT::FormatEnum ofxPrismSAT::GetSensorFormat(SensorType sensor) const
{
    TableRec const* table;
    FormatEnum result(FORMAT_LIMIT);
    
    if ((table = GetTableBySensor(sensor)) != NULL) {
        result = table->format;
    }
    return result;
}

/*public virtual */ofxPrismSAT::UnitEnum ofxPrismSAT::GetSensorUnit(SensorType sensor) const
{
    TableRec const* table;
    UnitEnum result(UNIT_LIMIT);
    
    if ((table = GetTableBySensor(sensor)) != NULL) {
        result = table->unit;
    }
    return result;
}

/*public virtual */ofxSATError ofxPrismSAT::GetSensorData(SensorType sensor, ofxSATTime const& time, void* result, int size, bool* simulation) const
{
    ofxSQLiteSelect select(NULL);
    TableRec const* table;
    TableRec const* target;
    ofxSATError error(SATERROR_OK);
    
    if ((error = PrepareSQL()) == SATERROR_OK) {
        if ((table = GetTableBySensor(SENSOR_TIME_RTC)) != NULL) {
            if ((target = GetTableBySensor(sensor)) != NULL) {
                select = GetSQL()->select(target->sql).from(TABLE_DATA).where(table->sql, time.Format(SQL_TIME)).execute();
                if (select.begin().hasNext()) {
                    if (result != NULL) {
                        error = DecodeData(select, target->format, result, size);
                    }
                    if (error == SATERROR_OK) {
                        if (simulation != NULL) {
                            *simulation = false;
                        }
                    }
                }
                else if ((error = DownloadSchedule(time)) == SATERROR_OK) {
                    select = GetSQL()->select(target->sql).from(TABLE_DATA).where(table->sql, time.Format(SQL_TIME)).execute();
                    if (select.begin().hasNext()) {
                        if (result != NULL) {
                            error = DecodeData(select, target->format, result, size);
                        }
                        if (error == SATERROR_OK) {
                            if (simulation != NULL) {
                                *simulation = false;
                            }
                        }
                    }
                    else {
                        error = SATERROR_NO_RESULT;
                    }
                }
            }
            else {
                error = SATERROR_FAILED;
            }
        }
        else {
            error = SATERROR_FAILED;
        }
    }
    return error;
}

/*private */ofxSATError ofxPrismSAT::PrepareSQL(void) const
{
    std::string query;
    TableRec const* table;
    SensorType sensor;
    ofxSATError error(SATERROR_OK);
    
    if ((error = OpenSQL()) == SATERROR_OK) {
        query = SQL_TABLE_BEGIN(TABLE_SCHEDULE);
        query += SQL_PRIMARY_KEY;
        query += ", date TEXT";
        query += ", id TEXT";
        query += ", tle1 TEXT";
        query += ", tle2 TEXT";
        query += SQL_TABLE_END;
        if (GetSQL()->simpleQuery(query.c_str()) == SQLITE_OK) {
            query = SQL_TABLE_BEGIN(TABLE_DATA);
            query += SQL_PRIMARY_KEY;
            query += ", id TEXT";
            for (sensor = 0; sensor < SENSOR_LIMIT && error == SATERROR_OK; ++sensor) {
                if ((table = GetTableBySensor(sensor)) != NULL) {
                    query += ", ";
                    query += table->sql;
                    query += " ";
                    switch (table->format) {
                        case FORMAT_BOOL:
                        case FORMAT_INT:
                            query += "INTEGER";
                            break;
                        case FORMAT_DOUBLE:
                            query += "REAL";
                            break;
                        case FORMAT_STRING:
                        case FORMAT_OFXSATTIME:
                            query += "TEXT";
                            break;
                        default:
                            error = SATERROR_FAILED;
                            break;
                    }
                }
                else {
                    error = SATERROR_FAILED;
                }
            }
            if (error == SATERROR_OK) {
                query += SQL_TABLE_END;
                if (GetSQL()->simpleQuery(query.c_str()) != SQLITE_OK) {
                    error = SATERROR_FAILED;
                }
            }
        }
        else {
            error = SATERROR_FAILED;
        }
        if (error != SATERROR_OK) {
            CloseSQL();
        }
    }
    return error;
}

/*private static */ofxSATError ofxPrismSAT::DecodeData(ofxSQLiteSelect& select, FormatEnum format, void* result, int size)
{
    ofxSATTime time;
    ofxSATError error(SATERROR_OK);
    
    if (result != NULL) {
        if (select.hasNext()) {
            switch (format) {
                case FORMAT_BOOL:
                    if (size >= sizeof(bool)) {
                        *static_cast<bool*>(result) = select.getInt();
                    }
                    else {
                        error = SATERROR_INVALID_PARAM;
                    }
                    break;
                case FORMAT_INT:
                    if (size >= sizeof(int)) {
                        *static_cast<int*>(result) = select.getInt();
                    }
                    else {
                        error = SATERROR_INVALID_PARAM;
                    }
                    break;
                case FORMAT_DOUBLE:
                    if (size >= sizeof(double)) {
                        *static_cast<double*>(result) = select.getFloat();
                    }
                    else {
                        error = SATERROR_INVALID_PARAM;
                    }
                    break;
                case FORMAT_STRING:
                    if (size >= sizeof(std::string)) {
                        *static_cast<std::string*>(result) = select.getString();
                    }
                    else {
                        error = SATERROR_INVALID_PARAM;
                    }
                    break;
                case FORMAT_OFXSATTIME:
                    if (size >= sizeof(ofxSATTime)) {
                        if ((error = time.Parse(SQL_TIME, select.getString())) == SATERROR_OK) {
                            *static_cast<ofxSATTime*>(result) = time;
                        }
                    }
                    else {
                        error = SATERROR_INVALID_PARAM;
                    }
                    break;
                default:
                    error = SATERROR_INVALID_PARAM;
                    break;
            }
        }
        else {
            error = SATERROR_INVALID_STATE;
        }
    }
    else {
        error = SATERROR_INVALID_PARAM;
    }
    return error;
}

/*private */ofxSATError ofxPrismSAT::DownloadSchedule(ofxSATTime const& time) const
{
    ofHttpResponse response;
    TLERec tle;
    std::vector<ScheduleRec> schedule;
    int i;
    ofxSATError error(SATERROR_OK);
    
    response = ofLoadURL(URL_SCHEDULE + time.Format(URL_TIME));
    switch (response.status) {
        case 200:
            if ((error = ParseSchedule(response.data, &tle, &schedule)) == SATERROR_OK) {
                if ((error = RecordSchedule(tle, schedule, GetSQL())) == SATERROR_OK) {
                    for (i = 0; i < schedule.size(); ++i) {
                        if ((error = DownloadData(schedule[i].id)) == SATERROR_INVALID_FORMAT) {
                            error = SATERROR_OK;
                        }
                        else if (error != SATERROR_OK) {
                            break;
                        }
                    }
                }
            }
            break;
        default:
            ofLog(OF_LOG_ERROR) << "ofxPrismSAT::DownloadSchedule [" << response.status << " : " << response.error << "]";
            break;
    }
    return error;
}

/*private */ofxSATError ofxPrismSAT::DownloadData(std::string const& id) const
{
    ofxSQLiteSelect select(NULL);
    ofHttpResponse response;
    std::vector<std::string> data;
    ofxSATError error(SATERROR_OK);
    
    select = GetSQL()->select("id").from(TABLE_DATA).where("id", id).execute();
    if (!select.begin().hasNext()) {
        response = ofLoadURL(URL_DATA + id);
        switch (response.status) {
            case 200:
                if ((error = ParseData(response.data, &data)) == SATERROR_OK) {
                    error = RecordData(id, data, GetSQL());
                }
                break;
            default:
                ofLog(OF_LOG_ERROR) << "ofxPrismSAT::DownloadData [" << response.status << " : " << response.error << "]";
                break;
        }
    }
    return error;
}

/*private static */ofxSATError ofxPrismSAT::ParseSchedule(std::string const& buffer, TLERec* tle, std::vector<ScheduleRec>* schedule)
{
    ofxXmlSettings xml;
    std::string line;
    std::string date;
    std::string time;
    std::vector<ScheduleRec> cache;
    ScheduleRec temp;
    int count;
    int i;
    ofxSATError error(SATERROR_OK);
    
    if (tle != NULL && schedule != NULL) {
        if (xml.loadFromBuffer(buffer)) {
            if (xml.pushTag("html")) {
                if (xml.pushTag("body")) {
                    if (xml.pushTag("form")) {
                        if (xml.pushTag("table")) {
                            if (xml.pushTag("tr", 1)) {
                                if (xml.pushTag("td")) {
                                    if (xml.pushTag("table")) {
                                        if (xml.pushTag("tr")) {
                                            if (xml.pushTag("td")) {
                                                if (xml.pushTag("div")) {
                                                    /////////////////////////
                                                    //// begin of parser ////
                                                    if (xml.pushTag("table", 0)) {
                                                        if (xml.pushTag("tr", 2)) {
                                                            if (xml.pushTag("td")) {
                                                                line = xml.getValue("pre", "");
                                                                xml.popTag();
                                                            }
                                                            else {
                                                                error = SATERROR_INVALID_FORMAT;
                                                            }
                                                            xml.popTag();
                                                        }
                                                        else {
                                                            error = SATERROR_INVALID_FORMAT;
                                                        }
                                                        xml.popTag();
                                                    }
                                                    else {
                                                        error = SATERROR_INVALID_FORMAT;
                                                    }
                                                    if (error == SATERROR_OK) {
                                                        if (!line.empty()) {
                                                            if (xml.pushTag("table", 1)) {
                                                                if (xml.pushTag("tr", 1)) {
                                                                    if (xml.pushTag("td")) {
                                                                        if (xml.pushTag("table")) {
                                                                            count = xml.getNumTags("tr") - 3;
                                                                            for (i = 0; i < count && error == SATERROR_OK; ++i) {
                                                                                if (xml.pushTag("tr", i + 2)) {
                                                                                    if (xml.attributeExists("td", "rowspan", 0)) {
                                                                                        if (xml.pushTag("td", 0)) {
                                                                                            if (xml.pushTag("font")) {
                                                                                                if (xml.tagExists("b")) {
                                                                                                    date = Trim(xml.getValue("b", ""));
                                                                                                    xml.popTag();
                                                                                                }
                                                                                                else {
                                                                                                    xml.popTag();
                                                                                                    date = Trim(xml.getValue("font", ""));
                                                                                                }
                                                                                            }
                                                                                            else {
                                                                                                error = SATERROR_INVALID_FORMAT;
                                                                                            }
                                                                                            xml.popTag();
                                                                                        }
                                                                                        else {
                                                                                            error = SATERROR_INVALID_FORMAT;
                                                                                        }
                                                                                        if (error == SATERROR_OK) {
                                                                                            if (xml.pushTag("td", 1)) {
                                                                                                time = Trim(xml.getValue("font", ""));
                                                                                                xml.popTag();
                                                                                            }
                                                                                            else {
                                                                                                error = SATERROR_INVALID_FORMAT;
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    else if (xml.pushTag("td", 0)) {
                                                                                        time = Trim(xml.getValue("font", ""));
                                                                                        xml.popTag();
                                                                                    }
                                                                                    else {
                                                                                        error = SATERROR_INVALID_FORMAT;
                                                                                    }
                                                                                    if (error == SATERROR_OK) {
                                                                                        if (!date.empty() && !time.empty()) {
                                                                                            if (xml.pushTag("td", xml.getNumTags("td") - 1)) {
                                                                                                if (xml.pushTag("font")) {
                                                                                                    temp.id = xml.getAttribute("a", "href", "");
                                                                                                    if (!temp.id.empty()) {
                                                                                                        temp.date = date + " " + time;
                                                                                                        cache.push_back(temp);
                                                                                                    }
                                                                                                    xml.popTag();
                                                                                                }
                                                                                                else {
                                                                                                    error = SATERROR_INVALID_FORMAT;
                                                                                                }
                                                                                                xml.popTag();
                                                                                            }
                                                                                            else {
                                                                                                error = SATERROR_INVALID_FORMAT;
                                                                                            }
                                                                                        }
                                                                                        else {
                                                                                            error = SATERROR_INVALID_FORMAT;
                                                                                        }
                                                                                    }
                                                                                    xml.popTag();
                                                                                }
                                                                                else {
                                                                                    error = SATERROR_INVALID_FORMAT;
                                                                                }
                                                                            }
                                                                            if (error == SATERROR_OK) {
                                                                                if ((error = NormalizeSchedule(line, tle, &cache)) == SATERROR_OK) {
                                                                                    *schedule = cache;
                                                                                }
                                                                            }
                                                                            xml.popTag();
                                                                        }
                                                                        else {
                                                                            error = SATERROR_INVALID_FORMAT;
                                                                        }
                                                                        xml.popTag();
                                                                    }
                                                                    else {
                                                                        error = SATERROR_INVALID_FORMAT;
                                                                    }
                                                                    xml.popTag();
                                                                }
                                                                else {
                                                                    error = SATERROR_INVALID_FORMAT;
                                                                }
                                                                xml.popTag();
                                                            }
                                                            else {
                                                                error = SATERROR_INVALID_FORMAT;
                                                            }
                                                        }
                                                        else {
                                                            error = SATERROR_INVALID_FORMAT;
                                                        }
                                                    }
                                                    //// end of parser /////
                                                    ////////////////////////
                                                    xml.popTag();
                                                }
                                                else {
                                                    error = SATERROR_INVALID_FORMAT;
                                                }
                                                xml.popTag();
                                            }
                                            else {
                                                error = SATERROR_INVALID_FORMAT;
                                            }
                                            xml.popTag();
                                        }
                                        else {
                                            error = SATERROR_INVALID_FORMAT;
                                        }
                                        xml.popTag();
                                    }
                                    else {
                                        error = SATERROR_INVALID_FORMAT;
                                    }
                                    xml.popTag();
                                }
                                else {
                                    error = SATERROR_INVALID_FORMAT;
                                }
                                xml.popTag();
                            }
                            else {
                                error = SATERROR_INVALID_FORMAT;
                            }
                            xml.popTag();
                        }
                        else {
                            error = SATERROR_INVALID_FORMAT;
                        }
                        xml.popTag();
                    }
                    else {
                        error = SATERROR_INVALID_FORMAT;
                    }
                    xml.popTag();
                }
                else {
                    error = SATERROR_INVALID_FORMAT;
                }
                xml.popTag();
            }
            else {
                error = SATERROR_INVALID_FORMAT;
            }
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    else {
        error = SATERROR_INVALID_PARAM;
    }
    return error;
}

/*private static */ofxSATError ofxPrismSAT::ParseData(std::string const& buffer, std::vector<std::string>* data)
{
    ofxXmlSettings xml;
    std::string aos;
    std::string los;
    std::string rtc;
    ofxSATTime atime;
    ofxSATTime ltime;
    ofxSATTime rtime;
    std::vector<std::string> cache(SENSOR_LIMIT);
    SensorType sensor;
    int count;
    int i;
    ofxSATError error(SATERROR_OK);
    
    if (data != NULL) {
        if (xml.loadFromBuffer(buffer)) {
            if (xml.pushTag("html")) {
                if (xml.pushTag("body")) {
                    if (xml.pushTag("form")) {
                        if (xml.pushTag("table")) {
                            if (xml.pushTag("tr", 1)) {
                                if (xml.pushTag("td")) {
                                    if (xml.pushTag("table")) {
                                        if (xml.pushTag("tr")) {
                                            if (xml.pushTag("td")) {
                                                if (xml.pushTag("div")) {
                                                    /////////////////////////
                                                    //// begin of parser ////
                                                    if (xml.pushTag("table", 0)) {
                                                        if (xml.pushTag("tr", 2)) {
                                                            if (xml.getValue("td", "", 0) == MARKER_AOS) {
                                                                aos = xml.getValue("td", "", 1);
                                                            }
                                                            if (xml.getValue("td", "", 2) == MARKER_LOS) {
                                                                los = xml.getValue("td", "", 3);
                                                            }
                                                            xml.popTag();
                                                        }
                                                        else {
                                                            error = SATERROR_INVALID_FORMAT;
                                                        }
                                                        xml.popTag();
                                                    }
                                                    else {
                                                        error = SATERROR_INVALID_FORMAT;
                                                    }
                                                    if (error == SATERROR_OK) {
                                                        if (!aos.empty() && !los.empty()) {
                                                            if ((error = atime.Parse(PARSE_AOSLOS, aos)) == SATERROR_OK) {
                                                                if ((error = ltime.Parse(PARSE_AOSLOS, los)) == SATERROR_OK) {
                                                                    if (xml.pushTag("table", 2)) {
                                                                        if (xml.pushTag("tr", 1)) {
                                                                            if (xml.pushTag("td")) {
                                                                                if (xml.pushTag("table")) {
                                                                                    count = xml.getNumTags("tr");
                                                                                    for (i = 0; i < count && error == SATERROR_OK; ++i) {
                                                                                        if (xml.pushTag("tr", i)) {
                                                                                            if ((sensor = GetSensorByTag(xml.getValue("td", "", 0))) >= 0) {
                                                                                                if (xml.pushTag("td", 1)) {
                                                                                                    if (xml.tagExists("font")) {
                                                                                                        cache[sensor] = xml.getValue("font", "");
                                                                                                        xml.popTag();
                                                                                                    }
                                                                                                    else {
                                                                                                        xml.popTag();
                                                                                                        cache[sensor] = xml.getValue("td", "", 1);
                                                                                                    }
                                                                                                }
                                                                                                else {
                                                                                                    error = SATERROR_INVALID_FORMAT;
                                                                                                }
                                                                                            }
                                                                                            if (error == SATERROR_OK) {
                                                                                                if ((sensor = GetSensorByTag(xml.getValue("td", "", 2))) >= 0) {
                                                                                                    if (xml.pushTag("td", 3)) {
                                                                                                        if (xml.tagExists("font")) {
                                                                                                            cache[sensor] = xml.getValue("font", "");
                                                                                                            xml.popTag();
                                                                                                        }
                                                                                                        else {
                                                                                                            xml.popTag();
                                                                                                            cache[sensor] = xml.getValue("td", "", 3);
                                                                                                        }
                                                                                                    }
                                                                                                    else {
                                                                                                        error = SATERROR_INVALID_FORMAT;
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                            xml.popTag();
                                                                                        }
                                                                                        else {
                                                                                            error = SATERROR_INVALID_FORMAT;
                                                                                        }
                                                                                    }
                                                                                    if (error == SATERROR_OK) {
                                                                                        rtc = cache[SENSOR_TIME_RTC];
                                                                                        if (!rtc.empty()) {
                                                                                            if ((error = rtime.Parse(PARSE_RTC, rtc)) == SATERROR_OK) {
                                                                                                if (atime <= rtime && rtime <= ltime) {
                                                                                                    if ((error = NormalizeData(&cache)) == SATERROR_OK) {
                                                                                                        *data = cache;
                                                                                                    }
                                                                                                }
                                                                                                else {
                                                                                                    error = SATERROR_INVALID_FORMAT;
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                        else {
                                                                                            error = SATERROR_INVALID_FORMAT;
                                                                                        }
                                                                                    }
                                                                                    xml.popTag();
                                                                                }
                                                                                else {
                                                                                    error = SATERROR_INVALID_FORMAT;
                                                                                }
                                                                                xml.popTag();
                                                                            }
                                                                            else {
                                                                                error = SATERROR_INVALID_FORMAT;
                                                                            }
                                                                            xml.popTag();
                                                                        }
                                                                        else {
                                                                            error = SATERROR_INVALID_FORMAT;
                                                                        }
                                                                        xml.popTag();
                                                                    }
                                                                    else {
                                                                        error = SATERROR_INVALID_FORMAT;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                        else {
                                                            error = SATERROR_INVALID_FORMAT;
                                                        }
                                                    }
                                                    //// end of parser /////
                                                    ////////////////////////
                                                    xml.popTag();
                                                }
                                                else {
                                                    error = SATERROR_INVALID_FORMAT;
                                                }
                                                xml.popTag();
                                            }
                                            else {
                                                error = SATERROR_INVALID_FORMAT;
                                            }
                                            xml.popTag();
                                        }
                                        else {
                                            error = SATERROR_INVALID_FORMAT;
                                        }
                                        xml.popTag();
                                    }
                                    else {
                                        error = SATERROR_INVALID_FORMAT;
                                    }
                                    xml.popTag();
                                }
                                else {
                                    error = SATERROR_INVALID_FORMAT;
                                }
                                xml.popTag();
                            }
                            else {
                                error = SATERROR_INVALID_FORMAT;
                            }
                            xml.popTag();
                        }
                        else {
                            error = SATERROR_INVALID_FORMAT;
                        }
                        xml.popTag();
                    }
                    else {
                        error = SATERROR_INVALID_FORMAT;
                    }
                    xml.popTag();
                }
                else {
                    error = SATERROR_INVALID_FORMAT;
                }
                xml.popTag();
            }
            else {
                error = SATERROR_INVALID_FORMAT;
            }
        }
        else {
            error = SATERROR_INVALID_PARAM;
        }
    }
    else {
        error = SATERROR_INVALID_PARAM;
    }
    return error;
}

/*private static */ofxSATError ofxPrismSAT::RecordSchedule(TLERec const& tle, std::vector<ScheduleRec> const& schedule, ofxSQLite* sql)
{
    ofxSQLiteSelect select(NULL);
    ofxSQLiteUpdate update(NULL, "");
    ofxSQLiteInsert insert(NULL, "");
    int i;
    ofxSATError error(SATERROR_OK);
    
    if (sql != NULL) {
        for (i = 0; i < schedule.size() && error == SATERROR_OK; ++i) {
            select = sql->select("date").from(TABLE_SCHEDULE).where("date", schedule[i].date).execute();
            if (select.begin().hasNext()) {
                update = sql->update(TABLE_SCHEDULE).where("date", schedule[i].date);
                update.use("date", schedule[i].date);
                update.use("id", schedule[i].id);
                update.use("tle1", tle.line[0]);
                update.use("tle2", tle.line[1]);
                if (update.execute() != SQLITE_OK) {
                    error = SATERROR_FAILED;
                }
            }
            else {
                insert = sql->insert(TABLE_SCHEDULE);
                insert.use("date", schedule[i].date);
                insert.use("id", schedule[i].id);
                insert.use("tle1", tle.line[0]);
                insert.use("tle2", tle.line[1]);
                if (insert.execute() != SQLITE_OK) {
                    error = SATERROR_FAILED;
                }
            }
        }
    }
    else {
        error = SATERROR_INVALID_PARAM;
    }
    return error;
}

/*private static */ofxSATError ofxPrismSAT::RecordData(std::string const& id, std::vector<std::string> const& data, ofxSQLite* sql)
{
    ofxSQLiteSelect select(NULL);
    ofxSQLiteUpdate update(NULL, "");
    ofxSQLiteInsert insert(NULL, "");
    TableRec const* table;
    SensorType sensor;
    ofxSATError error(SATERROR_OK);
    
    if (sql != NULL) {
        if (data.size() == SENSOR_LIMIT) {
            if ((table = GetTableBySensor(SENSOR_TIME_RTC)) != NULL) {
                select = sql->select(table->sql).from(TABLE_DATA).where(table->sql, data[SENSOR_TIME_RTC]).execute();
                if (select.begin().hasNext()) {
                    update = sql->update(TABLE_DATA).where(table->sql, data[SENSOR_TIME_RTC]);
                    update.use("id", id);
                    for (sensor = 0; sensor < SENSOR_LIMIT && error == SATERROR_OK; ++sensor) {
                        if ((table = GetTableBySensor(sensor)) != NULL) {
                            switch (table->format) {
                                case FORMAT_BOOL:
                                case FORMAT_INT:
                                    update.use(table->sql, static_cast<int>(strtol(data[sensor].c_str(), NULL, 0)));
                                    break;
                                case FORMAT_DOUBLE:
                                    update.use(table->sql, static_cast<double>(strtod(data[sensor].c_str(), NULL)));
                                    break;
                                case FORMAT_STRING:
                                case FORMAT_OFXSATTIME:
                                    update.use(table->sql, data[sensor]);
                                    break;
                                default:
                                    error = SATERROR_FAILED;
                                    break;
                            }
                        }
                        else {
                            error = SATERROR_FAILED;
                        }
                    }
                    if (error == SATERROR_OK) {
                        if (update.execute() != SQLITE_OK) {
                            error = SATERROR_FAILED;
                        }
                    }
                }
                else {
                    insert = sql->insert(TABLE_DATA);
                    insert.use("id", id);
                    for (sensor = 0; sensor < SENSOR_LIMIT && error == SATERROR_OK; ++sensor) {
                        if ((table = GetTableBySensor(sensor)) != NULL) {
                            switch (table->format) {
                                case FORMAT_BOOL:
                                case FORMAT_INT:
                                    insert.use(table->sql, static_cast<int>(strtol(data[sensor].c_str(), NULL, 0)));
                                    break;
                                case FORMAT_DOUBLE:
                                    insert.use(table->sql, static_cast<double>(strtod(data[sensor].c_str(), NULL)));
                                    break;
                                case FORMAT_STRING:
                                case FORMAT_OFXSATTIME:
                                    insert.use(table->sql, data[sensor]);
                                    break;
                                default:
                                    error = SATERROR_FAILED;
                                    break;
                            }
                        }
                        else {
                            error = SATERROR_FAILED;
                        }
                    }
                    if (error == SATERROR_OK) {
                        if (insert.execute() != SQLITE_OK) {
                            error = SATERROR_FAILED;
                        }
                    }
                }
            }
            else {
                error = SATERROR_FAILED;
            }
        }
        else {
            error = SATERROR_INVALID_STATE;
        }
    }
    else {
        error = SATERROR_INVALID_PARAM;
    }
    return error;
}

/*private static */ofxSATError ofxPrismSAT::NormalizeSchedule(std::string const& line, TLERec* tle, std::vector<ScheduleRec>* schedule)
{
    ofxSATTime time;
    char one[9][32];
    char two[8][32];
    TLERec temp;
    int index;
    int i;
    ofxSATError error(SATERROR_OK);
    
    if (tle != NULL && schedule != NULL) {
        for (i = 0; i < schedule->size() && error == SATERROR_OK; ++i) {
            if ((error = time.Parse(PARSE_SCHEDULE, (*schedule)[i].date)) == SATERROR_OK) {
                if ((index = (*schedule)[i].id.find(PARAMETER_ID)) != std::string::npos) {
                    (*schedule)[i].date = time.Format(SQL_TIME);
                    (*schedule)[i].id = (*schedule)[i].id.substr(index + asciiesof(PARAMETER_ID));
                }
                else {
                    error = SATERROR_INVALID_FORMAT;
                }
            }
        }
        if (error == SATERROR_OK) {
            if (sscanf(line.c_str(), "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
                &one[0], &one[1], &one[2], &one[3],
                &one[4], &one[5], &one[6], &one[7],
                &one[8],
                &two[0], &two[1], &two[2], &two[3],
                &two[4], &two[5], &two[6], &two[7]) == lengthof(one) + lengthof(two)) {
                if (snprintf(temp.line[0], sizeof(temp.line[0]), "%1s %-6s %-8s %14s %10s %8s %8s %1s %5s", one[0], one[1], one[2], one[3], one[4], one[5], one[6], one[7], one[8]) == asciiesof(temp.line[0])) {
                    if (snprintf(temp.line[1], sizeof(temp.line[1]), "%1s %5s %8s %8s %7s %8s %8s %17s", two[0], two[1], two[2], two[3], two[4], two[5], two[6], two[7]) == asciiesof(temp.line[1])) {
                        *tle = temp;
                    }
                    else {
                        error = SATERROR_INVALID_FORMAT;
                    }
                }
                else {
                    error = SATERROR_INVALID_FORMAT;
                }
            }
            else {
                error = SATERROR_INVALID_FORMAT;
            }
        }
    }
    else {
        error = SATERROR_INVALID_PARAM;
    }
    return error;
}

/*private static */ofxSATError ofxPrismSAT::NormalizeData(std::vector<std::string>* data)
{
    TableRec const* table;
    SensorType sensor;
    ofxSATTime time;
    ofxSATError error(SATERROR_OK);
    
    if (data != NULL) {
        for (sensor = 0; sensor < data->size() && error == SATERROR_OK; ++sensor) {
            if ((table = GetTableBySensor(sensor)) != NULL) {
                switch (table->format) {
                    case FORMAT_BOOL:
                        if ((*data)[sensor] == table->boolHint.no) {
                            (*data)[sensor] = "0";
                        }
                        else if ((*data)[sensor] == table->boolHint.yes) {
                            (*data)[sensor] = "1";
                        }
                        else if ((*data)[sensor] == "-") {
                            (*data)[sensor] = "0";
                        }
                        else {
                            error = SATERROR_INVALID_FORMAT;
                        }
                        break;
                    case FORMAT_INT:
                    case FORMAT_DOUBLE:
                        (*data)[sensor] = Trim((*data)[sensor]);
                        break;
                    case FORMAT_OFXSATTIME:
                        if ((error = time.Parse(table->ofxSATTimeHint.format, (*data)[sensor])) == SATERROR_OK) {
                            (*data)[sensor] = time.Format(SQL_TIME);
                        }
                        break;
                    default:
                        break;
                }
            }
            else {
                error = SATERROR_FAILED;
            }
        }
    }
    else {
        error = SATERROR_INVALID_PARAM;
    }
    return error;
}
