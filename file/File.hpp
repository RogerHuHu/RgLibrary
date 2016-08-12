/************************************************
 * @file File.h
 * \brief 
 * @author Roger
 * @version V1.0.0
 * @date 2016-08
 ***********************************************/

#ifndef _FILE_H_
#define _FILE_H_

#include <fstream>
#include <string>
#include <io.h>

namespace file {

typedef enum FileErrorType {
    FILE_OK = 0,
    FILE_NAME_EMPTY = 1,
    FILE_EXISTS = 2,
    FILE_STREAM_ABNORMAL = 3,
    FILE_DELETE_FAIL = 4,
    FILE_RENAME_FAIL = 5,
    FILE_OPEN_FAIL = 6，
} FileErrorT_;

/***************************************
 * \brief File operations
 * *************************************/
    
class File {
public:
    /************************************************
     * \brief Default Constructor
     ***********************************************/
    File() {}
    
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
     *        std::ios_base::in      open a file in readonly mode, create first 
     *                               when the file is not exsits
     *        std::ios_base::out     open a file in writeonly mode, create first 
     *                               when the file is not exsits, else clear it's
     *                               content
     *        std::ios_base::ate     open a file and move the pointer to the end of this file
     *        std::ios_base::app     open a file in append mode, create first 
     *                               when the file is not exsits
     *        std::ios_base::trunc   if the file to open exsits,delete it first
     *        std::ios_base::binary  open a file in binary mode
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
     * \brief Check whether a file is occupied
     *
     * \return file occupied or not
     ***********************************************/
    bool FileOccupied();

    /************************************************
     * \brief Check whether a file is occupied
     *
     * \param fileName  name of file
     *
     * \return file occupied or not
     ***********************************************/
    bool FileOccupied(const std::string &fileName);
    
    /************************************************
     * \brief Get file open status
     *
     * \return file opened or not
     ***********************************************/
    bool IsOpened() const { return m_isOpened; }

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
     * \return open resut
     ***********************************************/
    FileErrorT_ OpenFile();
    
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
    
    /************************************************
     * \brief Read file to int 
     *
     * \param out  file content
     *
     * \return read resut
     ***********************************************/
     FileErrorT_ Read(int *out);
     
    /************************************************
     * \brief Read file to long 
     *
     * \param out  file content
     *
     * \return read resut
     ***********************************************/
     FileErrorT_ Read(long *out);
     
    /************************************************
     * \brief Read file to string 
     *
     * \param out  file content
     *
     * \return read resut
     ***********************************************/
     FileErrorT_ Read(std::string &out);
     
    /************************************************
     * \brief Write int to file 
     *
     * \param int  data to write
     *
     * \return write resut
     ***********************************************/
     FileErrorT_ Write(int in);
     
    /************************************************
     * \brief Write long to file 
     *
     * \param int  data to write
     *
     * \return write resut
     ***********************************************/
     FileErrorT_ Write(long in);
     
    /************************************************
     * \brief Write string to file 
     *
     * \param int  data to write
     *
     * \return write resut
     ***********************************************/
     FileErrorT_ Write(const std::string &in);
     
    /************************************************
     * \brief Delete file 
     *
     * \param int  data to write
     *
     * \return delete resut
     ***********************************************/
     FileErrorT_ Delete();
     
    /************************************************
     * \brief Delete file 
     *
     * \param fileName  name of file to delete
     *
     * \return delete resut
     ***********************************************/
     FileErrorT_ Delete(const std::string &fileName);
     
    /************************************************
     * \brief Rename file 
     *
     * \param newName  new file name
     *
     * \return rename resut
     ***********************************************/
     FileErrorT_ Rename(const std::string &newName);
     
    /************************************************
     * \brief Rename file 
     *
     * \param oldName  old file name
     * \param newName  new file name
     *
     * \return rename resut
     ***********************************************/
     FileErrorT_ Rename(const std::string &oldName, const std::string &newName);
     
    /************************************************
     * \brief Update file name
     *
     * \param oldName  file name to update
     *
     * \return update resut
     ***********************************************/
     void UpdateFileName(const std::string &fileName) { m_fileName = fileName; }
     
    /************************************************
     * \brief Copy file 
     *
     * \param dstFileName  name of file to copy to
     *
     * \return copy resut
     ***********************************************/
     FileErrorT_ Copy(const std::string &dstFileName);
     
     /************************************************
     * \brief Copy file 
     *
     * \param dstFileName  name of file to copy to
     *
     * \return copy resut
     ***********************************************/
     FileErrorT_ Copy(File *dstFile);
     
     /************************************************
     * \brief Move file 
     *
     * \param dstFileName  name of file to move to
     *
     * \return move resut
     ***********************************************/
     FileErrorT_ Move(const std::string &dstFileName);
     
     /************************************************
     * \brief Move file 
     *
     * \param dstFileName  name of file to move to
     *
     * \return copy resut
     ***********************************************/
     FileErrorT_ Move(File *dstFile);
private:
    std::fstream m_fs;
    std::string m_fileName;
    std::ios_base m_openmode;
    bool m_isOpened;
};
}

#endif //_FILE_H_

