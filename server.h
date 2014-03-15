/*
    CS349 Assignment3 - server.h
    Author:- Rohit Rangan

    This file contains the declarations for the server part of the
    assignment.
*/

class FTPServer
{
private:
    int serverPort;

public:
    FTPServer (int port);
    int accept ();
};
