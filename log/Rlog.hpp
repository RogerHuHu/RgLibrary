/************************************************
 * @file Rlog.hpp
 * \brief 
 * @author Roger
 * @version V1.1.0
 * @date 2016-07
 ***********************************************/
 
#ifndef _R_LOG_H_
#define _R_LOG_H_
 
#include <iostream>

using namespace file;
class Directory;
class File;
class FileInfo;
 
namespace log {
/***************************************
 * \brief log module
 * *************************************/
 
enum APPENDERS { TERMINAL = 0, FILE = 1 };
enum LOG_INFO_SOURCE { CODE = 0, RESOURCE_FILE = 1 };
enum LOG_LEVEL { DEBUG = 0, INFO = 1, WARN = 2, ERROE = 3, FATAL = 4 };

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
     * \param  timeFormat     format of datetime in log content
     * \param  appenders      specify where to store log content
     * \param  logInfoSource  specify where the log information come from
     ***********************************************/
    Rlog(const std::string &timeFormat, int appenders, int logInfoSource);
    
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
     ***********************************************/
    LogErrorT_ RlogClose();
    
    /************************************************
     * \brief Set resource file path
     * 
     * \param resourceFilePath  path of resource file to set
     ***********************************************/
    void SetResourceFilePath(const std::string &resourceFilePath) { 
            m_resourceFilePath = resourceFilePath; }
            
    /************************************************
     * \brief Get resource file path
     * 
     * \param return  path of resource file which has been set
     ***********************************************/
     std::string GetResourceFilePath() const { return m_resourceFilePath; }
     
     /************************************************
     * \brief Set path of file to record log information
     * 
     * \param logFilePath  path of file to record log to set
     ***********************************************/
    void SetLogFilePath(const std::string &logFilePath) { 
            m_logFilePath = logFilePath; }
            
    /************************************************
     * \brief Get path of file to record log information
     * 
     * \param return  path of file to record log information
     ***********************************************/
     std::string GetLogFilePath() const { return m_logFilePath; }
     
     /************************************************
     * \brief Write debug log
     * 
     * \param logInfoCode  code of log information
     ***********************************************/
     void RlogDebug(int logInfoCode);
     
     /************************************************
     * \brief Write debug log
     * 
     * \param logInfo  log information
     ***********************************************/
     void RlogDebug(const std::string &logInfo);
private:
    std::string m_timeFormat;        //format of datetime
    std::string m_resourceFilePath;  //path of resource file
    std::string m_logFilePath;       //path of file to record log information
    int m_appenders;                 //where to store log information
    int m_logInfoSource;             //specify where the log information come from
    
    Directory *dirObj;
    File *fileObj;
    FileInfo *fileInfoObj;
};
}
 
 #endif //_R_LOG_H_