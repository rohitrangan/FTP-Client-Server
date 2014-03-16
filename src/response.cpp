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
