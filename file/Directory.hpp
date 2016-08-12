/************************************************
 * @file Directory.h
 * \brief 
 * @author Roger
 * @version V1.0.0
 * @date 2016-08
 ***********************************************/
 
#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include <string>

namespace file {
    
typedef enum DirErrorType {
    OK = 0,
    DIR_NAME_EMPTY = 1,
    DIR_EXISTS = 2,
    DIR_DELETE_FAIL = 3,
    DIR_RENAME_FAIL = 4,
} DirErrorT_;

/***************************************
 * \brief Directory operations
 * *************************************/
class Directory {
public:
    /************************************************
     * \brief Default Constructor
     ***********************************************/
    Directory() {}
    
    /************************************************
     * \brief Constructor
     * 
     * \param dirName  name of directory to deal with 
     ***********************************************/
    Directory(const std::string &dirName);
    
    /************************************************
     * \brief Copy constructor
     * 
     * \param copy 
     ***********************************************/
    Directory(const Directory &copy);
    
    /************************************************
     * \brief Destructor
     ***********************************************/
    ~Directory();

    /************************************************
     * \brief Check whether a directory is exists
     *
     * \return directory exists or not
     ***********************************************/
    bool DirectoryExists();

    /************************************************
     * \brief Check whether a directory is exists
     *
     * \param dirName  name of directory
     *
     * \return directory exists or not
     ***********************************************/
    bool DirectoryExists(const std::string &dirName);
    
    /************************************************
     * \brief Create an empty directory 
     *
     * \return create result
     ***********************************************/
    DirErrorT_ CreateDirectory();

    /************************************************
     * \brief Create an empty directory
     *
     * \param dirName  name of the directory to create
     *
     * \return create result
     ***********************************************/
    DirErrorT_ CreateDirectory(const std::string &dirName);
private:
    std::string m_dirName;
};

}

#endif  //_DIRECTORY_H_