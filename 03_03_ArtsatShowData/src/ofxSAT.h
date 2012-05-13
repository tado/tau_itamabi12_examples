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
***     ofxSAT.h
**/

#ifndef __OFXSAT_H
#define __OFXSAT_H

#include "ofxSATType.h"
#include <vector>
#include "ofxSATTime.h"

class ofxSAT {
    public:
        enum SensorEnum {
            // default
            SENSOR_LIMIT
        };
        enum FormatEnum {
            // primitive
            FORMAT_BOOL,
            FORMAT_INT,
            FORMAT_DOUBLE,
            // class
            FORMAT_STRING,
            FORMAT_OFXSATTIME,
            // default
            FORMAT_LIMIT
        };
        enum UnitEnum {
            // general
            UNIT_NONE,
            // voltage
            UNIT_KV,
            UNIT_V,
            UNIT_mV,
            UNIT_uV,
            UNIT_nV,
            // current
            UNIT_KA,
            UNIT_A,
            UNIT_mA,
            UNIT_uA,
            UNIT_nA,
            // velocity
            UNIT_RAD_S,
            UNIT_DEG_S,
            // temperature
            UNIT_KK,
            UNIT_K,
            UNIT_mK,
            UNIT_uK,
            UNIT_nK,
            UNIT_degC,
            UNIT_degF,
            // magnetism
            UNIT_KT,
            UNIT_T,
            UNIT_mT,
            UNIT_uT,
            UNIT_nT,
            // default
            UNIT_LIMIT
        };
    
    public:
        typedef int                 SensorType;
        struct TLERec {
            char                    line[2][70];
        };
    
    private:
                std::string         _id;
    
    public:
        virtual                     ~ofxSAT                         (void) = 0;
                std::string const&  GetID                           (void) const;
        virtual ofxSATError         GetTLE                          (TLERec* result) const = 0;
        virtual ofxSATError         GetTLETime                      (ofxSATTime* result) const = 0;
        virtual ofxSATError         GetAvailableTime                (std::vector<ofxSATTime>* result) const = 0;
        virtual FormatEnum          GetSensorFormat                 (SensorType sensor) const = 0;
        virtual UnitEnum            GetSensorUnit                   (SensorType sensor) const = 0;
        virtual ofxSATError         GetSensorData                   (SensorType sensor, ofxSATTime const& time, void* result, int size, bool* simulation = NULL) const = 0;
    protected:
        explicit                    ofxSAT                          (void);
                void                SetID                           (std::string const& param);
        static  std::string         Trim                            (std::string const& param);
        static  std::string         Replace                         (std::string const& string, std::string const& from, std::string const& to);
    private:
                                    ofxSAT                          (ofxSAT const&);
                ofxSAT&             operator=                       (ofxSAT const&);
    friend      class               ofxSATManager;
};

/*public */inline std::string const& ofxSAT::GetID(void) const
{
    return _id;
}

/*protected */inline void ofxSAT::SetID(std::string const& param)
{
    _id = param;
    return;
}

#endif
