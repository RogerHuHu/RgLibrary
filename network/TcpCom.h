/************************************************
 * @file TcpCom.h
 * \brief 
 * @author Roger
 * @version V1.1.0
 * @date 2016-07-10
 ***********************************************/

#ifndef _TCPCOM_H_
#define _TCPCOM_H_

#if (defined _linux) || (defined _unix)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#if (defined _WIN32) || (defined _WIN64) 
#include <winsock2.h>
#endif

#include <unistd.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <string>

using std::string;

namespace network{
    
const int BUFFER_LENGTH = 2048;
const int TCP_SEND_FAIL = -1;
const int TCP_NONBLOCK = 0;
const int TCP_BLOCK = 1;

/***************************************
 * \brief TCP Communication
 * *************************************/
class TcpCom {
public:
    /************************************************
     * \brief  Default Constructor 
     ***********************************************/
    TcpCom() {}

    /************************************************
     * \brief  Local Constructor
     *
     * \param port  local port
     ***********************************************/
    TcpCom(unsigned short port);

    /************************************************
     * \brief  Remote Constructor
     *
     * \param ip  remote ip address
     * \param port  remote port
     ***********************************************/
    TcpCom(const string &ip, unsigned short port);

    /************************************************
     * \brief Remote Constructor
     *
     * \param ip  remote ip address
     * \param port  remote port
     * \param backlog
     ***********************************************/
    TcpCom(const string &ip, unsigned short port, int backlog);

    /************************************************
     * \brief Copy Constuctor
     *
     * \param copy
     ***********************************************/
    TcpCom(const TcpCom &copy);

    /************************************************
     * \brief Destructor
     ***********************************************/
    ~TcpCom();
    
#if (defined _WIN32) || (defined _WIN64) 
    /************************************************
     * \brief Init socket when the operate system is windows
     * 
     * \param version  minor version
     * \param highVersion  major version
     * 
     * \return init result (true/false)
     ***********************************************/
    bool WinsockInit(WORD version, WORD highVersion);
#endif

    /************************************************
     * \brief Get Socket File Descriptor
     *
     * \return socket file descriptor
     ***********************************************/
    int GetSocketFd() const { return m_socketFd; }

    /************************************************
     * \brief Get Address of Socket
     *
     * \return address of socket
     ***********************************************/
    struct sockaddr_in GetSockAddr() const { return m_socketAddr; }

    /************************************************
     * \brief Set Block or NonBlock
     *
     * \param blockMode  block or nonblock
     *
     * \return set block mode result (true/false)
     ***********************************************/
    bool SetBlockMode(int blockMode);

    /************************************************
     * \brief Set Backlog
     *
     * \param backlog
     *
     * \return set backlog result (true/false)
     ***********************************************/
    void SetBacklog(int backlog);

    /************************************************
     * \brief Connect To TCP Server
     *
     * \param remote  tcp server
     *
     * \return connect result (true/false)
     ***********************************************/
    bool Connect(TcpCom *remote);

    /************************************************
     * \brief DisConnect The Connection Between Two TCP Parts
     *
     * \return disconnect result (true/false)
     ***********************************************/
    bool DisConnect();
	
	/************************************************
     * \brief Create A Socket And Listen The Request of Connection
     *
     * \return listen result (true/false)
     ***********************************************/
	bool Listen();

    /************************************************
     * \brief Wait For Connection From Client
     *
     * \return 
     ***********************************************/
    int Accept(TcpCom *remote);

    /************************************************
     * \brief Send TCP Data
     *
     * \param sndData  send data buffer
     * \param size  send data buffer size
     * \param flags 
     *
     * \return the length of data send successfully
     ***********************************************/
    int TcpSend(const char *sndData, int size, int flags = 0); 
    
    /************************************************
     * \brief Receive TCP Data
     *
     * \param recvData  receive data buffer
     * \param size  receive data buffer size
     * \param flags  
     *
     * \return the length of data receive successfully, -1 means receive failed
     ***********************************************/
    int TcpReceive(char *recvData, int size, int flags = 0);
private:
    struct sockaddr_in m_socketAddr;  //internet socket address
    int m_socketFd;  //socket file descriptor
    int m_backlog;  //max length of queue which wait for connecting
};
}

#endif //_TCPCOM_H_
