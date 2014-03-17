/*
    CS349 Assignment3 - server.h
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

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
#include <csignal>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>

#include <unistd.h>
#include <sys/wait.h>

using namespace std;

#define SERVER_NAME "FTP-Server"

class FTPServer
{
private:
    int listenPort;
    Socket listenSocket;
    Socket dataSocket;

    string ls (string arg);

public:
    FTPServer ();
    FTPServer (int port);
    int start ();
    void serveConnection (Socket control);
    bool processRequest (commands command, string args, Socket control);
    void stop ();
};

void sigchild_handler (int s);

#endif  /* LAB3_SERVER_H_ */
