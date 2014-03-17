/*
    CS349 Assignment3 - request.cpp
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the definitions for the FTP request.
*/

#include "../include/request.h"

bool Request::isLocalFile(char* filename){
	struct stat st_buf;
	stat(filename, &st_buf);
	return S_ISREG(st_buf.st_mode);
}

int Request::parseTerminalCommand(char* input){
	char *word1, *word2;
	word1 = strtok(input, " ");
	word2 = strtok(NULL, " ");

	//Error if there are more than 2 words in the terminal command.
	if(strtok(NULL, " ")){
		cerr << "Error: Malformed command. Contains more than 2 words.\n";
		return 0;
	}
    //cout << "word1 = " << word1 << endl;
	if(string(word1) == "put"){
		type = STOR;
	}
	else if(string(word1) == "get"){
		type = RETR;
	}
	else if(string(word1) == "ls"){
		type = LIST;
	}
	else if(string(word1) == "cd"){
		type = CWD;
	}
	else if(string(word1) == "pwd"){
		type = PWD;
	}
	else if(string(word1) == "quit"){
		type = QUIT;
	}
	else{
        type = UNKNOWN;
		cerr << "Error: Unrecognized Command.\n";
		return 0;
	}

	//Some syntactical errors -
	if((type == PWD || type == QUIT) && word2 != NULL){
		cerr << "Error: Command shouldn't be followed by another word.\n";
		return 0;
	}

	if((type == RETR || type == STOR) && word2 == NULL){
		cerr << "Error: Missing filename.\n";
		return 0;
	}

	if(type == STOR && !isLocalFile(word2)){
		cerr << "Error: File doesn't exist.\n";
		return 0;
	}

	if (word2 != NULL)
        arg = string (word2);
    else
        arg = string ("");
	return 1;
}


void Request::parseControlMessage(char* input){
    char *word1, *word2;
    word1 = strtok(input, " \r\n");
    if(string(word1) == "CWD") type = CWD;
    else if(string(word1) == "LIST") type = LIST;
    else if(string(word1) == "PORT") type = PORT;
    else if(string(word1) == "PWD") type = PWD;
    else if(string(word1) == "QUIT") type = QUIT;
    else if(string(word1) == "RETR") type = RETR;
    else if(string(word1) == "STOR") type = STOR;

    word2 = strtok(NULL, "\r\n");
    if (word2 != NULL)
        arg = string(word2);
    else
        arg = string ("");
}

commands Request::getCommand(){
    return type;
}

string Request::getArg(){
    return arg;
}

string Request::getRequestString(){
    stringstream s;
    if (type == PWD)
        s << "PWD";
    else if (type == QUIT)
        s << "QUIT";
    else if (type == CWD)
        s << "CWD " << arg;
    s << DELIM;
    return s.str();
}
