/************************************************
 * @file SSHForward.cpp
 * \brief 
 * @author Roger
 * @date 2016-08
 ***********************************************/
 
#include "SSHForward.hpp"
#include "TcpCom.h"

namespace forward {
/*
 * Construstor
 */
SSHForward::SSHForward(unsigned short port) : m_port(port),
                                              m_cancel(false),
                                              m_clientAddr(""),
                                              m_logTimeFormat("%Y-%m-%d %H:%M:%S"),
                                              m_logMaxFileSize(100 * 1024),
                                              m_logBackupNum(3) {
    log = new Rlog(m_logTimeFormat, LOG_TERMINAL, LOG_CODE, 
                   m_logBackupNum, m_logMaxFileSize);
    tcpServer = new TcpCom(m_port, TCP_SERVER);
    tcpServer->SetBacklog(SSH_FORWARD_BACKLOG);
    tcpServer->Listen();
}

/*
 * Construstor
 */
SSHForward::SSHForward(unsigned short port, const string &logTimeFormat,
                       int logMaxFileSize, int logBackupNum) 
                       : m_port(port), 
                         m_cancel(false),
                         m_clientAddr(""),
                         m_logTimeFormat(logTimeFormat),
                         m_logMaxFileSize(logMaxFileSize),
                         m_logBackupNum(logBackupNum) {
    log = new Rlog(m_logTimeFormat, LOG_TERMINAL, LOG_CODE, 
                   m_logBackupNum, m_logMaxFileSize);
    log->RlogOpen();
    tcpServer = new TcpCom(m_port, TCP_SERVER);
    tcpServer->SetBacklog(SSH_FORWARD_BACKLOG);
    tcpServer->Listen();
}

/*
 * Destrustor
 */
SSHForward::~SSHForward() {
    delete tcpServer;
}

/*
 * Cancel current thread
 */
void SSHForward::Cancel() {
    if(!m_cancel) {
        m_cancel = true;
        Join();
        m_cancel = false;
}
    
/*
 * What execute in current thread
 */
void SSHForward::Run() {
    while(!m_cancel) {
        if(m_clientAddr == "") {
            m_clientAddr = tcpServer->Accept();
            if(m_clientAddr != "")
                log->RlogWrite(0, "Client Access: " + m_clientAddr, LOG_INFO);
        } else {
            
        }
    }
}

}

}