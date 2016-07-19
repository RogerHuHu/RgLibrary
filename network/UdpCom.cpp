/************************************************
 * @file UdpCom.cpp
 * \brief 
 * @author Roger
 * @version V1.1.0
 * @date 2016-07-10
 ***********************************************/

#include <iostream>
#include "UdpCom.hpp"

using namespace std;

namespace network {

/*
 * UDP 本地
 */
UdpCom::UdpCom(unsigned short port) {
    socketFd = -1;
#if (defined _WIN32) || (defined _WIN64)
    if(!WinsockInit(2, 2)) {
        socketFd = -2;
        //记录日志
    }
#endif
    if(socketFd == -1) {
        memset(&socketAddr, 0, sizeof(struct sockaddr_in)); //清空socketAddr结构体
        socketAddr.sin_family = AF_INET; //地址类型为AF_INET(地址簇)
        socketAddr.sin_addr.s_addr = htonl(INADDR_ANY); //任意本地地址
        socketAddr.sin_port = htons(port); //服务器端口号
        socketFd = socket(AF_INET, SOCK_DGRAM, 0); //初始化一个IPv4族的数据报套接字
        //int flag = fcntl(socketFd, F_GETFL, 0); //获取建立的socketFd的当前状态
        //fcntl(socketFd, F_SETFL, flag | O_NONBLOCK); //将当前socketFd设置为非阻塞
        if(bind(socketFd, (struct sockaddr *)(&socketAddr), sizeof(struct sockaddr)) != 0) //绑定端口号
            cout << "Bind Port Error" << endl;
    }
}

/*
 * UDP 远端
 */
UdpCom::UdpCom(const char *ip, unsigned short port) {
    memset(&socketAddr, 0, sizeof(struct sockaddr_in)); //清空socketAddr结构体
    socketAddr.sin_family = AF_INET; //地址类型为AF_INET（地址簇）
    socketAddr.sin_addr.s_addr = inet_addr(ip); //远端地址
    socketAddr.sin_port = htons(port); //远端端口号
}

UdpCom::~UdpCom() {
    close(socketFd);
}

#if (defined _WIN32) || (defined _WIN64)
/*
 * Init socket when the operate system is windows
 */
bool UdpCom::WinsockInit(WORD version, WORD highVersion) {
    WSADATA wsaData;
    WORD socketVersion = MAKEWORD(version, highVersion);
    return WSAStartup(socketVersion, &wsaData) == 0;
}
#endif

/*
 * 发送UDP报文
 */
void UdpCom::UdpSend(const char *sndBuf, const struct sockaddr_in addr, int len) {
    if(socketFd >= 0) //检查是否正常初始化socket
        sendto(socketFd, sndBuf, len, 0, (struct sockaddr *)&addr, sizeof(addr)); //发送UDP报文
}

/*
 * 接收UDP报文
 */
char *UdpCom::UdpReceive(const struct sockaddr_in _socketAddr, int& length) {
    char *rcvBuf = new char[BUFF_LEN];
    int sockaddrLen = sizeof(_socketAddr);
    if(socketFd >= 0) {
        length = recvfrom(socketFd, rcvBuf, BUFF_LEN, 0, (struct sockaddr *)&_socketAddr, (int *)&sockaddrLen); //从远端接收数据
        if(length > 0) {
            remoteSocketAddr = _socketAddr;    /// Add 2015-03-09 by wtt
            return rcvBuf;
        }
    }
    delete []rcvBuf;
    return NULL;
}

}
