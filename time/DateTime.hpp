/************************************************
 * @file DateTime.hpp
 * \brief 
 * @author Roger
 * @version V1.0.0
 * @date 2016-07
 ***********************************************/

#ifndef _DATE_TIME_H_
#define _DATE_TIME_H_

#include <ctime>

#if (defined _linux) || (defined _unix)
#include <sys/time.h>
#endif

#if (defined _WIN32) || (defined _WIN64) 
#include <time.h>
#endif

#include <string>
#include <chrono>

namespace rtime {

/***************************************
 * \brief Date time
 * *************************************/
    
class DateTime {
    public:
    /************************************************
     * \brief Constructor
     * 
     * \param format  format of datetime
     ***********************************************/
    DateTime(const std::string &format);
    
    /************************************************
     * \brief Constructor
     * 
     * \param year
     * \param month
     * \param day
     * \param hour
     * \param minute
     * \param second
     ***********************************************/
    DateTime(int year, int month, int day, int hour, int minute, int second);
    
    /************************************************
     * \brief Destructor
     ***********************************************/
    ~DateTime() {}
    
    /************************************************
     * \brief Set year value
     * 
     * \param year  the year value to set
     ***********************************************/
    void SetYear(int year) { m_year = year; }
    
    /************************************************
     * \brief Get year value
     * 
     * \return the year value
     ***********************************************/
    int GetYear() const { return m_year; }
    
    /************************************************
     * \brief Set month value
     * 
     * \param month  the month value to set
     ***********************************************/
    void SetMonth(int month) { m_month = month; }
    
    /************************************************
     * \brief Get month value
     * 
     * \return the month value
     ***********************************************/
    int GetMonth() const { return m_month; }
    
    /************************************************
     * \brief Set day value
     * 
     * \param day  the day value to set
     ***********************************************/
    void SetDay(int day) { m_day = day; }
    
    /************************************************
     * \brief Get day value
     * 
     * \return the day value
     ***********************************************/
    int GetDay() const { return m_day; }
    
    /************************************************
     * \brief Set hour value
     * 
     * \param hour  the hour value to set
     ***********************************************/
    void SetHour(int hour) { m_hour = hour; }
    
    /************************************************
     * \brief Get hour value
     * 
     * \return the hour value
     ***********************************************/
    int GetHour() const { return m_hour; }
    
    /************************************************
     * \brief Set minute value
     * 
     * \param minute  the minute value to set
     ***********************************************/
    void SetMinute(int minute) { m_minute = minute; }
    
    /************************************************
     * \brief Get minute value
     * 
     * \return the minute value
     ***********************************************/
    int GetMinute() const { return m_minute; }
    
    /************************************************
     * \brief Set second value
     * 
     * \param second  the second value to set
     ***********************************************/
    void SetSecond(int second) { m_second = second; }
    
    /************************************************
     * \brief Get second value
     * 
     * \return the second value
     ***********************************************/
    int GetSecond() const { return m_second; }
    
    /************************************************
     * \brief Convert from struct tm to seconds from 1970-01-01
     *
     * \return seconds from 1970-01-01
     *************************************************/
    time_t ToSecondsFrom1970_1_1(struct tm tm_time);

    /************************************************
     * \brief Get current seconds from 1970-01-01
     *
     * \return seconds from 1970-01-01
     *************************************************/
    time_t GetSecondsFrom1970_1_1();
    
    /************************************************
     * \brief Get current UTC time
     * 
     * \return current UTC time struct
     *************************************************/
    struct tm GetCurrentUTCTime();

    /************************************************
     * \brief Get current UTC time
     *
     * \param format  time format
     * 
     * \return current UTC time string
     *************************************************/
    std::string GetCurrentUTCTime(const char *format);
    
    /************************************************
     * \brief Get current local time
     * 
     * \return current local time struct
     *************************************************/
    struct tm GetCurrentLocalTime();

    /************************************************
     * \brief Get current local time
     *
     * \param format
     * 
     * \return current local time string
     *************************************************/
    std::string GetCurrentLocalTime(const char *format);

    /************************************************
     * \brief Convert from ::tm to string
     *
     * \param format   time string format
     * \param tm_time  time struct
     * 
     * \return 
     *************************************************/
    std::string ToString(const char *format, struct tm tm_time);

    /************************************************
     * \brief Convert time format from ::tm to normal 
     * year, month, day, hour, minute, second
     *
     * \param tm_time  
     *************************************************/
    void ConvertFormat(struct tm tm_time);
    
    /************************************************
     * \brief To caculate a year value is leapyear or not
     * 
     * \param year  the year value
     * 
     * \return the year is leapyear or not
     ***********************************************/
    bool IsLeapYear(int year);
private:
    std::string m_format;  //format of datetime
    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    int m_minute;
    int m_second;
    struct tm m_tm_time;
};
}

#endif //_DATE_TIME_H_
