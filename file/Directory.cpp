/************************************************
 * @file Directory.cpp
 * \brief 
 * @author Roger
 * @version V1.0.0
 * @date 2016-08
 ***********************************************/
 
 #include "Directory.hpp"

namespace file {
/*
 * Construstor
 */
Directory::Directory(const std::string &dirName) : m_dirName(dirName) {
}

/*
 * Copy constructor
 */
Directory::Directory(const Directory &copy) {
    m_dirName = copy.m_dirName;
}

/*
 * Destructor
 */
Directory::~Directory() {
}

/*
 * Check whether a directory is exists
 */
bool Directory::DirectoryExists() {
    return DirectoryExists(m_dirName);
}

/*
 * Check whether a directory is exists 
 */
bool Directory::DirectoryExists(const std::string &dirName) {
    return (access(dirName.c_str(), F_OK) == 0); 
}

/*
 * Create an empty directory
 */
DirErrorT_ Directory::CreateDirectory() {
    return CreateDirectory(m_dirName);
}

/*
 * Create an empty directory
 */
DirErrorT_ Directory::CreateDirectory(const std::string &dirName) {
    if(dirName.empty()) return DIR_NAME_EMPTY;
    if(DirectoryExists(dirName)) return DIR_EXISTS;
    std::string tempPath = "";
    std::string::size_type left, right;
    for(left = 0, right = 1; right < dirName.size(); ++right) {
        if(dirName.at(right) == '/') {
            tempPath = dirName.substr(left, right);
            if(!DirectoryExists(tempPath))
                mkdir(tempPath.c_str());
        } else if(dirName.at(right) == '\\') {
            tempPath = dirName.substr(left, right);
            ++right;
            if(!DirectoryExists(tempPath))
                mkdir(tempPath.c_str());
        }
    }
    return DIR_OK;
}

}