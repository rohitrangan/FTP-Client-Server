/*
    CS349 Assignment3 - client.h
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the declarations for the client part of the
    assignment.
*/

#ifndef LAB3_CLIENT_H_
#define LAB3_CLIENT_H_

#include "../include/request.h"
#include "../include/response.h"
#include "../include/return_code.h"
#include "../include/socket.h"

#include <string>

class FTPClient {

 private:
    Socket controlSocket;
    Socket dataSocket;
    int dataport;

    void sendPort();

 public:

    FTPClient(string hostname, int hostport, int _dataport);
    void processRequest(char* input);

};


#endif  /* LAB3_CLIENT_H_ */
