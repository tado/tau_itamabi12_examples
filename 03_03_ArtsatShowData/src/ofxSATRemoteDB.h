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
***     ofxSATRemoteDB.h
**/

#ifndef __OFXSATREMOTEDB_H
#define __OFXSATREMOTEDB_H

#include "ofxSATType.h"
#include "ofxSAT.h"

class ofxSATRemoteDB : public ofxSAT {
    protected:
        explicit                    ofxSATRemoteDB                  (void);
        virtual                     ~ofxSATRemoteDB                 (void);
    private:
                                    ofxSATRemoteDB                  (ofxSATRemoteDB const&);
                ofxSATRemoteDB&     operator=                       (ofxSATRemoteDB const&);
};

#endif
