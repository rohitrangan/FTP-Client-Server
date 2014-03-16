/*
    CS349 Assignment3 - client.cpp
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the definitions for the client part of the
    assignment.
*/

#include "../include/client.h"


FTPClient::FTPClient(string hostname, int hostport, int _dataport){
    dataport = _dataport;
    controlSocket = Socket ();
    dataSocket = Socket ();
    if(dataSocket.bind(dataport) < 0){
        cout << "Couldn't bind data socket.\n";
        exit(1);
    }
    if(controlSocket.connect(hostname, hostport) < 0){
        cout << "Unable to connect to server.\n";
        exit(1);
    }
    string recv_str = controlSocket.recv(RECV_SIZE);
    Response r = Response::parseResponse(recv_str);
    //if(r.getReturnCode() != SERVICE_READY){
    //    cout << "Service Ready confirmation malformed. Terminating...\n";
    //    exit(1);
    //}
    cout << recv_str << endl;
}

void FTPClient::sendPort(){
    stringstream s;
    s << "PORT ";
    string hostname = controlSocket.getSourceAddr();
    int port = 0;
    for(int i = 0; i < (int)(hostname.size()); i++){
        s << (hostname[i]=='.'?',':hostname[i]);
    }
    s << ',' << port/256 << ',' << port%256 << DELIM;
    controlSocket.send(s.str());
}

bool FTPClient::processRequest(char* input){
    Request r;
    r.parseTerminalCommand(input);
    
    if(r.getCommand() == PWD){
       controlSocket.send(r.getRequestString());
       string recv_str = controlSocket.recv(RECV_SIZE);
       Response r = Response::parseResponse(recv_str);
       cout << recv_str << endl;
    }
    else if (r.getCommand () == QUIT)
    {
        controlSocket.send (r.getRequestString ());
        string recv_str = controlSocket.recv (RECV_SIZE);
        cout << recv_str << endl;
        return true;
    }
    return false;
}   
