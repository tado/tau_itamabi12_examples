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
***     ofxSATType.h
**/

#ifndef __OFX_SATTYPE_H
#define __OFX_SATTYPE_H

#define lengthof(param)         (sizeof(param) / sizeof(param[0]))
#define asciiesof(param)        (lengthof(param) - 1)

enum SATErrorEnum {
    SATERROR_OK,
    SATERROR_FAILED,
    SATERROR_NO_RESULT,
    SATERROR_NO_MEMORY,
    SATERROR_INVALID_PARAM,
    SATERROR_INVALID_STATE,
    SATERROR_INVALID_FORMAT,
    SATERROR_LIMIT
};

typedef int                     ofxSATError;

#endif
