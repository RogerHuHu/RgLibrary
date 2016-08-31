/************************************************
 * @file DateTime.cpp
 * \brief 
 * @author Roger
 * @version V1.0.0
 * @date 2016-07
 ***********************************************/
 
#include <iostream>
#include <string.h>
#include "DateTime.hpp"

using namespace std::chrono;

namespace rtime {
/*
 * Constructor
 */ 
DateTime::DateTime(const std::string &format) : m_format(format), 
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
 * Convert from struct tm to seconds from 1970-01-01
 */ 
time_t DateTime::ToSecondsFrom1970_1_1(struct tm tm_time) {
    return mktime(&tm_time);
}

/*
 * Get current seconds from 1970-01-01
 */ 
time_t DateTime::GetSecondsFrom1970_1_1() {
    system_clock::time_point tp = system_clock::now();
    return system_clock::to_time_t(tp);
}

/*
 * Get current UTC time
 */ 
struct tm DateTime::GetCurrentUTCTime() {
    time_t tt = GetSecondsFrom1970_1_1();
    struct tm *_time = gmtime(&tt);
    return *_time;
}

/*
 * Get current UTC time
 */ 
std::string DateTime::GetCurrentUTCTime(const char *format) {
    struct tm localTime = GetCurrentUTCTime();
    return ToString(format, localTime);
}

/*
 * Get current local time
 */ 
struct tm DateTime::GetCurrentLocalTime() {
    time_t tt = GetSecondsFrom1970_1_1();
    struct tm *_time = localtime(&tt);
    return *_time;
}

/*
 * Get current local time
 */ 
std::string DateTime::GetCurrentLocalTime(const char *format) {
    struct tm localTime = GetCurrentLocalTime();
    return ToString(format, localTime);
}

/*
 * Convert from tm to string
 */
std::string DateTime::ToString(const char *format, struct tm tm_time) {
    char buf[64] = {0};
    strftime(buf, 64, format, &tm_time);
    std::string result = buf;
    return result;
}

/*
 * Convert time format from struct tm to normal 
 * year, month, day, hour, minute, second
 */ 
void DateTime::ConvertFormat(struct tm tm_time) {
    m_year = tm_time.tm_year + 1900;
    m_month = tm_time.tm_mon + 1;
    m_day = tm_time.tm_mday;
    m_hour = tm_time.tm_hour;
    m_minute = tm_time.tm_min;
    m_second = tm_time.tm_sec;
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
