#include "../include/request.h"

bool Request::isLocalFile(char* filename){
	struct stat st_buf;
	stat(filename, &st_buf);
	return S_ISREG(st_buf.st_mode);
}

int Request::parse(char* input){
	char *word1, *word2;
	word1 = strtok(input, " ");
	word2 = strtok(NULL, " ");

	//Error if there are more than 2 words in the terminal command.
	if(strtok(NULL, " ")){
		cerr << "Error: Malformed command. Contains more than 2 words.\n";
		return 0;
	}

	if(string(word1) == "pwd"){
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

	argument = string(word2);
	return 1;
}


















