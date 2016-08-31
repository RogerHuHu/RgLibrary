/************************************************
 * @file SSHForward.hpp
 * \brief 
 * @author Roger
 * @date 2016-08
 ***********************************************/
 
#ifndef _SSH_FORWARD_H_
#define _SSH_FORWARD_H_

#include "Thread.hpp"
#include "TcpCom.hpp"
#include "Rlog.hpp"

using namespace network;
using namespace log;
using namespace multi_thread;

namespace forward {

#define SSH_FORWARD_BACKLOG 5
    
class SSHForward : public Thread {
public :
   /************************************************
    * \brief  Constructor
    * 
    * \param port  format of datetime in log content
    ***********************************************/
    SSHForward(unsigned short port);
    
   /************************************************
    * \brief  Constructor
    * 
    * \param port            format of datetime in log content
    * \param logTimeFormat   format of time string in log
    * \param logMaxFileSize  max size of single log file
    * \param logBackupNum    max backup log file num
    ***********************************************/
    SSHForward(unsigned short port, const string &logTimeFormat,
    int logMaxFileSize, int logBackupNum);
     
   /************************************************
    * \brief Destructor
    ***********************************************/
    ~SSHForward();
     
   /************************************************
    * \brief Cancel current thread
    ***********************************************/
    void Cancel(); 
private :
   /************************************************
    * \brief What execute in current thread
    ***********************************************/
    void run();
     
    TcpCom *tcpServer;
    Rlog *log;
    
    bool m_cancel;
    unsigned short m_port;
    string m_clientAddr;
     
    string m_logTimeFormat;
    int m_logMaxFileSize;
    int m_logBackupNum;
};
}

#endif  //_SSH_FORWARD_H_