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
***     ofxSAT.cpp
**/

#include "ofxSAT.h"

/*protected */ofxSAT::ofxSAT(void)
{
}

/*public virtual */ofxSAT::~ofxSAT(void)
{
}

/*protected static */std::string ofxSAT::Trim(std::string const& param)
{
    int index;
    std::string result(param);
    
    if ((index = result.find(' ')) != std::string::npos) {
        result.erase(index);
    }
    return result;
}

/*protected static */std::string ofxSAT::Replace(std::string const& string, std::string const& from, std::string const& to)
{
    int i;
    std::string result(string);
    
    i = 0;
    while ((i = result.find(from, i)) != std::string::npos) {
        result.replace(i, from.size(), to);
        i += to.size();
    }
    return result;
}
