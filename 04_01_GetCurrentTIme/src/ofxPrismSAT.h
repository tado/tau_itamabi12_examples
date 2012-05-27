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
***     ofxPrismSAT.h
**/

#ifndef __OFX_PRISMSAT_H
#define __OFX_PRISMSAT_H

#include "ofxSATType.h"
#include "ofxSATLocalDB.h"

class ofxPrismSAT : public ofxSATLocalDB {
    public:
        enum SensorEnum {
            SENSOR_MODE             = ofxSATLocalDB::SENSOR_LIMIT,
            SENSOR_TIME_SHOBC,
            SENSOR_CONTROL_ATTITUDE,
            SENSOR_TIME_RTC,
            SENSOR_CONTROL_CAMERA,
            SENSOR_VOLTAGE_SOLAR,
            SENSOR_SCHEDULE_CAMERA,
            SENSOR_VOLTAGE_BATTERY,
            SENSOR_CURRENT_CHARGE,
            SENSOR_CURRENT_DISCHARGE,
            SENSOR_CURRENT_SOLARPXF,
            SENSOR_CURRENT_SOLARMXF,
            SENSOR_CURRENT_SOLARPYF,
            SENSOR_CURRENT_SOLARMYF,
            SENSOR_CURRENT_SOLARPXB,
            SENSOR_CURRENT_SOLARMXB,
            SENSOR_CURRENT_SOLARPYB,
            SENSOR_CURRENT_SOLARMYB,
            SENSOR_CURRENT_SOLARPXM,
            SENSOR_CURRENT_SOLARMXM,
            SENSOR_CURRENT_SOLARPYM,
            SENSOR_CURRENT_SOLARMYM,
            SENSOR_GYRO_X,
            SENSOR_MAGNETOMETER_X,
            SENSOR_GYRO_Y,
            SENSOR_MAGNETOMETER_Y,
            SENSOR_GYRO_Z,
            SENSOR_MAGNETOMETER_Z,
            SENSOR_TEMPERATURE_MAINOBC,
            SENSOR_TEMPERATURE_MAINCAMERA,
            SENSOR_TEMPERATURE_OUTSIDEPX,
            SENSOR_TEMPERATURE_OUTSIDEMX,
            SENSOR_TEMPERATURE_OUTSIDEPY,
            SENSOR_TEMPERATURE_OUTSIDEMY,
            SENSOR_TEMPERATURE_OUTSIDEPZ,
            SENSOR_TEMPERATURE_OUTSIDEMZ,
            SENSOR_TEMPERATURE_PANELPX,
            SENSOR_TEMPERATURE_PANELMX,
            SENSOR_TEMPERATURE_PANELPY,
            SENSOR_TEMPERATURE_PANELMY,
            SENSOR_TEMPERATURE_BATTERY1,
            SENSOR_TEMPERATURE_BATTERY2,
            SENSOR_CURRENT_MAIN33V,
            SENSOR_CURRENT_MAIN50V,
            SENSOR_CURRENT_NETWORK,
            SENSOR_CURRENT_POWER,
            SENSOR_CURRENT_MAINRECEIVER,
            SENSOR_CURRENT_SUBRECEIVER,
            SENSOR_CURRENT_AFSKSENDER,
            SENSOR_CURRENT_GMSKSENDER,
            SENSOR_CURRENT_MISSION50V,
            SENSOR_CURRENT_SENSOR,
            SENSOR_CURRENT_HEATER,
            SENSOR_CURRENT_EXPANDER,
            SENSOR_VOLTAGE_MAIN33V,
            SENSOR_VOLTAGE_MAIN50V,
            SENSOR_VOLTAGE_NETWORK,
            SENSOR_VOLTAGE_POWER,
            SENSOR_VOLTAGE_MAINRECEIVER,
            SENSOR_VOLTAGE_SUBRECEIVER,
            SENSOR_VOLTAGE_AFSKSENDER,
            SENSOR_VOLTAGE_GMSKSENDER,
            SENSOR_VOLTAGE_MISSION50V,
            SENSOR_VOLTAGE_MISSION33V,
            SENSOR_VOLTAGE_HEATER,
            SENSOR_VOLTAGE_EXPANDER,
            SENSOR_LIMIT
        };
    
    private:
        struct ScheduleRec {
            std::string             date;
            std::string             id;
        };
    
    public:
        explicit                    ofxPrismSAT                     (void);
        virtual                     ~ofxPrismSAT                    (void);
        virtual ofxSATError         GetTLE                          (TLERec* result) const;
        virtual ofxSATError         GetTLETime                      (ofxSATTime* result) const;
        virtual ofxSATError         GetAvailableTime                (std::vector<ofxSATTime>* result) const;
        virtual FormatEnum          GetSensorFormat                 (SensorType sensor) const;
        virtual UnitEnum            GetSensorUnit                   (SensorType sensor) const;
        virtual ofxSATError         GetSensorData                   (SensorType sensor, ofxSATTime const& time, void* result, int size, bool* simulation = NULL) const;
                ofxSATError         GetSensorMode                   (ofxSATTime const& time, bool* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTimeSHOBC              (ofxSATTime const& time, int* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorControlAttitude        (ofxSATTime const& time, bool* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTimeRTC                (ofxSATTime const& time, ofxSATTime* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorControlCamera          (ofxSATTime const& time, bool* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorVoltageSolar           (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorScheduleCamera         (ofxSATTime const& time, bool* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorVoltageBattery         (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentCharge          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentDischarge       (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentSolarPXF        (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentSolarMXF        (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentSolarPYF        (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentSolarMYF        (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentSolarPXB        (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentSolarMXB        (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentSolarPYB        (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentSolarMYB        (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentSolarPXM        (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentSolarMXM        (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentSolarPYM        (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentSolarMYM        (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorGyroX                  (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorMagnetometerX          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorGyroY                  (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorMagnetometerY          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorGyroZ                  (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorMagnetometerZ          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTemperatureMainOBC     (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTemperatureMainCamera  (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTemperatureOutsidePX   (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTemperatureOutsideMX   (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTemperatureOutsidePY   (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTemperatureOutsideMY   (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTemperatureOutsidePZ   (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTemperatureOutsideMZ   (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTemperaturePanelPX     (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTemperaturePanelMX     (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTemperaturePanelPY     (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTemperaturePanelMY     (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTemperatureBattery1    (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorTemperatureBattery2    (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentMain33V         (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentMain50V         (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentNetwork         (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentPower           (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentMainReceiver    (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentSubReceiver     (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentAFSKSender      (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentGMSKSender      (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentMission50V      (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentSensor          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentHeater          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorCurrentExpander        (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorVoltageMain33V         (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorVoltageMain50V         (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorVoltageNetwork         (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorVoltagePower           (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorVoltageMainReceiver    (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorVoltageSubReceiver     (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorVoltageAFSKSender      (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorVoltageGMSKSender      (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorVoltageMission50V      (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorVoltageMission33V      (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorVoltageHeater          (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
                ofxSATError         GetSensorVoltageExpander        (ofxSATTime const& time, double* result, bool* simulation = NULL) const;
    private:
                ofxSATError         PrepareSQL                      (void) const;
        static  ofxSATError         DecodeData                      (ofxSQLiteSelect& select, FormatEnum format, void* result, int size);
                ofxSATError         DownloadSchedule                (ofxSATTime const& time) const;
                ofxSATError         DownloadData                    (std::string const& id) const;
        static  ofxSATError         ParseSchedule                   (std::string const& buffer, TLERec* tle, std::vector<ScheduleRec>* schedule);
        static  ofxSATError         ParseData                       (std::string const& buffer, std::vector<std::string>* data);
        static  ofxSATError         RecordSchedule                  (TLERec const& tle, std::vector<ScheduleRec> const& schedule, ofxSQLite* sql);
        static  ofxSATError         RecordData                      (std::string const& id, std::vector<std::string> const& data, ofxSQLite* sql);
        static  ofxSATError         NormalizeSchedule               (std::string const& line, TLERec* tle, std::vector<ScheduleRec>* schedule);
        static  ofxSATError         NormalizeData                   (std::vector<std::string>* data);
    private:
                                    ofxPrismSAT                     (ofxPrismSAT const&);
                ofxPrismSAT&        operator=                       (ofxPrismSAT const&);
};

/*public */inline ofxSATError ofxPrismSAT::GetSensorMode(ofxSATTime const& time, bool* result, bool* simulation) const
{
    return GetSensorData(SENSOR_MODE, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTimeSHOBC(ofxSATTime const& time, int* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TIME_SHOBC, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorControlAttitude(ofxSATTime const& time, bool* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CONTROL_ATTITUDE, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTimeRTC(ofxSATTime const& time, ofxSATTime* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TIME_RTC, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorControlCamera(ofxSATTime const& time, bool* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CONTROL_CAMERA, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorVoltageSolar(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_VOLTAGE_SOLAR, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorScheduleCamera(ofxSATTime const& time, bool* result, bool* simulation) const
{
    return GetSensorData(SENSOR_SCHEDULE_CAMERA, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorVoltageBattery(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_VOLTAGE_BATTERY, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentCharge(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_CHARGE, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentDischarge(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_DISCHARGE, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentSolarPXF(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_SOLARPXF, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentSolarMXF(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_SOLARMXF, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentSolarPYF(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_SOLARPYF, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentSolarMYF(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_SOLARMYF, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentSolarPXB(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_SOLARPXB, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentSolarMXB(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_SOLARMXB, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentSolarPYB(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_SOLARPYB, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentSolarMYB(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_SOLARMYB, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentSolarPXM(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_SOLARPXM, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentSolarMXM(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_SOLARMXM, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentSolarPYM(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_SOLARPYM, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentSolarMYM(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_SOLARMYM, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorGyroX(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_GYRO_X, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorMagnetometerX(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_MAGNETOMETER_X, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorGyroY(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_GYRO_Y, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorMagnetometerY(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_MAGNETOMETER_Y, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorGyroZ(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_GYRO_Z, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorMagnetometerZ(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_MAGNETOMETER_Z, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTemperatureMainOBC(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TEMPERATURE_MAINOBC, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTemperatureMainCamera(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TEMPERATURE_MAINCAMERA, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTemperatureOutsidePX(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TEMPERATURE_OUTSIDEPX, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTemperatureOutsideMX(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TEMPERATURE_OUTSIDEMX, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTemperatureOutsidePY(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TEMPERATURE_OUTSIDEPY, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTemperatureOutsideMY(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TEMPERATURE_OUTSIDEMY, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTemperatureOutsidePZ(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TEMPERATURE_OUTSIDEPZ, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTemperatureOutsideMZ(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TEMPERATURE_OUTSIDEMZ, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTemperaturePanelPX(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TEMPERATURE_PANELPX, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTemperaturePanelMX(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TEMPERATURE_PANELMX, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTemperaturePanelPY(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TEMPERATURE_PANELPY, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTemperaturePanelMY(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TEMPERATURE_PANELMY, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTemperatureBattery1(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TEMPERATURE_BATTERY1, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorTemperatureBattery2(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_TEMPERATURE_BATTERY2, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentMain33V(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_MAIN33V, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentMain50V(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_MAIN50V, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentNetwork(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_NETWORK, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentPower(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_POWER, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentMainReceiver(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_MAINRECEIVER, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentSubReceiver(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_SUBRECEIVER, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentAFSKSender(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_AFSKSENDER, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentGMSKSender(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_GMSKSENDER, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentMission50V(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_MISSION50V, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentSensor(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_SENSOR, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentHeater(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_HEATER, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorCurrentExpander(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_CURRENT_EXPANDER, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorVoltageMain33V(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_VOLTAGE_MAIN33V, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorVoltageMain50V(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_VOLTAGE_MAIN50V, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorVoltageNetwork(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_VOLTAGE_NETWORK, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorVoltagePower(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_VOLTAGE_POWER, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorVoltageMainReceiver(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_VOLTAGE_MAINRECEIVER, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorVoltageSubReceiver(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_VOLTAGE_SUBRECEIVER, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorVoltageAFSKSender(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_VOLTAGE_AFSKSENDER, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorVoltageGMSKSender(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_VOLTAGE_GMSKSENDER, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorVoltageMission50V(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_VOLTAGE_MISSION50V, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorVoltageMission33V(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_VOLTAGE_MISSION33V, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorVoltageHeater(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_VOLTAGE_HEATER, time, result, sizeof(*result), simulation);
}

/*public */inline ofxSATError ofxPrismSAT::GetSensorVoltageExpander(ofxSATTime const& time, double* result, bool* simulation) const
{
    return GetSensorData(SENSOR_VOLTAGE_EXPANDER, time, result, sizeof(*result), simulation);
}

#endif
