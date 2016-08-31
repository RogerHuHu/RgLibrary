/************************************************
 * @file Rlog.cpp
 * \brief 
 * @author Roger
 * @version V1.1.0
 * @date 2016-08
 ***********************************************/

#include <sstream>
#include "Rlog.hpp"

namespace log {

const char *logLvlStr[] = 
{
    " DEBUG ",
    " INFO ",
    " WARN ",
    " ERROR ",
    " FATAL "
};

/*
 * Construstor
 */
Rlog::Rlog(const std::string &timeFormat, LogAppendersT_ appenders, 
           LogInfoSourceT_ logInfoSource, int maxBackupNum = 0, 
           size_t maxFileSize = 10 * 1024 * 1024) 
           : m_timeFormat(timeFormat),
             m_appenders(appenders),
             m_logInfoSource(logInfoSource),
             m_maxBackupNum(maxBackupNum),
             m_maxFileSize(maxFileSize) {
    
}

/*
 * Construstor
 */
Rlog::Rlog(const Rlog &copy) {
    m_timeFormat = copy.m_timeFormat;
    m_resourceFileName = copy.m_resourceFileName;
    m_logFileName = copy.m_logFileName;
    m_appenders = copy.m_appenders;
    m_logInfoSource = copy.m_logInfoSource;
}
 
/*
 * Destrustor
 */
Rlog::~Rlog() {
}

/*
 * It needs to close log appenders before record
 * stopped when the appender is file
 * 1.file
 * 2. ...
 */
LogErrorT_ Rlog::RlogOpen() {
    LogErrorT_ result = LOG_OK;
    switch(m_appenders) {
        case LOG_TERMINAL :
        break;
        case LOG_FILE : {
            fileObj = new File(m_logFileName, std::ios_base::app);
            if(fileObj->OpenFile() != FILE_OK) {
                delete fileObj;
                fileObj = NULL;
                result = LOG_FILE_OPEN_FIALED;
            }
            dateTimeObj = new DateTime(m_timeFormat);
            fileInfoObj = new FileInfo(m_logFileName);
            result = LOG_OK;
        }
        break;
        default:
        break;
    }
    return result;
}

/*
 * It needs to close log appenders before record
 * stopped when the appender is file
 * 1.file
 * 2. ...
 */
LogErrorT_ Rlog::RlogClose() {
    LogErrorT_ result = LOG_OK;
    switch(m_appenders) {
        case LOG_TERMINAL :
        break;
        case LOG_FILE : {
            if(fileObj != NULL) {
                fileObj->CloseFile();
                delete fileObj;
                fileObj = NULL;
            }
            if(dateTimeObj != NULL) {
                delete dateTimeObj;
                dateTimeObj = NULL;
            }
            if(fileInfoObj != NULL) {
                delete dateTimeObj;
                fileInfoObj = NULL;
            }
            result = LOG_OK;
        }
        break;
        default:
        break;
    }
}

/*
 * Write log
 */
void Rlog::RlogWrite(LogInfoSourceT_ logInfoCode, LogLevelT_ level) {
}

/*
 * Write log
 */
void Rlog::RlogWrite(int logCode, const std::string &logInfo, LogLevelT_ level) {
    switch(m_appenders) {
        case LOG_TERMINAL : {
            std::cout << dateTimeObj->GetCurrentLocalTime(m_timeFormat.c_str()) << 
            " " << 
            logLvlStr[level] << 
            logCode <<
            logInfo << 
            std::endl;
        }
        break;
        case LOG_FILE : {
            if(fileObj != NULL) {
                fileInfoObj->Update();
                if(fileInfoObj->GetSize() > m_maxFileSize) {
                    fileObj->CloseFile();
                    RollOverFiles();
                    fileObj->OpenFile(std::ios_base::trunc | std::ios_base::app);
                }
                std::stringstream stream;
                stream << dateTimeObj->GetCurrentLocalTime(m_timeFormat.c_str()) << 
                          " " <<
                          logLvlStr[level] <<
                          logCode <<
                          logInfo << std::endl;
                fileObj->WriteLine(stream.str());
            }
        }
        break;
        default : 
        break;
    }
}

/*
 * Rollover log files
 */
void Rlog::RollOverFiles() {
    std::stringstream ss;
    ss << m_logFileName << "." << m_maxBackupNum;
    if(fileObj->FileExists(ss.str()))
        fileObj->Delete(ss.str());
    
    std::stringstream ssSrc;
    std::stringstream ssDst;
    std::string srcFileName;
    std::string dstFileName;
    
    //rolling backup files
    for(int i = m_maxBackupNum - 2; i >= 0; --i) {
        ssSrc << m_logFileName << "." << i;
        ssDst << m_logFileName << "." << (i + 1);
        srcFileName = "";
        dstFileName = "";
        srcFileName = ssSrc.str();
        dstFileName = ssDst.str();
        if(fileObj->FileExists(dstFileName))
            fileObj->Delete(dstFileName);
        if(fileObj->FileExists(srcFileName))
            fileObj->Rename(srcFileName, dstFileName);
    }
    
    //rolling formal file
    if(fileObj->FileExists(srcFileName))
        fileObj->Delete(srcFileName);
    if(fileObj->FileExists(m_logFileName))
        fileObj->Rename(m_logFileName, srcFileName);
}

}