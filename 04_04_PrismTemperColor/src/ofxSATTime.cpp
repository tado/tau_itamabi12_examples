/**
***     ARTSAT Project
***
***     Copyright (C) 2011 - 2011 HORIGUCHI Junshi.
***     Version openFrameworks
***     Homepage    http://iridium.jp/
***     E-mail      zap00365@nifty.com
***
***     This source code is for Xcode.
***     Xcode 4.0 (LLVM compiler 2.0)
***
***     ofxSATTime.cpp
**/

#include "ofxSATTime.h"

static  char const              ofxsattime_month[][13][10] = {
    {"MONTH", "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"},
    {"Month", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"},
    {"month", "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"}
};
static  char const              ofxsattime_mth[][13][4] = {
    {"MTH", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"},
    {"Mth", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"},
    {"mth", "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"}
};
static  char const              ofxsattime_week[][8][10] = {
    {"WEEK", "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"},
    {"Week", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"},
    {"week", "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"}
};
static  char const              ofxsattime_wek[][8][4] = {
    {"WEK", "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"},
    {"Wek", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"},
    {"wek", "sun", "mon", "tue", "wed", "thu", "fri", "sat"}
};
static  char const              ofxsattime_youbi[][8][4] = {
    {"y", "日", "月", "火", "水", "木", "金", "土"}
};
static  char const              ofxsattime_ampm[][3][5] = {
    {"AN", "AM", "PM"},
    {"an", "am", "pm"},
    {"AD", "A.M.", "P.M."},
    {"ad", "a.m.", "p.m."}
};
static  char const              ofxsattime_gozengogo[][3][7] = {
    {"g", "午前", "午後"}
};
static  char const              ofxsattime_format[][5] = {
    "%d", "%02d", "%04d"
};

/*public */ofxSATTime& ofxSATTime::Set(ofxSATTime const& param)
{
    _year = param._year;
    _month = param._month;
    _day = param._day;
    _hour = param._hour;
    _minute = param._minute;
    _second = param._second;
    _week = param._week;
    return *this;
}

/*public */ofxSATTime& ofxSATTime::Set(int year, int month, int day, int hour, int minute, int second)
{
    From(year, month, day, hour, minute, second, false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::Set(int year, int month, int day)
{
    From(year, month, day, 0, 0, 0, false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::Set(time_t param)
{
    From(param);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::SetDate(int year, int month, int day)
{
    From(year, month, day, _hour, _minute, _second, false);
    return *this;
}

/*public */void ofxSATTime::GetDate(int* year, int* month, int* day, DayOfWeekEnum* week) const
{
    if (year != NULL) {
        *year = _year;
    }
    if (month != NULL) {
        *month = _month;
    }
    if (day != NULL) {
        *day = _day;
    }
    if (week != NULL) {
        *week = _week;
    }
    return;
}

/*public */ofxSATTime& ofxSATTime::SetTime(int hour, int minute, int second)
{
    From(_year, _month, _day, hour, minute, second, false);
    return *this;
}

/*public */void ofxSATTime::GetTime(int* hour, int* minute, int* second) const
{
    if (hour != NULL) {
        *hour = _hour;
    }
    if (minute != NULL) {
        *minute = _minute;
    }
    if (second != NULL) {
        *second = _second;
    }
    return;
}

/*public */ofxSATTime& ofxSATTime::SetYear(int param)
{
    From(param, _month, _day, _hour, _minute, _second, true);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::SetMonth(int param)
{
    From(_year, param, _day, _hour, _minute, _second, true);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::SetDay(int param)
{
    From(_year, _month, param, _hour, _minute, _second, false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::SetHour(int param)
{
    From(_year, _month, _day, param, _minute, _second, false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::SetMinute(int param)
{
    From(_year, _month, _day, _hour, param, _second, false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::SetSecond(int param)
{
    From(_year, _month, _day, _hour, _minute, param, false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::Add(ofxSATTimeDiff const& param)
{
    From(_year, _month, _day, _hour, _minute, _second + param.AsTime_t(), false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::AddYear(int param)
{
    From(_year + param, _month, _day, _hour, _minute, _second, true);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::AddMonth(int param)
{
    From(_year, _month + param, _day, _hour, _minute, _second, true);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::AddDay(int param)
{
    From(_year, _month, _day + param, _hour, _minute, _second, false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::AddHour(int param)
{
    From(_year, _month, _day, _hour + param, _minute, _second, false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::AddMinute(int param)
{
    From(_year, _month, _day, _hour, _minute + param, _second, false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::AddSecond(int param)
{
    From(_year, _month, _day, _hour, _minute, _second + param, false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::Sub(ofxSATTimeDiff const& param)
{
    From(_year, _month, _day, _hour, _minute, _second - param.AsTime_t(), false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::SubYear(int param)
{
    From(_year - param, _month, _day, _hour, _minute, _second, true);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::SubMonth(int param)
{
    From(_year, _month - param, _day, _hour, _minute, _second, true);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::SubDay(int param)
{
    From(_year, _month, _day - param, _hour, _minute, _second, false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::SubHour(int param)
{
    From(_year, _month, _day, _hour - param, _minute, _second, false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::SubMinute(int param)
{
    From(_year, _month, _day, _hour, _minute - param, _second, false);
    return *this;
}

/*public */ofxSATTime& ofxSATTime::SubSecond(int param)
{
    From(_year, _month, _day, _hour, _minute, _second - param, false);
    return *this;
}

/*public */bool ofxSATTime::Equals(ofxSATTime const& param) const
{
    return (_year == param._year &&
            _month == param._month &&
            _day == param._day &&
            _hour == param._hour &&
            _minute == param._minute &&
            _second == param._second);
}

/*public */bool ofxSATTime::EqualsDate(ofxSATTime const& param) const
{
    return (_year == param._year &&
            _month == param._month &&
            _day == param._day);
}

/*public */bool ofxSATTime::EqualsTime(ofxSATTime const& param) const
{
    return (_hour == param._hour &&
            _minute == param._minute &&
            _second == param._second);
}

/*public */int ofxSATTime::Compare(ofxSATTime const& param) const
{
    int result(0);
    
    if (_year > param._year) {
        result = +1;
    }
    else if (_year < param._year) {
        result = -1;
    }
    else if (_month > param._month) {
        result = +1;
    }
    else if (_month < param._month) {
        result = -1;
    }
    else if (_day > param._day) {
        result = +1;
    }
    else if (_day < param._day) {
        result = -1;
    }
    else if (_hour > param._hour) {
        result = +1;
    }
    else if (_hour < param._hour) {
        result = -1;
    }
    else if (_minute > param._minute) {
        result = +1;
    }
    else if (_minute < param._minute) {
        result = -1;
    }
    else if (_second > param._second) {
        result = +1;
    }
    else if (_second < param._second) {
        result = -1;
    }
    return result;
}

/*public */int ofxSATTime::CompareDate(ofxSATTime const& param) const
{
    int result(0);
    
    if (_year > param._year) {
        result = +1;
    }
    else if (_year < param._year) {
        result = -1;
    }
    else if (_month > param._month) {
        result = +1;
    }
    else if (_month < param._month) {
        result = -1;
    }
    else if (_day > param._day) {
        result = +1;
    }
    else if (_day < param._day) {
        result = -1;
    }
    return result;
}

/*public */int ofxSATTime::CompareTime(ofxSATTime const& param) const
{
    int result(0);
    
    if (_hour > param._hour) {
        result = +1;
    }
    else if (_hour < param._hour) {
        result = -1;
    }
    else if (_minute > param._minute) {
        result = +1;
    }
    else if (_minute < param._minute) {
        result = -1;
    }
    else if (_second > param._second) {
        result = +1;
    }
    else if (_second < param._second) {
        result = -1;
    }
    return result;
}

/*public */ofxSATTimeDiff ofxSATTime::Difference(ofxSATTime const& param) const
{
    return ofxSATTimeDiff(difftime(To(), param.To()));
}

/*public */ofxSATError ofxSATTime::Parse(std::string const& format, std::string const& string)
{
    char fkey;
    char skey;
    int value;
    int i;
    int j;
    int k;
    int x;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    bool ampm;
    bool ispm;
    ofxSATError error(SATERROR_OK);
    
    year = 1970;
    month = 1;
    day = 1;
    hour = 0;
    minute = 0;
    second = 0;
    ampm = false;
    ispm = false;
    for (i = 0, x = 0; i < format.size() && x < string.size() && error == SATERROR_OK; ) {
        switch (Search(format, &i, &fkey)) {
            case SEARCH_PERCENT:
                if (i < format.size()) {
                    switch (Search(format, &i, &fkey, &j)) {
                        case SEARCH_PERCENT:
                            Step(string, &x, &skey);
                            if (fkey != skey) {
                                error = SATERROR_INVALID_FORMAT;
                            }
                            break;
                        case SEARCH_MONTH:
                            for (k = 1; k < lengthof(ofxsattime_month[j]); ++k) {
                                if (Compare(string, &x, ofxsattime_month[j][k])) {
                                    month = k;
                                    break;
                                }
                            }
                            if (k >= lengthof(ofxsattime_month[j])) {
                                error = SATERROR_INVALID_FORMAT;
                            }
                            break;
                        case SEARCH_MTH:
                            for (k = 1; k < lengthof(ofxsattime_mth[j]); ++k) {
                                if (Compare(string, &x, ofxsattime_mth[j][k])) {
                                    month = k;
                                    break;
                                }
                            }
                            if (k >= lengthof(ofxsattime_mth[j])) {
                                error = SATERROR_INVALID_FORMAT;
                            }
                            break;
                        case SEARCH_WEEK:
                            for (k = 1; k < lengthof(ofxsattime_week[j]); ++k) {
                                if (Compare(string, &x, ofxsattime_week[j][k])) {
                                    break;
                                }
                            }
                            if (k >= lengthof(ofxsattime_week[j])) {
                                error = SATERROR_INVALID_FORMAT;
                            }
                            break;
                        case SEARCH_WEK:
                            for (k = 1; k < lengthof(ofxsattime_wek[j]); ++k) {
                                if (Compare(string, &x, ofxsattime_wek[j][k])) {
                                    break;
                                }
                            }
                            if (k >= lengthof(ofxsattime_wek[j])) {
                                error = SATERROR_INVALID_FORMAT;
                            }
                            break;
                        case SEARCH_YOUBI:
                            for (k = 1; k < lengthof(ofxsattime_youbi[j]); ++k) {
                                if (Compare(string, &x, ofxsattime_youbi[j][k])) {
                                    break;
                                }
                            }
                            if (k >= lengthof(ofxsattime_youbi[j])) {
                                error = SATERROR_INVALID_FORMAT;
                            }
                            break;
                        case SEARCH_AMPM:
                            for (k = 1; k < lengthof(ofxsattime_ampm[j]); ++k) {
                                if (Compare(string, &x, ofxsattime_ampm[j][k])) {
                                    ispm = (k == 2);
                                    break;
                                }
                            }
                            if (k >= lengthof(ofxsattime_ampm[j])) {
                                error = SATERROR_INVALID_FORMAT;
                            }
                            break;
                        case SEARCH_GOZENGOGO:
                            for (k = 1; k < lengthof(ofxsattime_gozengogo[j]); ++k) {
                                if (Compare(string, &x, ofxsattime_gozengogo[j][k])) {
                                    ispm = (k == 2);
                                    break;
                                }
                            }
                            if (k >= lengthof(ofxsattime_gozengogo[j])) {
                                error = SATERROR_INVALID_FORMAT;
                            }
                            break;
                        default:
                            switch (fkey) {
                                case ' ':
                                    // nop
                                    break;
                                case '*':
                                    for (k = 0; k < j && x < string.size(); ++k, ++x) {
                                        // nop
                                    }
                                    if (k < j) {
                                        error = SATERROR_INVALID_FORMAT;
                                    }
                                    break;
                                case 'Y':
                                case 'M':
                                case 'D':
                                case 'H':
                                case 'h':
                                case 'm':
                                case 's':
                                    if (j > 1) {
                                        for (k = 0; k < j && x < string.size(); ++k, ++x) {
                                            if (!isdigit(string[x])) {
                                                break;
                                            }
                                        }
                                        if (k >= j) {
                                            if (j >= 4) {
                                                k = 2;
                                            }
                                            else if (j >= 2) {
                                                k = 1;
                                            }
                                            else {
                                                k = 0;
                                            }
                                        }
                                        else {
                                            error = SATERROR_INVALID_FORMAT;
                                        }
                                    }
                                    else {
                                        for (j = 0; x < string.size(); ++x, ++j) {
                                            if (!isdigit(string[x])) {
                                                break;
                                            }
                                        }
                                        if (j > 0) {
                                            k = 0;
                                        }
                                        else {
                                            error = SATERROR_INVALID_FORMAT;
                                        }
                                    }
                                    if (error == SATERROR_OK) {
                                        if (sscanf(&string[x - j], ofxsattime_format[k], &value) > 0) {
                                            switch (fkey) {
                                                case 'Y':
                                                    if (k == 1) {
                                                        value += (value < 70) ? (2000) : (1900);
                                                    }
                                                    year = value;
                                                    break;
                                                case 'M':
                                                    month = value;
                                                    break;
                                                case 'D':
                                                    day = value;
                                                    break;
                                                case 'H':
                                                    hour = value;
                                                    ampm = true;
                                                    break;
                                                case 'h':
                                                    hour = value;
                                                    ampm = false;
                                                    break;
                                                case 'm':
                                                    minute = value;
                                                    break;
                                                case 's':
                                                    second = value;
                                                    break;
                                                default:
                                                    break;
                                            }
                                        }
                                        else {
                                            error = SATERROR_INVALID_FORMAT;
                                        }
                                    }
                                    break;
                                default:
                                    break;
                            }
                            break;
                    }
                }
                break;
            default:
                Step(string, &x, &skey);
                if (isspace(fkey) && isspace(skey)) {
                    for (j = 0; i < format.size(); ++i, ++j) {
                        if (!isspace(format[i])) {
                            break;
                        }
                    }
                    for (; x < string.size(); ++x, --j) {
                        if (!isspace(string[x])) {
                            break;
                        }
                    }
                    if (j > 0) {
                        error = SATERROR_INVALID_FORMAT;
                    }
                }
                else if (fkey != skey) {
                    error = SATERROR_INVALID_FORMAT;
                }
                break;
        }
    }
    if (error == SATERROR_OK) {
        if (i >= format.size()) {
            if (ampm) {
                if (0 <= hour && hour <= 12) {
                    hour %= 12;
                    if (ispm) {
                        hour += 12;
                    }
                }
                else {
                    error = SATERROR_INVALID_FORMAT;
                }
            }
            if (error == SATERROR_OK) {
                From(year, month, day, hour, minute, second, false);
            }
        }
        else {
            error = SATERROR_INVALID_FORMAT;
        }
    }
    return error;
}

/*public */std::string ofxSATTime::Format(std::string const& format) const
{
    char temp[32];
    char fkey;
    int value;
    int i;
    int j;
    std::string result;
    
    for (i = 0; i < format.size(); ) {
        switch (Search(format, &i, &fkey)) {
            case SEARCH_PERCENT:
                if (i < format.size()) {
                    switch (Search(format, &i, &fkey, &j)) {
                        case SEARCH_PERCENT:
                            result.append(1, fkey);
                            break;
                        case SEARCH_MONTH:
                            result.append(ofxsattime_month[j][_month]);
                            break;
                        case SEARCH_MTH:
                            result.append(ofxsattime_mth[j][_month]);
                            break;
                        case SEARCH_WEEK:
                            result.append(ofxsattime_week[j][_week + 1]);
                            break;
                        case SEARCH_WEK:
                            result.append(ofxsattime_wek[j][_week + 1]);
                            break;
                        case SEARCH_YOUBI:
                            result.append(ofxsattime_youbi[j][_week + 1]);
                            break;
                        case SEARCH_AMPM:
                            result.append(ofxsattime_ampm[j][(_hour < 12) ? (1) : (2)]);
                            break;
                        case SEARCH_GOZENGOGO:
                            result.append(ofxsattime_gozengogo[j][(_hour < 12) ? (1) : (2)]);
                            break;
                        default:
                            switch (fkey) {
                                case ' ':
                                    // nop
                                    break;
                                case '*':
                                    result.append(j, fkey);
                                    break;
                                case 'Y':
                                case 'M':
                                case 'D':
                                case 'H':
                                case 'h':
                                case 'm':
                                case 's':
                                    value = 0;
                                    switch (fkey) {
                                        case 'Y':
                                            value = _year;
                                            break;
                                        case 'M':
                                            value = _month;
                                            break;
                                        case 'D':
                                            value = _day;
                                            break;
                                        case 'H':
                                            if ((value = _hour % 12) == 0) {
                                                value = 12;
                                            }
                                            break;
                                        case 'h':
                                            value = _hour;
                                            break;
                                        case 'm':
                                            value = _minute;
                                            break;
                                        case 's':
                                            value = _second;
                                            break;
                                        default:
                                            break;
                                    }
                                    if (j >= 4) {
                                        value %= 10000;
                                        j = 2;
                                    }
                                    else if (j >= 2) {
                                        value %= 100;
                                        j = 1;
                                    }
                                    else {
                                        j = 0;
                                    }
                                    snprintf(temp, sizeof(temp), ofxsattime_format[j], value);
                                    result.append(temp);
                                    break;
                                default:
                                    break;
                            }
                            break;
                    }
                }
                break;
            default:
                result.append(1, fkey);
                break;
        }
    }
    return result;
}

/*public static */ofxSATTime ofxSATTime::EpochTime(void)
{
    return ofxSATTime(0);
}

/*public static */ofxSATTime ofxSATTime::EpochUTCTime(void)
{
    return ofxSATTime(1970, 1, 1, 0, 0, 0);
}

/*public static */ofxSATTime ofxSATTime::CurrentTime(void)
{
    return ofxSATTime(time(NULL));
}

/*public static */ofxSATTime ofxSATTime::CurrentUTCTime(void)
{
    time_t utc;
    tm* addr;
    tm temp = {
        0
    };
    
    utc = time(NULL);
    if ((addr = gmtime(&utc)) != NULL) {
        temp = *addr;
    }
    return ofxSATTime(temp.tm_year + 1900, temp.tm_mon + 1, temp.tm_mday, temp.tm_hour, temp.tm_min, temp.tm_sec);
}

/*private */void ofxSATTime::From(int year, int month, int day, int hour, int minute, int second, bool truncate)
{
    tm temp = {
        0
    };
    
    temp.tm_year = year - 1900;
    temp.tm_mon = month - 1;
    temp.tm_mday = day;
    temp.tm_hour = hour;
    temp.tm_min = minute;
    temp.tm_sec = second;
    From(mktime(&temp));
    if (truncate) {
        if (_day != day) {
            From(year, month, day - _day, hour, minute, second, false);
        }
    }
    return;
}

/*private */void ofxSATTime::From(time_t param)
{
    tm* addr;
    tm temp = {
        0
    };
    
    if ((addr = localtime(&param)) != NULL) {
        temp = *addr;
    }
    _year = temp.tm_year + 1900;
    _month = temp.tm_mon + 1;
    _day = temp.tm_mday;
    _hour = temp.tm_hour;
    _minute = temp.tm_min;
    _second = temp.tm_sec;
    _week = static_cast<DayOfWeekEnum>(temp.tm_wday);
    return;
}

/*private */time_t ofxSATTime::To(void) const
{
    tm temp = {
        0
    };
    
    temp.tm_year = _year - 1900;
    temp.tm_mon = _month - 1;
    temp.tm_mday = _day;
    temp.tm_hour = _hour;
    temp.tm_min = _minute;
    temp.tm_sec = _second;
    return mktime(&temp);
}

/*private static */ofxSATTime::SearchEnum ofxSATTime::Search(std::string const& string, int* index, char* key)
{
    SearchEnum result(SEARCH_LIMIT);
    
    *key = string[*index];
    ++*index;
    switch (*key) {
        case '%':
            result = SEARCH_PERCENT;
            break;
        default:
            break;
    }
    return result;
}

/*private static */ofxSATTime::SearchEnum ofxSATTime::Search(std::string const& string, int* index, char* key, int* hint)
{
    int i;
    SearchEnum result(SEARCH_LIMIT);
    
    *key = string[*index];
    switch (*key) {
        case '%':
            ++*index;
            result = SEARCH_PERCENT;
            break;
        case 'M':
        case 'm':
            for (i = 0; i < lengthof(ofxsattime_month); ++i) {
                if (Compare(string, index, ofxsattime_month[i][0])) {
                    *hint = i;
                    result = SEARCH_MONTH;
                    break;
                }
            }
            if (i >= lengthof(ofxsattime_month)) {
                for (i = 0; i < lengthof(ofxsattime_mth); ++i) {
                    if (Compare(string, index, ofxsattime_mth[i][0])) {
                        *hint = i;
                        result = SEARCH_MTH;
                        break;
                    }
                }
            }
            break;
        case 'W':
        case 'w':
            for (i = 0; i < lengthof(ofxsattime_week); ++i) {
                if (Compare(string, index, ofxsattime_week[i][0])) {
                    *hint = i;
                    result = SEARCH_WEEK;
                    break;
                }
            }
            if (i >= lengthof(ofxsattime_week)) {
                for (i = 0; i < lengthof(ofxsattime_wek); ++i) {
                    if (Compare(string, index, ofxsattime_wek[i][0])) {
                        *hint = i;
                        result = SEARCH_WEK;
                        break;
                    }
                }
            }
            break;
        case 'y':
            for (i = 0; i < lengthof(ofxsattime_youbi); ++i) {
                if (Compare(string, index, ofxsattime_youbi[i][0])) {
                    *hint = i;
                    result = SEARCH_YOUBI;
                    break;
                }
            }
            break;
        case 'A':
        case 'a':
            for (i = 0; i < lengthof(ofxsattime_ampm); ++i) {
                if (Compare(string, index, ofxsattime_ampm[i][0])) {
                    *hint = i;
                    result = SEARCH_AMPM;
                    break;
                }
            }
            break;
        case 'g':
            for (i = 0; i < lengthof(ofxsattime_gozengogo); ++i) {
                if (Compare(string, index, ofxsattime_gozengogo[i][0])) {
                    *hint = i;
                    result = SEARCH_GOZENGOGO;
                    break;
                }
            }
            break;
        default:
            break;
    }
    if (result == SEARCH_LIMIT) {
        for (i = 0; *index < string.size(); ++*index, ++i) {
            if (string[*index] != *key) {
                break;
            }
        }
        switch (*key) {
            case '*':
                // nop
                break;
            case 'Y':
                if (i >= 4) {
                    i = 4;
                    break;
                }
            case 'M':
            case 'D':
            case 'H':
            case 'h':
            case 'm':
            case 's':
                if (i >= 2) {
                    i = 2;
                    break;
                }
            default:
                if (i >= 1) {
                    i = 1;
                }
                break;
        }
        *hint = i;
    }
    return result;
}

/*private static */void ofxSATTime::Step(std::string const& string, int* index, char* key)
{
    *key = string[*index];
    ++*index;
    return;
}

/*private static */bool ofxSATTime::Compare(std::string const& string, int* index, char const* compare)
{
    int length;
    bool result(false);
    
    length = strlen(compare);
    if (string.compare(*index, length, compare) == 0) {
        *index += length;
        result = true;
    }
    return result;
}
