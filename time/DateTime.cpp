/************************************************
 * @file DateTime.cpp
 * \brief 
 * @author Roger
 * @version V1.0.0
 * @date 2016-07
 ***********************************************/
 
#include <iostream>
#include "DateTime.hpp"

namespace time {
/*
 * Constructor
 */ 
DateTime::DateTime(const string &format) : m_format(format), 
                                           m_year(0),
                                           m_month(0),
                                           m_day(0),
                                           m_hour(0),
                                           m_minute(0),
                                           m_second(0) {
}

/*
 * Constructor
 */ 
DateTime::DateTime(int year, int month, int day, 
                   int hour, int minute, int second) :
                                           m_year(year),
                                           m_month(month),
                                           m_day(day),
                                           m_hour(hour),
                                           m_minute(minute),
                                           m_second(second) {
    m_tm_time.tm_year = year - 1900; //year starts from 1900
    m_tm_time.tm_mon = month - 1; //month starts from 0, 0 is January
    m_tm_time.tm_mday = day;
    m_tm_time.tm_hour = hour;
    m_tm_time.tm_min = minute;
    m_tm_time.tm_sec = second;
}

/*
 * Get current seconds from 1970-01-01
 */ 
time_t DateTime::GetSecondsFrom1970_1_1() {
    time_t curTime;
    time(&curTime);
    return curTime;
}

/*
 * Get current UTC time
 */ 
void DateTime::GetCurrentUTCTime() {
    time_t curTime;
    time(&curTime);
    struct tm *now = gmtime(&curTime);
    m_year = now->tm_year + 1900;
    m_month = now->tm_mon + 1;
    m_day = now->tm_mday；
    m_hour = now->tm_hour;
    m_minute = now->tm_min;
    m_second = now->tm_sec;
}

/*
 * Get current local time
 */ 
void DateTime::GetCurrentLocalTime() {
    time_t curTime;
    time(&curTime);
    struct tm *now = localtime(&curTime);
    m_year = now->tm_year + 1900;
    m_month = now->tm_mon + 1;
    m_day = now->tm_mday；
    m_hour = now->tm_hour;
    m_minute = now->tm_min;
    m_second = now->tm_sec;
}

/*
 * To caculate a year value is leapyear or not
 */ 
bool DateTime::IsLeapYear(int year) {
    if((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))
        return true;
    return false;
}
}