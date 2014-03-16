/*
    CS349 Assignment3 - client.h
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the declarations for the client part of the
    assignment.
*/

#ifndef LAB3_CLIENT_H_
#define LAB3_CLIENT_H_

#include "../include/socket.h"

#include <string>

class FTPClient {

 private:
    socket controlSocket;
    string hostname;
    int port;

    void sendPort();

 public:

    void FTPClient(string hostname, int port);

    //n stands for 'NOT'. for eg. nls means !ls.
    void ncd();
    void nls();
    void npwd();

    void ls();
    
    void quit() 
};


#endif  /* LAB3_CLIENT_H_ */
