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
***     ofxSATTimeDiff.cpp
**/

#include "ofxSATTimeDiff.h"
#include "ofxSATTime.h"

/*public */ofxSATTimeDiff& ofxSATTimeDiff::Set(int day, int hour, int minute, int second)
{
    _second = 86400 * day + 3600 * hour + 60 * minute + second;
    return *this;
}

/*public */void ofxSATTimeDiff::Get(int* day, int* hour, int* minute, int* second) const
{
    time_t value;
    
    value = _second;
    if (second != NULL) {
        *second = value % 60;
    }
    value /= 60;
    if (minute != NULL) {
        *minute = value % 60;
    }
    value /= 60;
    if (hour != NULL) {
        *hour = value % 24;
    }
    value /= 24;
    if (day != NULL) {
        *day = value;
    }
    return;
}

/*public */ofxSATTimeDiff& ofxSATTimeDiff::Set(int hour, int minute, int second)
{
    _second = 3600 * hour + 60 * minute + second;
    return *this;
}

/*public */void ofxSATTimeDiff::Get(int* hour, int* minute, int* second) const
{
    time_t value;
    
    value = _second;
    if (second != NULL) {
        *second = value % 60;
    }
    value /= 60;
    if (minute != NULL) {
        *minute = value % 60;
    }
    value /= 60;
    if (hour != NULL) {
        *hour = value;
    }
    return;
}

/*public */ofxSATTimeDiff& ofxSATTimeDiff::Set(int minute, int second)
{
    _second = 60 * minute + second;
    return *this;
}

/*public */void ofxSATTimeDiff::Get(int* minute, int* second) const
{
    time_t value;
    
    value = _second;
    if (second != NULL) {
        *second = value % 60;
    }
    value /= 60;
    if (minute != NULL) {
        *minute = value;
    }
    return;
}

/*public */int ofxSATTimeDiff::Compare(ofxSATTimeDiff const& param) const
{
    int result(0);
    
    if (_second > param._second) {
        result = +1;
    }
    else if (_second < param._second) {
        result = -1;
    }
    return result;
}

/*public static */ofxSATTimeDiff ofxSATTimeDiff::LocalTimeOffset(void)
{
    return ofxSATTimeDiff(-ofxSATTime::EpochUTCTime().AsTime_t());
}
