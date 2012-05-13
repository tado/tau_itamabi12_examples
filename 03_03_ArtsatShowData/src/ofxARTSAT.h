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
***     ofxARTSAT.h
**/

#ifndef __OFXARTSAT_H
#define __OFXARTSAT_H

#include "ofxSATType.h"
#include "ofxSATLocalDB.h"

class ofxARTSAT : public ofxSATLocalDB {
    public:
        enum SensorEnum {
            SENSOR_TEMPERATURE      = ofxSATLocalDB::SENSOR_LIMIT,
            SENSOR_RADIATION,
            SENSOR_LIMIT
        };
    
    public:
        explicit                    ofxARTSAT                       (void);
        virtual                     ~ofxARTSAT                      (void);
        virtual FormatEnum          GetSensorFormat                 (SensorType sensor) const;
        virtual UnitEnum            GetSensorUnit                   (SensorType sensor) const;
        virtual ofxSATError         GetSensorData                   (SensorType sensor, ofxSATTime const& time, void* result, int size, bool* simulation);
    private:
                                    ofxARTSAT                       (ofxARTSAT const&);
                ofxARTSAT&          operator=                       (ofxARTSAT const&);
};

#endif
