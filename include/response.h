/*
    CS349 Assignment3 - response.h
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the declarations for the FTP server's response.
*/

#ifndef LAB3_RESPONSE_H_
#define LAB3_RESPONSE_H_

#include "../include/socket.h"

#include <string>
#include <sstream>
#include <cstdlib>

class Response
{
private:
    int returnCode;
    string args;

public:
    Response (int code, string arg);
    string getString ();
    static Response parseResponse (string arg);
    int getReturnCode ();
    string getArgs ();
};

#endif  /* LAB3_RESPONSE_H_ */
