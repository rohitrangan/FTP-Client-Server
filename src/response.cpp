/*
    CS349 Assignment3 - response.cpp
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the definitions for the FTP server's response.
*/

#include "../include/response.h"

Response::Response (int code, string arg) : returnCode (code), args (arg)
{
}

string Response::getString ()
{
    stringstream s;
    s << returnCode << " " << args << DELIM;
    return s.str ();
}

Response Response::parseResponse (string arg)
{
    int n1 = arg.find (" ");
    int code = atoi (arg.substr (0, n1).c_str ());
    string args = arg.substr (n1+1, string::npos);
    return Response (code, args);
}

int Response::getReturnCode ()
{
    return returnCode;
}

string Response::getArgs ()
{
    return args;
}
