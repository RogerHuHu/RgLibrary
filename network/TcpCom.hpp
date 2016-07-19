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

namespace network {
    
const int BUFFER_LENGTH = 2048;
const int TCP_SEND_FAIL = -1;
const int TCP_NONBLOCK = 0;
const int TCP_BLOCK = 1;

const int SERVER = 0;
const int CLIENT = 1;

/***************************************
 * \brief TCP communication
 * *************************************/
class TcpCom {
public:
    /************************************************
     * \brief  Default constructor 
     ***********************************************/
    TcpCom() {}

    /************************************************
     * \brief  Local constructor
     *
     * \param port  local port
     * \param type  socket type
     ***********************************************/
    TcpCom(unsigned short port, int type);

    /************************************************
     * \brief  Remote constructor
     *
     * \param ip  remote ip address
     * \param port  remote port
     ***********************************************/
    TcpCom(const string &ip, unsigned short port);

    /************************************************
     * \brief Remote constructor
     *
     * \param ip  remote ip address
     * \param port  remote port
     * \param backlog
     ***********************************************/
    TcpCom(const string &ip, unsigned short port, int backlog);

    /************************************************
     * \brief Copy constuctor
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
     * \brief Get socket file descriptor
     *
     * \return socket file descriptor
     ***********************************************/
    int GetSocketFd() const { return m_socketFd; }

    /************************************************
     * \brief Get address of socket
     *
     * \return address of socket
     ***********************************************/
    struct sockaddr_in GetSockAddr() const { return m_socketAddr; }

    /************************************************
     * \brief Set block or nonBlock
     *
     * \param blockMode  block or nonblock
     *
     * \return set block mode result (true/false)
     ***********************************************/
    bool SetBlockMode(int blockMode);

    /************************************************
     * \brief Set backlog
     *
     * \param backlog
     *
     * \return set backlog result (true/false)
     ***********************************************/
    void SetBacklog(int backlog);

    /************************************************
     * \brief Connect to TCP server
     *
     * \param remote  tcp server
     *
     * \return connect result (true/false)
     ***********************************************/
    bool Connect(TcpCom *remote);

    /************************************************
     * \brief DisConnect the connection between two TCP parts
     *
     * \return disconnect result (true/false)
     ***********************************************/
    bool DisConnect();
	
	/************************************************
     * \brief Create a socket and listen the request of connection
     *
     * \return listen result (true/false)
     ***********************************************/
	bool Listen();

    /************************************************
     * \brief Wait for connection from client
     *
     * \return remote ip address
     ***********************************************/
    string Accept();

    /************************************************
     * \brief Send TCP data
     *
     * \param sndData  send data buffer
     * \param flags 
     *
     * \return the length of data send successfully
     ***********************************************/
    int TcpSend(const string &sndData, int flags = 0); 
    
    /************************************************
     * \brief Receive TCP data
     *
     * \param recvData  receive data buffer
     * \param flags  
     *
     * \return the length of data receive successfully, -1 means receive failed
     ***********************************************/
    int TcpReceive(string &recvData, int flags = 0);
    
    /************************************************
     * \brief Get the value of socket connection
     *
     * \param recvData  receive data buffer
     * \param size  receive data buffer size
     * \param flags  
     *
     * \return the length of data receive successfully, -1 means receive failed
     ***********************************************/
    int GetSockConnect() const { return m_sockConnect; }
    private:
    struct sockaddr_in m_socketAddr;  //internet socket address
    int *m_localSockFd;  //local socket file descriptor
    int m_socketFd;  //socket file descriptor
    int m_backlog;  //max length of queue which wait for connecting
    int m_sockConnect;  //socket connection
    char m_recvData[BUFFER_LENGTH];
};
}

#endif //_TCPCOM_H_
