/************************************************
 * @file FileInfo.h
 * \brief 
 * @author Roger
 * @version V1.0.0
 * @date 2016-08
 ***********************************************/
 
#ifndef _FILE_INFO_H_
#define _FILE_INFO_H_

#include <sys/stat.h>
#include <string>

namespace file {
    
typedef enum FileInfoErrorType {
    OK = 0,
    FILE_NAME_EMPTY = 1,
    FILE_NOT_FOUND = 2,
    INVALID_PARAMETER = 3,
    UNEXPCETED_ERROR = 4,
} FileInfoErrorT_

/***************************************
 * \brief File information
 * *************************************/
class FileInfo {
public:
    /************************************************
     * \brief Default constructor
     ***********************************************/
    FileInfo() {}
    
    /************************************************
     * \brief Constructor
     * 
     * \param fileName  name of file to deal with 
     ***********************************************/
    FileInfo(const std::string &fileName);
    
    /************************************************
     * \brief Copy constructor
     * 
     * \param copy 
     ***********************************************/
    FileInfo(const FileInfo &copy);
    
    /************************************************
     * \brief Destructor
     ***********************************************/
    ~FileInfo();
    
    /************************************************
     * \brief Update file information
     ***********************************************/
    void Update();
    
    /************************************************
     * \brief Update file information
     * 
     * \param fileName  name of file to deal with 
     ***********************************************/
    void Update(const std::string &fileName);
    
    /************************************************
     * \brief Get file mode
     * 
     * \return this path is a file or a directory
     ***********************************************/
     unsigned short GetMode() const { return m_mode; }
     
     /************************************************
     * \brief Get file size
     * 
     * \return size of the file
     ***********************************************/
     unsigned long GetSize() const { return\m_size; }
     
     /************************************************
     * \brief Get last access time of the file
     * 
     * \return lase access time of the file
     ***********************************************/
     time_t GetLastAccessTime() const { return m_lastAccessTime; }
     
     /************************************************
     * \brief Get last modify time of the file
     * 
     * \return lase modify time of the file
     ***********************************************/
     time_t GetLastModifyTime() const { return m_lastModifyTime; }
     
     /************************************************
     * \brief Set last modify time of the file（invalid）
     * 
     * \param modifyTime  lase modify time to set
     * 
     * \return error code
     ***********************************************/
     FileInfoErrorT_ SetLastModifyTime(time_t modifyTime);
     
     /************************************************
     * \brief Get create time of the file
     * 
     * \return create time of the file
     ***********************************************/
     time_t GetCreateTime() const { return m_createTime; }
     
     /************************************************
     * \brief Get error code
     * 
     * \return error code
     ***********************************************/
     FileInfoErrorT_ GetErrorCode() const { return m_errorInfo; }
private:
    std::string m_fileName;
    unsigned short m_mode;     //文件、文件夹标志
    unsigned long m_size;      //文件大小
    time_t m_lastAccessTime;   //上次访问时间
    time_t m_lastModifyTime;   //上次修改时间
    time_t m_createTime;       //创建时间
    FileInfoErrorT_ m_errorInfo; //错误信息
};
}

#endif //_FILE_INF_H_