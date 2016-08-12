/************************************************
 * @file Rlog.cpp
 * \brief 
 * @author Roger
 * @version V1.1.0
 * @date 2016-08
 ***********************************************/
 
#include "Rlog.hpp"
#include "Directory.hpp"
#include "File.hpp"
#include "FileInfo.hpp"

namespace log {
/*
 * Construstor
 */
Rlog::Rlog(const std::string &timeFormat, int appenders, int logInfoSource) ：
                                                        m_timeFormat(timeFormat),
                                                        m_appenders(appenders),
                                                        m_logInfoSource(logInfoSource) {
    
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
    if(m_appenders == TERMINAL) {
    } else if(m_appenders == FILE) {
        fileObj = new File(m_logFilePath, std::ios_base::app);
        if(fileObj->OpenFile() != FILE_OK) {
            delete fileObj;
            return LOG_FILE_OPEN_FIALED;
        }
        return LOG_OK;
    }
}

}