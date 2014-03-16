/*
    CS349 Assignment3 - server_main.cpp
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the main function for the FTP server.
*/

#include "../include/server.h"

int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Usage: ./server PORT_NUMBER\n\n";
        return 0;
    }

    int port = atoi (argv[1]);
    if (!port)
    {
        cout << "ERROR! Invalid port number\n\n";
        return 1;
    }

    FTPServer server (port);
    int status = server.start ();
    if (status < 0)
    {
        cout << "ERROR! Server could not start\n";
        return 1;
    }

    return 0;
}
