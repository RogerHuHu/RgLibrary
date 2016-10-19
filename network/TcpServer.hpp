#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_

/************************************************
 * \file TcpServer.hpp
 * 
 * \brief 
 * 
 * \author Roger
 * 
 * \version V1.0.0
 * 
 * \date 2016-09-13
 ***********************************************/

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

#include <string>
#include "TcpCom.h"

namespace network {

/**
 * \class TcpServer
 */
class TcpServer {
public:
    /**
     * \brief Default constructor 
     */
    TcpServer() {}
    
    /**
     * \brief  Local constructor
     *
     * \param port  local port
     * \param type  socket type
     */
    TcpServer(unsigned short port, int type);
    
    /**
     * \brief Destructor
     */
    ~TcpServer();

#if (defined _WIN32) || (defined _WIN64) 
    /**
     * \brief Init socket when the operate system is windows
     * 
     * \param version  minor version
     * \param highVersion  major version
     * 
     * \return init result (true/false)
     */
    bool WinsockInit(WORD version, WORD highVersion);
#endif

    /**
     * \brief Create a socket and listen the request of connection
     *
     * \return listen result (true/false)
     */
	bool Listen();
    
    /**
     * \brief Wait for connection from client
     *
     * \return remote ip address
     */
    TcpCom Accept();
};

}

#endif // _TCPSERVER_H_
