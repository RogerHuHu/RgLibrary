/************************************************
 * @file FileInfo.h
 * \brief 
 * @author Roger
 * @version V1.0.0
 * @date 2016-08
 ***********************************************/
 
#include "FileInfo.hpp"
 
namespace file {
/*
 * Construstor
 */
FileInfo::FileInfo(const std::string &fileName) : m_fileName(fileName) {
    struct _stat fileInfo;
    int result = _stat(m_fileName.c_str(), &fileInfo);
    if(result == 0) {
        m_mode = fileInfo.st_mode;
        m_size = fileInfo.st_size;
        m_lastAccessTime = fileInfo.st_atime;
        m_lastModifyTime = fileInfo.st_mtime;
        m_createTime = fileInfo.st_ctime;
        m_errorInfo = OK；
    } else {
        switch(errno) {
            case ENOENT: m_errorInfo = FILE_NOT_FOUND; break;
            case EINVAL: m_errorInfo = INVALID_PARAMETER; break;
            default: m_errorInfo = UNEXPCETED_ERROR; break;
        }
    }
}

/*
 * Copy constructor
 */
FileInfo::FileInfo(const FileInfo &copy) {
    m_fileName = copy.m_fileName;
    m_mode = copy.m_mode;
    m_size = copy.m_size;
    m_lastAccessTime = copy.m_lastAccessTime;
    m_lastModifyTime = copy.m_lastModifyTime;
    m_createTime = copy.m_createTime;
}

/*
 * Destructor
 */
FileInfo::~FileInfo() {
}
}