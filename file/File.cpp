/************************************************
 * @file File.h
 * \brief 
 * @author Roger
 * @version V1.0.0
 * @date 2016-08
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
    if(m_fs) 
        return OK;
    else
        return FILE_OPEN_FAIL;
}

/*
 * Close file
 */
void File::CloseFile() {
    if(m_fs.is_open()) m_fs.close();
}

/*
 * Read file to int 
 */
FileErrorT_ File::Read(int *out) {
    if(m_fs.good())
        m_fs >> *out;
    else
        return FILE_STREAM_ABNORMAL;
    return OK;
}

/*
 * Read file to long 
 */
FileErrorT_ File::Read(long *out) {
    if(m_fs.good())
        m_fs >> *out;
    else
        return FILE_STREAM_ABNORMAL;
    return OK;
}

/*
 * Read file to string 
 */
FileErrorT_ File::Read(std::string &out) {
    if(m_fs.good()) {
        string temp;
        while(getline(m_fs, temp))
            out += temp;
    } else {
        return FILE_STREAM_ABNORMAL;
    }
    return OK;
}

/*
 * Write int to file
 */
FileErrorT_ File::Write(int in) {
    if(m_fs.good())
        m_fs << in;
    else
        return FILE_STREAM_ABNORMAL;
    return OK;
}

/*
 * Write long to file
 */
FileErrorT_ File::Write(long in) {
    if(m_fs.good())
        m_fs << in;
    else
        return FILE_STREAM_ABNORMAL;
    return OK;
}

/*
 * Write string to file
 */
FileErrorT_ File::Write(const std::string &in) {
    if(m_fs.good())
        m_fs << in;
    else
        return FILE_STREAM_ABNORMAL;
    return OK;
}

/*
 * Delete file 
 */
FileErrorT_ File::Delete() {
    return Delete(m_fileName);
}

/*
 * Delete file 
 */
FileErrorT_ File::Delete(const std::string &fileName) {
    if(remove(fileName.c_str()) == 0) return OK;
    return FILE_DELETE_FAIL;
}

/*
 * Rename file 
 */
FileErrorT_ File::Rename(const std::string &newName) {
    return Rename(m_fileName, newName);
}

/*
 * Rename file 
 */
FileErrorT_ File::Rename(const std::string &oldName, const std::string &newName) {
    if(rename(oldName.c_str(), newName.c_str()) == 0) {
        return OK;
    } else {
        return FILE_RENAME_FAIL;
    }
}

/*
 * Copy file 
 */
FileErrorT_ File::Copy(const std::string &dstFileName) {
    
}

/*
 * Copy file 
 */
FileErrorT_ File::Copy(File *dstFile) {
    FileErrorT_ errCode = OpenFile();
    if(errCode != OK) return errCode;
    errCode = dstFile->OpenFile();
    if(errCode != OK) return errCode;
    
    if(!m_fs.good() || !dstFile->m_fs.good()) {
        CloseFile();
        dstFile->CloseFile();
        return FILE_STREAM_ABNORMAL;
    }
    
}
}
