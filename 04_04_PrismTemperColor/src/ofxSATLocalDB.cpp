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
***     ofxSATLocalDB.cpp
**/

#include "ofxSATLocalDB.h"
#include "ofUtils.h"

#define REPLACE_FROM            ("://")
#define REPLACE_TO              ("-")
#define SQL_EXTENSION           (".db")

/*protected */ofxSATLocalDB::ofxSATLocalDB(void) : _sql(NULL)
{
}

/*protected virtual */ofxSATLocalDB::~ofxSATLocalDB(void)
{
    CloseSQL();
}

/*protected */ofxSATError ofxSATLocalDB::OpenSQL(void) const
{
    ofxSATError error(SATERROR_OK);
    
    if (_sql != NULL) {
        if (_id != GetID()) {
            CloseSQL();
        }
    }
    if (_sql == NULL) {
        if (!GetID().empty()) {
            if ((_sql = new ofxSQLite(ofToDataPath(Replace(GetID(), REPLACE_FROM, REPLACE_TO) + SQL_EXTENSION))) != NULL) {
                _id = GetID();
            }
            else {
                error = SATERROR_NO_MEMORY;
            }
        }
        else {
            error = SATERROR_INVALID_STATE;
        }
    }
    return error;
}

/*protected */void ofxSATLocalDB::CloseSQL(void) const
{
    if (_sql != NULL) {
        delete _sql;
        _sql = NULL;
    }
    return;
}
