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
***     ofxARTSAT.cpp
**/

#include "ofxARTSAT.h"

#define SAT_ID                  ("norad://00000")

/*public */ofxARTSAT::ofxARTSAT(void)
{
    SetID(SAT_ID);
}

/*public virtual */ofxARTSAT::~ofxARTSAT(void)
{
}

/*public virtual */ofxARTSAT::FormatEnum ofxARTSAT::GetSensorFormat(SensorType sensor) const
{
    return FORMAT_LIMIT;
}

/*public virtual */ofxARTSAT::UnitEnum ofxARTSAT::GetSensorUnit(SensorType sensor) const
{
    return UNIT_LIMIT;
}

/*public virtual */ofxSATError ofxARTSAT::GetSensorData(SensorType sensor, ofxSATTime const& time, void* result, int size, bool* simulation)
{
    ofxSATError error(SATERROR_OK);
    
    return error;
}
