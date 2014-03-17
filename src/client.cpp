/*
    CS349 Assignment3 - client.cpp
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the definitions for the client part of the
    assignment.
*/

#include "../include/client.h"


FTPClient::FTPClient(string hostname, int hostport, int _dataport) :
                     controlSocket (), dataSocket ()
{
    dataport = _dataport;
    if(dataSocket.bind(dataport) < 0){
        cout << "Couldn't bind data socket.\n";
        exit(1);
    }
    
    if(dataSocket.listen(BACKLOG) < 0){
        cout << "Couldn't listen on data socket.\n";
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
    cout << recv_str;
}

bool FTPClient::establishPORT(Socket& incoming)
{
    stringstream s;
    s << "PORT ";
    string hostname = controlSocket.getSourceAddr();
    int port = 0;
    for(int i = 0; i < (int)(hostname.size()); i++){
        s << (hostname[i]=='.'?',':hostname[i]);
    }
    s << ',' << port/256 << ',' << port%256 << DELIM;
    controlSocket.send(s.str());
    Response r = Response::parseResponse(controlSocket.recv(RECV_SIZE));
    if(r.getReturnCode() == GENERIC_ERROR){
        cout << r.getArgs() << "\n";
        cout << "Aborting action.\n";
        return false;
    }
    cout << r.getArgs() << "\n";
    incoming = dataSocket.accept();
    return true;
}


bool FTPClient::processRequest(char* input)
{
    Request r;
    r.parseTerminalCommand(input);
    //cout << "processRequest\n";
    //cout << r.type << "\n";
    //cout << r.arg << "\n";
    //cout << r.getRequestString() << "\n";
    if(r.getCommand() == PWD){
       controlSocket.send(r.getRequestString());
       string recv_str = controlSocket.recv(RECV_SIZE);
       Response r = Response::parseResponse(recv_str);
       cout << r.getArgs() << "\n";
    }
    else if (r.getCommand () == QUIT)
    {
        controlSocket.send (r.getRequestString ());
        string recv_str = controlSocket.recv (RECV_SIZE);
        cout << recv_str;
        return true;
    }

    return false;
}

