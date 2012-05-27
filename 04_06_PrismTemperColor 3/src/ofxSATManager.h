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
***     ofxSATManager.h
**/

#ifndef __OFXSATMANAGER_H
#define __OFXSATMANAGER_H

#include "ofxSATType.h"
#include "ofxSAT.h"

class ofxSATManager {
    public:
        explicit                    ofxSATManager                   (void);
                                    ~ofxSATManager                  (void);
                ofxSATError         SetID                           (ofxSAT* param);
    private:
                                    ofxSATManager                   (ofxSATManager const&);
                ofxSATManager&      operator=                       (ofxSATManager const&);
};

#endif
