/************************************************
 * @file File.h
 * \brief 
 * @author Roger
 * @version V1.0.0
 * @date 2016-07
 ***********************************************/

#ifndef _FILE_H_
#define _FILE_H_

#include <fstream>
#include <string>
#include <io.h>

namespace file {

typedef enum FileErrorType {
    OK = 0;
    FILE_NAME_EMPTY = 1;
    FILE_EXISTS = 2;
    FILE_STREAM_ABNORMAL = 3;
} FileErrorT_

/***************************************
 * \brief File operations
 * *************************************/
    
class File {
public:
    /************************************************
     * \brief Constructor
     * 
     * \param fileName  name of file to deal with 
     ***********************************************/
    File(const std::string &fileName);

    /************************************************
     * \brief Constructor
     * 
     * \param fileName  name of file to deal with
     * \param mode      file open mode
     ***********************************************/
    File(const std::string &fileName, std::ios_base::openmode mode);

    /************************************************
     * \brief Copy constructor
     * 
     * \param copy 
     ***********************************************/
    File(const File &copy);

    /************************************************
     * \brief Destructor
     ***********************************************/
    ~File();
    
    /************************************************
     * \brief Check whether a file is exists
     *
     * \return file exists or not
     ***********************************************/
    bool FileExists();

    /************************************************
     * \brief Check whether a file is exists
     *
     * \param fileName  name of file
     *
     * \return file exists or not
     ***********************************************/
    bool FileExists(const std::string &fileName);

    /************************************************
     * \brief Create an empty file 
     *
     * \return create result
     ***********************************************/
    FileErrorT_ CreateFile();

    /************************************************
     * \brief Create an empty file
     *
     * \param fileName  name of the file to create
     *
     * \return create result
     ***********************************************/
    FileErrorT_ CreateFile(const std::string &fileName);

    /************************************************
     * \brief Open file 
     *
     * \paran mode      file open mode
     *
     * \return open resut
     ***********************************************/
    FileErrorT_ OpenFile(std::ios_base::openmode mode);

    /************************************************
     * \brief Open file 
     *
     * \param fileName  name of file to open
     * \paran mode      file open mode
     *
     * \return open resut
     ***********************************************/
    FileErrorT_ OpenFile(const std::string &fileName, std::ios_base::openmode mode);

    /************************************************
     * \brief Close file 
     ***********************************************/
    void CloseFile();
private:
    std::fstream m_fs;
    std::string m_fileName;
    std::ios_base m_openmode;
};
}

#endif //_FILE_H_

