/*
    CS349 Assignment3 - server.h
    Author:- Rohit Rangan

    This file contains the declarations for the FTP server.
*/

#ifndef LAB3_SERVER_H_
#define LAB3_SERVER_H_

#include "../include/socket.h"
#include "../include/request.h"
#include "../include/response.h"
#include "../include/return_code.h"

#include <string>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <iostream>

#include <unistd.h>

using namespace std;

#define BACKLOG     10
#define RECV_SIZE   1000
#define DISP_ERR    "ERROR! "
#define SERVER_NAME "FTP-Server"

class FTPServer
{
private:
    int listenPort;
    Socket listenSocket;
    Socket dataSocket;

    string ls (string arg);

public:
    FTPServer (int port);
    int start ();
    void serveConnection (Socket control);
    bool processRequest (string command, string args, Socket control);
};

#endif  /* LAB3_SERVER_H_ */
