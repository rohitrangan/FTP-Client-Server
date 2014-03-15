/*
    CS349 Assignment3 - socket.h
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    Contains the wrapper functions for a TCP socket.
*/

#ifndef LAB3_SOCKET_H_
#define LAB3_SOCKET_H_

#include <cerrno>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <iostream>

#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

class Socket
{
private:
    string hostname;
    int port;
    addrinfo* serverAddrinfo;
    int clientSocket;

public:
    Socket (string hostname, int port);
    ~Socket ();
};

#endif  /* LAB3_SOCKET_H_ */
