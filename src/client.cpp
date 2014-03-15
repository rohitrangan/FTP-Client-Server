/*
    CS349 Assignment3 - client.cpp
    Author:- Rohit Rangan

    This file contains the definitions for the client part of the
    assignment.
*/

#include "client.h"

FTPClient::FTPClient (string hostname, int port) : serverHostname (hostname),
                                                   serverPort (port)
{
    const char* server_addr = serverHostname.c_str ();
    stringstream s1;
    s1 << serverPort;
    const char* give_port = s1.str ().c_str ();
    int status;
    addrinfo hints;
    addrinfo* servinfo;
    memset (&hints, 0, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if ((status = getaddrinfo (server_addr, give_port, &hints, &servinfo)) != 0)
    {
        std::cerr << CLIENT_DISP_ERR << "Cannot obtain IP address of ";
        std::cerr << server_addr << "\n";
        exit (1);
    }
    serverAddrinfo = servinfo;

    /* Creating the socket. */
    int fd;
    if ((fd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    {
        int errsv = errno;
        std::cerr << CLIENT_DISP_ERR << "Cannot Create Socket, Error ";
        std::cerr << errsv << "\n";
        exit (1);
    }
    clientSocket = fd;
}

int FTPClient::connectServer ()
{
    /* Connecting to the server. */
    if (connect (clientSocket, serverAddrinfo->ai_addr, serverAddrinfo->ai_addrlen) < 0)
    {
        int errsv = errno;
        std::cerr << CLIENT_DISP_ERR << "Cannot Connect to Server, Error ";
        std::cerr << errsv << "\n";
        exit (1);
    }
    std::cout << "Conected to " << serverHostname << ":" << serverPort;
    std::cout << "\n";
    return 0;
}

FTPClient::~FTPClient ()
{
    freeaddrinfo (serverAddrinfo);
}
