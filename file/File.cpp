/************************************************
 * @file File.cpp
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
File::File(const std::string &fileName) : 
            m_fileName(fileName), m_isOpened(false) {
}

/*
 * Construstor
 */
File::File(const std::string &fileName, std::ios_base::openmode mode) :
            m_fileName(fileName), m_openMode(mode), m_isOpened(false) {    }
            
/*
 * Copy constructor
 */
File::File(const File &copy) {
    //m_fs = copy.m_fs;
    m_fileName = copy.m_fileName;
    //m_openMode = copy.m_openMode;
    m_isOpened = copy.m_isOpened;
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
    return (access(fileName.c_str(), F_OK) == 0); 
}

/*
 * Check whether a file is occupied
 */
bool File::FileOccupied() {
    return FileOccupied(m_fileName);
}

/*
 * Check whether a file is occupied 
 */
bool File::FileOccupied(const std::string &fileName) {
    bool result = false;
    if(OpenFile(fileName, std::ios_base::out) != FILE_OK) 
        result = true;
    return result;
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
FileErrorT_ File::OpenFile() {
    return OpenFile(m_fileName, m_openMode);
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
    m_fs.open(fileName.c_str(), mode);
    if(m_fs) {
        m_isOpened = true;
        return FILE_OK;
    } else {
        m_isOpened = false;
        return FILE_OPEN_FAIL;
    }
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
    return FILE_OK;
}

/*
 * Read file to long 
 */
FileErrorT_ File::Read(long *out) {
    if(m_fs.good())
        m_fs >> *out;
    else
        return FILE_STREAM_ABNORMAL;
    return FILE_OK;
}

/*
 * Read file to string 
 */
FileErrorT_ File::Read(std::string &out) {
    if(m_fs.good()) {
        std::string temp;
        while(getline(m_fs, temp))
            out += temp;
    } else {
        return FILE_STREAM_ABNORMAL;
    }
    return FILE_OK;
}

/*
 * Write int to file
 */
FileErrorT_ File::Write(int in) {
    if(m_fs.good())
        m_fs << in;
    else
        return FILE_STREAM_ABNORMAL;
    return FILE_OK;
}

/*
 * Write long to file
 */
FileErrorT_ File::Write(long in) {
    if(m_fs.good())
        m_fs << in;
    else
        return FILE_STREAM_ABNORMAL;
    return FILE_OK;
}

/*
 * Write string to file
 */
FileErrorT_ File::Write(const std::string &in) {
    if(m_fs.good())
        m_fs << in;
    else
        return FILE_STREAM_ABNORMAL;
    return FILE_OK;
}

/*
 * Write int to file, one line per write
 */
FileErrorT_ File::WriteLine(int in) {
    if(m_fs.good())
        m_fs << in << std::endl;
    else
        return FILE_STREAM_ABNORMAL;
    return FILE_OK;
}

/*
 * Write long to file, one line per write
 */
FileErrorT_ File::WriteLine(long in) {
    if(m_fs.good())
        m_fs << in << std::endl;
    else
        return FILE_STREAM_ABNORMAL;
    return FILE_OK;
}

/*
 * Write string to file, one line per write
 */
FileErrorT_ File::WriteLine(const std::string &in) {
    if(m_fs.good())
        m_fs << in << std::endl;
    else
        return FILE_STREAM_ABNORMAL;
    return FILE_OK;
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
    if(remove(fileName.c_str()) == 0) return FILE_OK;
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
        return FILE_OK;
    } else {
        return FILE_RENAME_FAIL;
    }
}

/*
 * Copy file 
 */
FileErrorT_ File::Copy(const std::string &dstFileName) {
    return Copy(new File(dstFileName, std::ios_base::in)); 
}

/*
 * Copy file 
 */
FileErrorT_ File::Copy(File *dstFile) {
    FileErrorT_ errCode = OpenFile();
    if(errCode != FILE_OK) return errCode;
    errCode = dstFile->OpenFile();
    if(errCode != FILE_OK) return errCode;
    
    //Check whether source and destination file stream is good
    if(!m_fs.good() || !dstFile->m_fs.good()) {
        CloseFile();
        dstFile->CloseFile();
        return FILE_STREAM_ABNORMAL;
    }

    dstFile->m_fs << m_fs.rdbuf();
    CloseFile();
    dstFile->CloseFile();
    return FILE_OK;
}

/*
 * Move file 
 */
FileErrorT_ File::Move(const std::string &dstFileName) {
    return FILE_OK;
}

/*
 * Move file 
 */
FileErrorT_ File::Move(File *dstFile) {
    return FILE_OK;
}

}
