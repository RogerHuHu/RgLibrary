/************************************************
 * @file TcpCom.cpp
 * \brief 
 * @author Roger
 * @version V1.1.0
 * @date 2016-07-10
 ***********************************************/

#include "TcpCom.h"

using namespace std;

namespace network {
/*
 * Local Constructor 
 */
TcpCom::TcpCom(unsigned short port) : m_backlog(1) {
    m_socketFd = -1;
#if (defined _WIN32) || (defined _WIN64)
    if(!WinsockInit(2, 2)) {
        m_socketFd = -2;
        //记录日志
    }
#endif
    if(m_socketFd == -1) {
        m_socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
        memset(&m_socketAddr, 0, sizeof(struct sockaddr_in));  //clear struct m_socketAddr
        m_socketAddr.sin_family = AF_INET;  //address type is AF_INET
        m_socketAddr.sin_port = htons(port);  //local port
        m_socketAddr.sin_addr.s_addr = INADDR_ANY;  //any local ip address
        bind(m_socketFd, (struct sockaddr *)(&m_socketAddr), sizeof(struct sockaddr));
    }
}

/*
 * Remote Constructor
 */
TcpCom::TcpCom(const string &ip, unsigned short port) {
    memset(&m_socketAddr, 0, sizeof(struct sockaddr_in));  //clear struct m_socketAddr
    m_socketAddr.sin_family = AF_INET;  //address type is AF_INET
    m_socketAddr.sin_addr.s_addr = inet_addr(ip.c_str());  //remote address
    m_socketAddr.sin_port = htons(port);  //remote port
}

/*
 * Remote Constructor
 */
TcpCom::TcpCom(const string &ip, unsigned short port, int backlog) {
    memset(&m_socketAddr, 0, sizeof(struct sockaddr_in));  //clear struct m_socketAddr
    m_socketAddr.sin_family = AF_INET;  //address type is AF_INET
    m_socketAddr.sin_addr.s_addr = inet_addr(ip.c_str());  //remote address
    m_socketAddr.sin_port = htons(port);  //remote port

    m_backlog = backlog;
}

/*
 * Copy Constructor
 */
TcpCom::TcpCom(const TcpCom &copy) {
    this->m_socketAddr = copy.m_socketAddr;
    this->m_socketFd = copy.m_socketFd;
    this->m_backlog = copy.m_backlog;
}

/*
 * Destructor
 */
TcpCom::~TcpCom() {
    if(m_socketFd > 0)
        close(m_socketFd);
}

#if (defined _WIN32) || (defined _WIN64)
/*
 * Init socket when the operate system is windows
 */
bool TcpCom::WinsockInit(WORD version, WORD highVersion) {
    WSADATA wsaData;
    WORD socketVersion = MAKEWORD(version, highVersion);
    return WSAStartup(socketVersion, &wsaData) == 0;
}
#endif

/*
 * Set Block or Nonblock
 */
bool TcpCom::SetBlockMode(int blockMode) {
#if (defined _linux) || (defined _unix)
    int flag = fcntl(m_socketFd, F_GETFL, 0);  //get status of socket which descriptor is m_socketFd
    if(flag == -1) return false;
    if(blockMode == TCP_NONBLOCK)
        return (fcntl(m_socketFd, F_SETFL, flag | O_NONBLOCK) == 0);  //set status of socket(nonblock)
    else if(blockMode == TCP_BLOCK)
        return (fcntl(m_socketFd, F_SETFL, flag & ~O_NONBLOCK) == 0);  //set status of socket(block)
    else
        return false;
#endif

#if (defined _WIN32) || (defined _WIN64) 
    unsigned long ul = 1;
    if(blockMode == TCP_NONBLOCK)
        return (ioctlsocket(m_socketFd, FIONBIO, (unsigned long *)&ul) != SOCKET_ERROR);  //set status of socket(nonblock)
    else if(blockMode == TCP_BLOCK)
        return true;
    else
        return false;
#endif
}

/*
 * Set Backlog
 */
void TcpCom::SetBacklog(int backlog) {
    m_backlog = backlog;
}

/*
 * Connect To TCP Server
 */
bool TcpCom::Connect(TcpCom *remote) {
    int socketFd = remote->GetSocketFd();
	struct sockaddr_in remoteAddr = remote->GetSockAddr();
    if(socketFd > 0)
        return (connect(socketFd, (struct sockaddr *)&remoteAddr,
                    sizeof(struct sockaddr)) != -1);
    return false;
}

/*
 * DisConnect The Connection Between Two TCP Port
 */
bool TcpCom::DisConnect() {
    if(m_socketFd > 0)
        return close(m_socketFd) == 0;
	return true;
}

/*
 * Create A Socket And Listen The Request of Connection
 */
bool TcpCom::Listen() {
	return listen(m_socketFd, m_backlog) == -1;
}

/*
 * Wait For Connection From Client
 */
string TcpCom::Accept() {
    struct sockaddr_in remoteAddr;
    int len = sizeof(struct sockaddr_in);
    m_sockConnect = accept(m_socketFd, (struct sockaddr *)&remoteAddr, &len);
    if(m_sockConnect == -1)
        return "";
    else
        return inet_ntoa(remoteAddr.sin_addr);
}

/*
 * Send TCP Data
 */
int TcpCom::TcpSend(const char *sndData, int size, int flags) {
    if(m_socketFd > 0)
        return send(m_sockConnect, sndData, size, flags);
    return TCP_SEND_FAIL;
}

/*
 * Receive TCP Data
 */
int TcpCom::TcpReceive(char *recvData, int size, int flags) {
    if(m_socketFd > 0) {
        int recvLength = 0;
        recvLength = recv(m_sockConnect, recvData, size, flags);
        return recvLength;
    }
    
    return -1;
}

}
