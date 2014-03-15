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

#define DELIM "\r\n"

using namespace std;

class socket
{
private:
    int socketFD;

public:
    socket ();
    socket (int sockfd);
    ~socket ();
    int connect (string host, int port);
    int send (string data);
    int send (char* data, size_t size);
    string recv (size_t len);
    ssize_t recv (char* data, size_t len);
    int bind ();
    int listen (int backlog);
    socket accept ();
    string getSourceAddr ();
    int getSourcePort ();
    string getDestAddr ();
    int getDestPort ();
};

#endif  /* LAB3_SOCKET_H_ */

