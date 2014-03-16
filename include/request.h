/*
    CS349 Assignment3 - request.h
    Author:- Rohit Rangan

    This file contains the declarations for the client part of the
    assignment.
*/

#ifndef LAB3_REQUEST_H_
#define LAB3_REQUEST_H_

#include "socket.h"

#include <cstring>
#include <sstream>
#include <string>
#include <sys/stat.h>

enum commands {
	CWD,
	LIST,
	PORT,
	PWD,
	QUIT,
	RETR,
	STOR,
	TYPE,
};

class Request {
 public:
 	commands type;
 	string argument;

 	bool isLocalFile(char* filename);


 	//Parses termnial command and converts it into the request class format
 	// Returns 1 if parsing successful and 0 if there is an error.
 	int parse(char* input);
};

#endif
