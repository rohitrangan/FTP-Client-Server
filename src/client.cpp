/*
    CS349 Assignment3 - client.cpp
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the definitions for the client part of the
    assignment.
*/

#include "../include/client.h"


FTPClient(string _hostname, int _port){
    controlSocket.setHost(_hostname, _port);
    hostname = controlSocket.getSourceAddr();
    port = controlSocket.getSourcePort(); 
    controlSocket.connect();
}

FTPClient::sendPort(){
    stringstream s;
    s << "PORT ";
    for(int i = 0; i < hostname.size(); i++){
        s << hostname[i]=='.'?',':hostname[i];
    }
    s << ',' << port/256 << ',' << port%256 << DELIM;
    controlSocket.send(s.str());
}

ftpClient::ls(){
    sendPort();
    stringstream s;
    s << "LIST ";
    
}

FTPClient::ncd(){
    char* dirName = strtok(NULL, "\n");
    sys::cd(dirName);
}

FTPClient::nls(){
    char* dirName = strtok(NULL, "\n");
    if(dirName) cout<< sys::ls(dirName);
    else cout << sys::ls("");
}

FTPClient::npwd(){
    char* dirName = strtok(NULL, "\n");
    if(dirName) cout<< sys::pwd();
}

FTPClient::quit(){
    exit();
}