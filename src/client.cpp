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
    if(controlSocket.connect(hostname, hostport) < 0){
        cout << "Unable to connect to server.\n";
        exit(1);
    }
    if(dataSocket.bind(dataport) < 0){
        cout << "Couldn't bind data socket.\n";
        exit(1);
    }
    
    if(dataSocket.listen(BACKLOG) < 0){
        cout << "Couldn't listen on data socket.\n";
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
    int port = dataport;
    for(int i = 0; i < (int)(hostname.size()); i++){
        s << (hostname[i]=='.'?',':hostname[i]);
    }
    s << ',' << port/256 << ',' << port%256 << DELIM;
    controlSocket.send(s.str());
    string recv_str = controlSocket.recv(RECV_SIZE);
    Response r = Response::parseResponse(recv_str);
    if(r.getReturnCode() == GENERIC_ERROR){
        cout << recv_str;
        cout << "Aborting action.\n";
        return false;
    }
    cout << recv_str;
    incoming = dataSocket.accept();
    return true;
}


bool FTPClient::processRequest(char* input)
{
    Request r;
    int ret_val = r.parseTerminalCommand(input);
    if (ret_val == 2)
        return false;

    //cout << "processRequest\n";
    //cout << r.type << "\n";
    //cout << r.arg << "\n";
    //cout << r.getRequestString() << "\n";
    if(r.getCommand () == PWD)
    {
       controlSocket.send (r.getRequestString ());
       string recv_str = controlSocket.recv (RECV_SIZE);
       Response res = Response::parseResponse (recv_str);
       cout << recv_str;
    }
    else if (r.getCommand () == CWD)
    {
        controlSocket.send (r.getRequestString ());
        string recv_str = controlSocket.recv (RECV_SIZE);
        Response res = Response::parseResponse (recv_str);
        cout << recv_str;
    }
    else if (r.getCommand () == LIST)
    {
        Socket datSock;
        if (!establishPORT (datSock))
        {
            cout << "Data connection failed." << endl;
            return false;
        }
        controlSocket.send (r.getRequestString ());
        string recv_str = controlSocket.recv (RECV_SIZE);
        cout << recv_str << "\n";
        while ((recv_str = datSock.recv (RECV_SIZE)).length () > 0)
        {
            cout << recv_str;
        }
        datSock.close ();
        recv_str = controlSocket.recv (RECV_SIZE);
        cout << "\n" << recv_str;
    }
    else if (r.getCommand () == RETR)
    {
        Socket datSock;
        if (!establishPORT (datSock))
        {
            cout << "Data connection failed." << endl;
            return false;
        }
        controlSocket.send (r.getRequestString ());
        string recv_str = controlSocket.recv (RECV_SIZE);
        Response res = Response::parseResponse (recv_str);
        if (res.getReturnCode () == FILE_NOT_FOUND)
        {
            cout << recv_str;
            datSock.close ();
            return false;
        }
        cout << recv_str << "\n";
        ofstream out_file;
        out_file.open (r.getArg ().c_str (), ios::out);
        if (!out_file.is_open ())
        {
            cerr << "ERROR! Could not open file." << endl;
            datSock.close ();
            return false;
        }
        char recv_str_data[RECV_SIZE];
        int recv_len;
        while ((recv_len = datSock.recv (recv_str_data, RECV_SIZE)) > 0)
        {
            out_file.write (recv_str_data, recv_len);
        }
        datSock.close ();
        out_file.close ();
        recv_str = controlSocket.recv (RECV_SIZE);
        cout << "\n" << recv_str;
    }
    else if (r.getCommand () == STOR)
    {
        Socket datSock;
        if (!establishPORT (datSock))
        {
            cerr << "ERROR! Data connection failed." << endl;
            return false;
        }
        controlSocket.send (r.getRequestString ());
        string recv_str = controlSocket.recv (RECV_SIZE);
        Response res = Response::parseResponse (recv_str);
        if (res.getReturnCode () == FILE_NOT_FOUND)
        {
            cout << recv_str;
            datSock.close ();
            return false;
        }
        cout << recv_str << "\n";
        ifstream in_file;
        string args = r.getArg ();
        in_file.open (args.c_str (), ios::in | ios::ate);
        if (!in_file.is_open ())
        {
            cerr << "ERROR! Could not open file." << endl;
            datSock.close ();
            return false;
        }
        int file_len = (int)in_file.tellg ();
        in_file.seekg (0, ios::beg);
        char* file_data = new char[file_len] ();
        in_file.read (file_data, file_len);
        datSock.send (file_data, file_len);
        datSock.close ();
        in_file.close ();
        recv_str = controlSocket.recv (RECV_SIZE);
        cout << "\n" << recv_str;
        delete[] file_data;
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

