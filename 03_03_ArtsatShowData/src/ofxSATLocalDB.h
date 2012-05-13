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
***     ofxSATLocalDB.h
**/

#ifndef __OFXSATLOCALDB_H
#define __OFXSATLOCALDB_H

#include "ofxSATType.h"
#include "ofxSAT.h"
#include "ofxSQLite.h"

#define SQL_TABLE_BEGIN(param)      ("CREATE TABLE IF NOT EXISTS " + std::string(param) + "(")
#define SQL_PRIMARY_KEY             ("_id_ INTEGER PRIMARY KEY AUTOINCREMENT")
#define SQL_TABLE_END               (");")
#define SQL_TIME                    ("%YYYY-%MM-%DD %hh:%mm:%ss")

class ofxSATLocalDB : public ofxSAT {
    private:
        mutable ofxSQLite*          _sql;
        mutable std::string         _id;
    
    protected:
        explicit                    ofxSATLocalDB                   (void);
        virtual                     ~ofxSATLocalDB                  (void);
                ofxSQLite*          GetSQL                          (void) const;
                ofxSATError         OpenSQL                         (void) const;
                void                CloseSQL                        (void) const;
    private:
                                    ofxSATLocalDB                   (ofxSATLocalDB const&);
                ofxSATLocalDB&      operator=                       (ofxSATLocalDB const&);
};

/*protected */inline ofxSQLite* ofxSATLocalDB::GetSQL(void) const
{
    return _sql;
}

#endif
