/************************************************
 * @file UdpCom.h
 * \brief 
 * @author Roger
 * @version V1.1.0
 * @date 2016-07-10
 ***********************************************/

#ifndef _UDPCOM_H_
#define _UDPCOM_H_

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

namespace network {

#define BUFF_LEN 2048

/************************************************
 * \brief UDP通信
 *************************************************/
class UdpCom {
public:
    UdpCom() {}
    UdpCom(unsigned short port);
    UdpCom(const char *ip, unsigned short port);
    ~UdpCom();
    
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
     * \brief 获取sockAddr
     *
     * \return 返回sockAddr
     *************************************************/
    struct sockaddr_in GetSockAddr() const { return socketAddr; }

    /************************************************
     * \brief 发送UDP报文
     *
     * \param socketFd 正在监听端口的套接字描述符
     * \param sndBuf 发送缓冲区
     * \param addr 接收数据的主机地址信息
     * \param len 接收数据的主机地址信息的长度
     *************************************************/
    void UdpSend(const char *sndBuf, const struct sockaddr_in addr, int len);

    /************************************************
     * \brief 接收UDP报文
     *
     * \param _socketAddr 发送方的地址信息
     * \param length 接收到的字符串长度
     * \return 接收到的数据
     *************************************************/
    char *UdpReceive(const struct sockaddr_in _socketAddr, int &length);

    /************************************************
     * \brief 获取套接字文件描述符
     *
     * \return 套接字文件描述符
     ************************************************/
    int GetSocketFd() const { return socketFd; }

    /************************************************
     * \brief 获取远端发送方的sockAddr   add
     *
     * \return 返回sockAddr
     *************************************************/
    struct sockaddr_in GetRemoteSockAddr() const { return remoteSocketAddr; }
private:
    struct sockaddr_in socketAddr;
    int socketFd;
    struct sockaddr_in remoteSocketAddr;
};

}

#endif // _UDPCOM_H_
