/*
    CS349 Assignment3 - client.h
    Author:- Rohit Rangan

    This file contains the declarations for the client part of the
    assignment.
*/

#ifndef LAB3_CLIENT_H_
#define LAB3_CLIENT_H_

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

#define CLIENT_DISP_ERR "ERROR! "

class FTPClient
{
private:
    string serverHostname;
    int serverPort;
    addrinfo* serverAddrinfo;
    int clientSocket;

public:
    FTPClient (string hostname, int port);
    ~FTPClient ();
    int connectServer ();
};

#endif  /* LAB3_CLIENT_H_ */
