/*
    CS349 Assignment3 - server_main.cpp
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the main function for the FTP server.
*/

#include "../include/server.h"

int main ()
{
    FTPServer server (20);
    server.start ();
    return 0;
}
