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
***     ofxSATTimeDiff.h
**/

#ifndef __OFX_SATTIMEDIFF_H
#define __OFX_SATTIMEDIFF_H

#include "ofxSATType.h"
#include <time.h>

class ofxSATTimeDiff {
    private:
                time_t              _second;
    
    public:
        explicit                    ofxSATTimeDiff                  (void);
                                    ofxSATTimeDiff                  (ofxSATTimeDiff const& param);
        explicit                    ofxSATTimeDiff                  (int day, int hour, int minute, int second);
        explicit                    ofxSATTimeDiff                  (int hour, int minute, int second);
        explicit                    ofxSATTimeDiff                  (int minute, int second);
        explicit                    ofxSATTimeDiff                  (time_t second);
                                    ~ofxSATTimeDiff                 (void);
                ofxSATTimeDiff&     operator=                       (ofxSATTimeDiff const& param);
                ofxSATTimeDiff&     operator+=                      (ofxSATTimeDiff const& param);
                ofxSATTimeDiff&     operator-=                      (ofxSATTimeDiff const& param);
                ofxSATTimeDiff&     operator*=                      (int param);
                ofxSATTimeDiff&     operator/=                      (int param);
                ofxSATTimeDiff&     operator%=                      (int param);
                ofxSATTimeDiff      operator+                       (void) const;
                ofxSATTimeDiff      operator-                       (void) const;
                ofxSATTimeDiff&     Set                             (ofxSATTimeDiff const& param);
                ofxSATTimeDiff&     Set                             (int day, int hour, int minute, int second);
                void                Get                             (int* day, int* hour, int* minute, int* second) const;
                ofxSATTimeDiff&     Set                             (int hour, int minute, int second);
                void                Get                             (int* hour, int* minute, int* second) const;
                ofxSATTimeDiff&     Set                             (int minute, int second);
                void                Get                             (int* minute, int* second) const;
                ofxSATTimeDiff&     Set                             (time_t second);
                ofxSATTimeDiff&     Add                             (ofxSATTimeDiff const& param);
                ofxSATTimeDiff&     Sub                             (ofxSATTimeDiff const& param);
                ofxSATTimeDiff&     Mul                             (int param);
                ofxSATTimeDiff&     Div                             (int param);
                ofxSATTimeDiff&     Mod                             (int param);
                ofxSATTimeDiff&     Neg                             (void);
                bool                Equals                          (ofxSATTimeDiff const& param) const;
                int                 Compare                         (ofxSATTimeDiff const& param) const;
                time_t              AsTime_t                        (void) const;
        static  ofxSATTimeDiff      LocalTimeOffset                 (void);
};

extern  ofxSATTimeDiff              operator+                       (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);
extern  ofxSATTimeDiff              operator-                       (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);
extern  ofxSATTimeDiff              operator*                       (ofxSATTimeDiff const& x, int y);
extern  ofxSATTimeDiff              operator/                       (ofxSATTimeDiff const& x, int y);
extern  ofxSATTimeDiff              operator%                       (ofxSATTimeDiff const& x, int y);
extern  bool                        operator==                      (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);
extern  bool                        operator!=                      (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);
extern  bool                        operator<                       (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);
extern  bool                        operator<=                      (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);
extern  bool                        operator>                       (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);
extern  bool                        operator>=                      (ofxSATTimeDiff const& x, ofxSATTimeDiff const& y);

/*public */inline ofxSATTimeDiff::ofxSATTimeDiff(void)
{
}

/*public */inline ofxSATTimeDiff::ofxSATTimeDiff(ofxSATTimeDiff const& param)
{
    Set(param);
}

/*public */inline ofxSATTimeDiff::ofxSATTimeDiff(int day, int hour, int minute, int second)
{
    Set(day, hour, minute, second);
}

/*public */inline ofxSATTimeDiff::ofxSATTimeDiff(int hour, int minute, int second)
{
    Set(hour, minute, second);
}

/*public */inline ofxSATTimeDiff::ofxSATTimeDiff(int minute, int second)
{
    Set(minute, second);
}

/*public */inline ofxSATTimeDiff::ofxSATTimeDiff(time_t second)
{
    Set(second);
}

/*public */inline ofxSATTimeDiff::~ofxSATTimeDiff(void)
{
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::operator=(ofxSATTimeDiff const& param)
{
    return Set(param);
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::operator+=(ofxSATTimeDiff const& param)
{
    return Add(param);
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::operator-=(ofxSATTimeDiff const& param)
{
    return Sub(param);
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::operator*=(int param)
{
    return Mul(param);
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::operator/=(int param)
{
    return Div(param);
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::operator%=(int param)
{
    return Mod(param);
}

/*public */inline ofxSATTimeDiff ofxSATTimeDiff::operator+(void) const
{
    return ofxSATTimeDiff(+_second);
}

/*public */inline ofxSATTimeDiff ofxSATTimeDiff::operator-(void) const
{
    return ofxSATTimeDiff(-_second);
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::Set(ofxSATTimeDiff const& param)
{
    _second = param._second;
    return *this;
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::Set(time_t second)
{
    _second = second;
    return *this;
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::Add(ofxSATTimeDiff const& param)
{
    _second += param._second;
    return *this;
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::Sub(ofxSATTimeDiff const& param)
{
    _second -= param._second;
    return *this;
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::Mul(int param)
{
    _second *= param;
    return *this;
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::Div(int param)
{
    _second /= param;
    return *this;
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::Mod(int param)
{
    _second %= param;
    return *this;
}

/*public */inline ofxSATTimeDiff& ofxSATTimeDiff::Neg(void)
{
    _second = -_second;
    return *this;
}

/*public */inline bool ofxSATTimeDiff::Equals(ofxSATTimeDiff const& param) const
{
    return (_second == param._second);
}

/*public */inline time_t ofxSATTimeDiff::AsTime_t(void) const
{
    return _second;
}

inline ofxSATTimeDiff operator+(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return ofxSATTimeDiff(x).operator+=(y);
}

inline ofxSATTimeDiff operator-(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return ofxSATTimeDiff(x).operator-=(y);
}

inline ofxSATTimeDiff operator*(ofxSATTimeDiff const& x, int y)
{
    return ofxSATTimeDiff(x).operator*=(y);
}

inline ofxSATTimeDiff operator/(ofxSATTimeDiff const& x, int y)
{
    return ofxSATTimeDiff(x).operator/=(y);
}

inline ofxSATTimeDiff operator%(ofxSATTimeDiff const& x, int y)
{
    return ofxSATTimeDiff(x).operator%=(y);
}

inline bool operator==(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return x.Equals(y);
}

inline bool operator!=(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return !x.Equals(y);
}

inline bool operator<(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return (x.Compare(y) < 0);
}

inline bool operator<=(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return (x.Compare(y) <= 0);
}

inline bool operator>(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return (x.Compare(y) > 0);
}

inline bool operator>=(ofxSATTimeDiff const& x, ofxSATTimeDiff const& y)
{
    return (x.Compare(y) >= 0);
}

#endif
