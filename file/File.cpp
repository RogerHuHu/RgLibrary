/************************************************
 * @file File.h
 * \brief 
 * @author Roger
 * @version V1.0.0
 * @date 2016-07
 ***********************************************/

#include "File.hpp"

namespace file {
/*
 * Construstor
 */
File::File(const std::string &fileName) : m_fileName(fileName) {
}

/*
 * Construstor
 */
File::File(const std::string &fileName, std::ios_base::openmode mode) :
            m_fileName(fileName), m_openmode(mode) {    }
            
/*
 * Copy constructor
 */
File::File(const File &copy) {
    m_fs = copy.m_fs;
    m_fileName = copy.m_fileName;
    m_openmode = copy.m_openmode;
}

/*
 * Destructor
 */
File::~File() {
}

/*
 * Check whether a file is exists
 */
bool File::FileExists() {
    return FileExists(m_fileName);
}

/*
 * Check whether a file is exists 
 */
bool File::FileExists(const std::string &fileName) {
    return (access(fileName.c_str(), 0) == 0); 
}

/*
 * Create an empty file
 */
FileErrorT_ File::CreateFile() {
    return CreateFile(m_fileName);
}

/*
 * Create an empty file
 */
FileErrorT_ File::CreateFile(const std::string &fileName) {
    if(fileName.empty()) return FILE_NAME_EMPTY;
    if(FileExists(fileName)) return FILE_EXISTS;
    FileErrorT_ openResult = OpenFile(fileName, std::ios_base::out);
    CloseFile();
    return openResult;
}

/*
 * Open file
 */
FileErrorT_ File::OpenFile(std::ios_base::openmode mode) {
    return OpenFile(m_fileName, mode);
}

/*
 * Open file
 */
FileErrorT_ File::OpenFile(const std::string &fileName, std::ios_base::openmode mode) {
    if(fileName.empty()) return FILE_NAME_EMPTY;
    m_fs.open(fileName, mode);
    if(m_fs.good()) 
        return OK;
    else
        return FILE_STREAM_ABNORMAL;
}

/*
 * Close File
 */
void File::CloseFile() {
    if(m_fs.is_open()) m_fs.close();
}
}
