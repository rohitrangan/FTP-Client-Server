/*
    CS349 Assignment3 - request.h
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the declarations for the FTP request.
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
};

class Request {
 public:
 	commands type;
 	string arg;

 	bool isLocalFile(char* filename);


 	//Parses termnial command and converts it into the request class format
 	// Returns 1 if parsing successful and 0 if there is an error.
 	int parseTerminalCommand(char* input);

    //Parses control message received by server. It will always be successful.
    void parseControlMessage(char* input);

    commands getCommand();

    string getArg();

    string getRequestString();
};

#endif
