/************************************************
 * @file Rlog.cpp
 * \brief 
 * @author Roger
 * @version V1.1.0
 * @date 2016-08
 ***********************************************/

#include <sstream>
#include "Rlog.hpp"
#include "Directory.hpp"
#include "File.hpp"
#include "FileInfo.hpp"

namespace log {
/*
 * Construstor
 */
Rlog::Rlog(const std::string &timeFormat, int appenders, int logInfoSource,
           int maxBackupNum = 0, size_t maxFileSize = 10 * 1024 * 1024) ：
                                                        m_timeFormat(timeFormat),
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
    m_resourceFilePath = copy.m_resourceFilePath;
    m_logFilePath = copy.m_logFilePath;
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
        case TERMINAL :
        break;
        case FILE : {
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
        case TERMINAL :
        break;
        case FILE : {
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
void Rlog::RlogWrite(int logInfoCode, LOG_LEVEL level) {
}

/*
 * Write log
 */
void Rlog::RlogWrite(const std::string &logInfo, LOG_LEVEL level) {
    switch(m_appenders) {
        case TERMINAL : {
            std::cout << dateTimeObj->GetCurrentLocalTime() << 
            log_lvl_str[level] << 
            logInfo << 
            std::endl;
        }
        break;
        case FILE : {
            fileInfoObj->Update();
            if(fileInfoObj->GetSize() > m_maxFileSize) {
                fileObj->CloseFile();
                RollOverFiles();
                fileObj->OpenFile(std::ios_base::trunc | std::ios_base::app);
            }
            fileObj->WriteLen(dateTimeObj->GetCurrentLocalTime() + 
                           log_lvl_str[level] +
                           logInfo);
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