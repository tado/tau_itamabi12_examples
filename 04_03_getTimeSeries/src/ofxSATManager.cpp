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
***     ofxSATManager.cpp
**/

#include "ofxSATManager.h"

/*public */ofxSATManager::ofxSATManager(void)
{
}

/*public */ofxSATManager::~ofxSATManager(void)
{
}

/*public */ofxSATError ofxSATManager::SetID(ofxSAT* param)
{
    ofxSATError error(SATERROR_OK);
    
    if (param != NULL) {
        param->SetID("PRISM");
    }
    else {
        error = SATERROR_INVALID_PARAM;
    }
    return error;
}
