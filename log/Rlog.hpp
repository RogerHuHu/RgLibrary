/************************************************
 * @file Rlog.hpp
 * \brief 
 * @author Roger
 * @date 2016-08
 ***********************************************/
 
#ifndef _R_LOG_H_
#define _R_LOG_H_
 
#include <iostream>
#include <string>

using namespace file;
using namespace time;

class Directory;
class File;
class FileInfo;
class DateTime;
 
namespace log {
/***************************************
 * \brief log module
 * *************************************/
 
typedef enum LogAppendersType { 
    LOG_TERMINAL = 0, 
    LOG_FILE = 1 
} LogAppendersT_;

typedef enum LogInfoSourceType { 
    LOG_CODE = 0, 
    LOG_RESOURCE_FILE = 1 
} LogInfoSourceT_;

typedef enum LogLevelType { 
    LOG_DEBUG = 0,
    LOG_INFO = 1, 
    LOG_WARN = 2, 
    LOG_ERROE = 3, 
    LOG_FATAL = 4 
}  LogLevelT_;

extern const char *logLvlStr[5];

typedef enum LogErrorType {
    LOG_OK = 0,
    LOG_FILE_OPEN_FIALED = 1,
    FILE_EXISTS = 2,
    FILE_STREAM_ABNORMAL = 3,
    FILE_DELETE_FAIL = 4,
    FILE_RENAME_FAIL = 5,
    FILE_OPEN_FAIL = 6，
} LogErrorT_;
 
class Rlog {
public:
    /************************************************
     * \brief  Constructor
     * 
     * \param timeFormat     format of datetime in log content
     * \param appenders      specify where to store log content
     * \param logInfoSource  specify where the log information come from
     * \param maxBackupNum   max backup file number of rolling file
     * \param maxFileSize    max file size of log file
     ***********************************************/
    Rlog(const std::string &timeFormat, LogAppendersT_ appenders, LogInfoSourceT_ logInfoSource,
         int maxBackupNum = 0, size_t maxFileSize = 10 * 1024 * 1024);
    
    /************************************************
     * \brief Copy constuctor
     *
     * \param copy
     ***********************************************/
    Rlog(const Rlog &copy);
    
    /************************************************
     * \brief Destructor
     ***********************************************/
    ~Rlog();
    
    /************************************************
     * \brief It needs to open log appenders before record  
     *        started when the appender is file
     *        1.file
     *        2. ...
     * 
     * \return log appenders open result
     ***********************************************/
    LogErrorT_ RlogOpen();
    
    /************************************************
     * \brief It needs to close log appenders before record
     *        stopped when the appender is file
     *        1.file
     *        2. ...
     * 
     * \return log appenders close result
     ****0*******************************************/
    LogErrorT_ RlogClose();
    
    /************************************************
     * \brief Set resource file name
     * 
     * \param resourceFileName  name of resource file to set
     ***********************************************/
    void SetResourceFilePath(const std::string &resourceFileName) { 
            m_resourceFileName = resourceFileName; }
            
    /************************************************
     * \brief Get resource file name
     * 
     * \param return  name of resource file which has been set
     ***********************************************/
     std::string GetResourceFileName() const { return m_resourceFileName; }
     
     /************************************************
     * \brief Set name of file to record log information
     * 
     * \param logFileName  name of file to record log to set
     ***********************************************/
    void SetLogFileName(const std::string &logFileName) { 
            m_logFileName = logFileName; }
            
    /************************************************
     * \brief Get name of file to record log information
     * 
     * \param return  name of file to record log information
     ***********************************************/
     std::string GetLogFileName() const { return m_logFileName; }
     
    /************************************************
     * \brief Write log
     * 
     * \param logInfoCode  code of log information
     * \param level        log level
     ***********************************************/
     void RlogWrite(LogInfoSourceT_ logInfoCode, LogLevelT_ level);
     
    /************************************************
     * \brief Write log
     * 
     * \param logCode  code of log information
     * \param logInfo  log information
     * \param level    log level
     ***********************************************/
     void RlogWrite(int logCode, const std::string &logInfo, LogLevelT_ level);
     
     /************************************************
     * \brief Rollover log files
     ***********************************************/
     void RollOverFiles();
private:
    std::string m_timeFormat;         //format of datetime
    std::string m_resourceFileName;   //name of resource file
    std::string m_logFileName;        //name of file to record log information
    LogAppendersT_ m_appenders;       //where to store log information
    LogInfoSourceT_ m_logInfoSource;  //specify where the log information come from
    int m_maxBackupNum;               //max backup file number of rolling file
    size_t m_maxFileSize;             //max file size of log file
    
    Directory *dirObj;
    File *fileObj;
    FileInfo *fileInfoObj;
    DateTime *dateTimeObj;
};
}
 
 #endif //_R_LOG_H_