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
#include <iostream>

class FTPClient {

 private:
    Socket controlSocket;
    Socket dataSocket;
    int dataport;

 public:

    FTPClient(string hostname, int hostport, int _dataport);
    bool processRequest(char* input);
    
    //Returns true if PORT command succeded and return incoming port through
    //'incoming'. Returns false if PORT response failure.
    bool establishPORT(Socket& incoming);

};


#endif  /* LAB3_CLIENT_H_ */
