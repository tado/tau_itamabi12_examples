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
***     ofxSATTime.h
**/

#ifndef __OFX_SATTIME_H
#define __OFX_SATTIME_H

#include "ofxSATType.h"
#include <string>
#include "ofxSATTimeDiff.h"

class ofxSATTime {
    public:
        enum DayOfWeekEnum {
            DAYOFWEEK_SUNDAY,
            DAYOFWEEK_MONDAY,
            DAYOFWEEK_TUESDAY,
            DAYOFWEEK_WEDNESDAY,
            DAYOFWEEK_THURSDAY,
            DAYOFWEEK_FRIDAY,
            DAYOFWEEK_SATURDAY
        };
    private:
        enum SearchEnum {
            SEARCH_PERCENT,
            SEARCH_MONTH,
            SEARCH_MTH,
            SEARCH_WEEK,
            SEARCH_WEK,
            SEARCH_YOUBI,
            SEARCH_AMPM,
            SEARCH_GOZENGOGO,
            SEARCH_LIMIT
        };
    
    private:
                int                 _year;
                int                 _month;
                int                 _day;
                int                 _hour;
                int                 _minute;
                int                 _second;
                DayOfWeekEnum       _week;
    
    public:
        explicit                    ofxSATTime                      (void);
                                    ofxSATTime                      (ofxSATTime const& param);
        explicit                    ofxSATTime                      (int year, int month, int day, int hour, int minute, int second);
        explicit                    ofxSATTime                      (int year, int month, int day);
        explicit                    ofxSATTime                      (time_t param);
                                    ~ofxSATTime                     (void);
                ofxSATTime&         operator=                       (ofxSATTime const& param);
                ofxSATTime&         operator+=                      (ofxSATTimeDiff const& param);
                ofxSATTime&         operator-=                      (ofxSATTimeDiff const& param);
                ofxSATTime&         Set                             (ofxSATTime const& param);
                ofxSATTime&         Set                             (int year, int month, int day, int hour, int minute, int second);
                ofxSATTime&         Set                             (int year, int month, int day);
                ofxSATTime&         Set                             (time_t param);
                ofxSATTime&         SetDate                         (int year, int month, int day);
                void                GetDate                         (int* year, int* month, int* day, DayOfWeekEnum* week = NULL) const;
                ofxSATTime&         SetTime                         (int hour, int minute, int second);
                void                GetTime                         (int* hour, int* minute, int* second) const;
                ofxSATTime&         SetYear                         (int param);
                int                 GetYear                         (void) const;
                ofxSATTime&         SetMonth                        (int param);
                int                 GetMonth                        (void) const;
                ofxSATTime&         SetDay                          (int param);
                int                 GetDay                          (void) const;
                ofxSATTime&         SetHour                         (int param);
                int                 GetHour                         (void) const;
                ofxSATTime&         SetMinute                       (int param);
                int                 GetMinute                       (void) const;
                ofxSATTime&         SetSecond                       (int param);
                int                 GetSecond                       (void) const;
                DayOfWeekEnum       GetDayOfWeek                    (void) const;
                ofxSATTime&         Add                             (ofxSATTimeDiff const& param);
                ofxSATTime&         AddYear                         (int param);
                ofxSATTime&         AddMonth                        (int param);
                ofxSATTime&         AddDay                          (int param);
                ofxSATTime&         AddHour                         (int param);
                ofxSATTime&         AddMinute                       (int param);
                ofxSATTime&         AddSecond                       (int param);
                ofxSATTime&         Sub                             (ofxSATTimeDiff const& param);
                ofxSATTime&         SubYear                         (int param);
                ofxSATTime&         SubMonth                        (int param);
                ofxSATTime&         SubDay                          (int param);
                ofxSATTime&         SubHour                         (int param);
                ofxSATTime&         SubMinute                       (int param);
                ofxSATTime&         SubSecond                       (int param);
                bool                Equals                          (ofxSATTime const& param) const;
                bool                EqualsDate                      (ofxSATTime const& param) const;
                bool                EqualsTime                      (ofxSATTime const& param) const;
                int                 Compare                         (ofxSATTime const& param) const;
                int                 CompareDate                     (ofxSATTime const& param) const;
                int                 CompareTime                     (ofxSATTime const& param) const;
                ofxSATTimeDiff      Difference                      (ofxSATTime const& param) const;
                ofxSATError         Parse                           (std::string const& format, std::string const& string);
                std::string         Format                          (std::string const& format) const;
                time_t              AsTime_t                        (void) const;
        static  ofxSATTime          EpochTime                       (void);
        static  ofxSATTime          EpochUTCTime                    (void);
        static  ofxSATTime          CurrentTime                     (void);
        static  ofxSATTime          CurrentUTCTime                  (void);
    private:
                void                From                            (int year, int month, int day, int hour, int minute, int second, bool truncate);
                void                From                            (time_t param);
                time_t              To                              (void) const;
        static  SearchEnum          Search                          (std::string const& string, int* index, char* key);
        static  SearchEnum          Search                          (std::string const& string, int* index, char* key, int* hint);
        static  void                Step                            (std::string const& string, int* index, char* key);
        static  bool                Compare                         (std::string const& string, int* index, char const* compare);
};

extern  ofxSATTime                  operator+                       (ofxSATTime const& x, ofxSATTimeDiff const& y);
extern  ofxSATTime                  operator-                       (ofxSATTime const& x, ofxSATTimeDiff const& y);
extern  ofxSATTimeDiff              operator-                       (ofxSATTime const& x, ofxSATTime const& y);
extern  bool                        operator==                      (ofxSATTime const& x, ofxSATTime const& y);
extern  bool                        operator!=                      (ofxSATTime const& x, ofxSATTime const& y);
extern  bool                        operator<                       (ofxSATTime const& x, ofxSATTime const& y);
extern  bool                        operator<=                      (ofxSATTime const& x, ofxSATTime const& y);
extern  bool                        operator>                       (ofxSATTime const& x, ofxSATTime const& y);
extern  bool                        operator>=                      (ofxSATTime const& x, ofxSATTime const& y);

/*public */inline ofxSATTime::ofxSATTime(void)
{
    Set(1970, 1, 1, 0, 0, 0);
}

/*public */inline ofxSATTime::ofxSATTime(ofxSATTime const& param)
{
    Set(param);
}

/*public */inline ofxSATTime::ofxSATTime(int year, int month, int day, int hour, int minute, int second)
{
    Set(year, month, day, hour, minute, second);
}

/*public */inline ofxSATTime::ofxSATTime(int year, int month, int day)
{
    Set(year, month, day);
}

/*public */inline ofxSATTime::ofxSATTime(time_t param)
{
    Set(param);
}

/*public */inline ofxSATTime::~ofxSATTime(void)
{
}

/*public */inline ofxSATTime& ofxSATTime::operator=(ofxSATTime const& param)
{
    return Set(param);
}

/*public */inline ofxSATTime& ofxSATTime::operator+=(ofxSATTimeDiff const& param)
{
    return Add(param);
}

/*public */inline ofxSATTime& ofxSATTime::operator-=(ofxSATTimeDiff const& param)
{
    return Sub(param);
}

/*public */inline int ofxSATTime::GetYear(void) const
{
    return _year;
}

/*public */inline int ofxSATTime::GetMonth(void) const
{
    return _month;
}

/*public */inline int ofxSATTime::GetDay(void) const
{
    return _day;
}

/*public */inline int ofxSATTime::GetHour(void) const
{
    return _hour;
}

/*public */inline int ofxSATTime::GetMinute(void) const
{
    return _minute;
}

/*public */inline int ofxSATTime::GetSecond(void) const
{
    return _second;
}

/*public */inline ofxSATTime::DayOfWeekEnum ofxSATTime::GetDayOfWeek(void) const
{
    return _week;
}

/*public */inline time_t ofxSATTime::AsTime_t(void) const
{
    return To();
}

inline ofxSATTime operator+(ofxSATTime const& x, ofxSATTimeDiff const& y)
{
    return ofxSATTime(x).operator+=(y);
}

inline ofxSATTime operator-(ofxSATTime const& x, ofxSATTimeDiff const& y)
{
    return ofxSATTime(x).operator-=(y);
}

inline ofxSATTimeDiff operator-(ofxSATTime const& x, ofxSATTime const& y)
{
    return x.Difference(y);
}

inline bool operator==(ofxSATTime const& x, ofxSATTime const& y)
{
    return x.Equals(y);
}

inline bool operator!=(ofxSATTime const& x, ofxSATTime const& y)
{
    return !x.Equals(y);
}

inline bool operator<(ofxSATTime const& x, ofxSATTime const& y)
{
    return (x.Compare(y) < 0);
}

inline bool operator<=(ofxSATTime const& x, ofxSATTime const& y)
{
    return (x.Compare(y) <= 0);
}

inline bool operator>(ofxSATTime const& x, ofxSATTime const& y)
{
    return (x.Compare(y) > 0);
}

inline bool operator>=(ofxSATTime const& x, ofxSATTime const& y)
{
    return (x.Compare(y) >= 0);
}

#endif
