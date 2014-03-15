/*
    CS349 Assignment3 - server.cpp
    Author:- Rohit Rangan

    This file contains the definitions for the FTP server.
*/

#include "../include/server.h"

string FTPServer::ls (string arg)
{
    string command = "ls " + arg;
    FILE* file = popen(command.c_str (), "r");
    char fname[200];
    stringstream s1;
    while (fgets (fname, 200, file))
    {
        s1 << fname;
    }
    pclose(file);
    return s1.str ();
}

FTPServer::FTPServer (int port) : listenPort (port)
{
}

void FTPServer::serveConnection (Socket control)
{
    /* Sending a reply. */
    string recv_data;
    control.send (Response (SERVICE_READY, SERVER_NAME).getString ());

    while ((recv_data = control.recv (RECV_SIZE)).length () > 0)
    {
        //Request r1 = Request::parseRequest (recv_data);
        //if (processRequest (r1.getCommand (), r1.getArg ()))
        //    break;
    }
}

int FTPServer::start ()
{
    int status;
    if ((status = listenSocket.bind (listenPort)) < 0)
        return status;
    if ((status = listenSocket.listen (BACKLOG)) < 0)
        return status;

    cout << "Server Initialized!\n\n";
    while (true)
    {
        Socket incoming = listenSocket.accept ();
        cout << "Accepted connection from - " << incoming.getDestAddr ();
        cout << ":" << incoming.getDestPort () << "\n\n";
        serveConnection (incoming);
    }

    return 0;
}

bool FTPServer::processRequest (string command, string args, Socket control)
{
    if (command == "CWD")
    {
        if (chdir (args.c_str ()) < 0)
        {
            control.send (Response (FILE_NOT_FOUND,
                                    "Cannot Change Directory").getString ());
        }
        else
        {
            control.send (Response (FILE_FOUND,
                                    "Changed Directory").getString ());
        }
    }
    else if (command == "PWD")
    {
        char curr_dir[1024];
        getcwd (curr_dir, 1024);
        if (!curr_dir)
        {
            control.send (Response (FILE_NOT_FOUND,
                                    "PWD Error").getString ());
        }
        else
        {
            control.send (Response (FILE_FOUND,
                                    string (curr_dir)).getString ());
        }
    }
    else if (command == "LIST")
    {
        control.send (Response (OPENING_DATA,
                                "Sending Directory Information").getString ());
        string ls_data = ls (args);
        dataSocket.send (ls_data);
        dataSocket.close ();
        control.send (Response (DATA_CONN_CLOSE, "Success").getString ());
    }
    else if (command == "PORT")
    {
        int i = args.find (":");
        string hostname = args.substr (0, i);
        string port_str = args.substr (i+1, string::npos);
        int port = atoi (port_str.c_str ());
        if (dataSocket.connect (hostname, port) < 0)
        {
            control.send (Response (GENERIC_ERROR,
                                    "Connection Error").getString ());
        }
        else
        {
            control.send (Response (GENERIC_SUCCESS,
                                    "Connection Success").getString ());
        }
    }
    else if (command == "QUIT")
    {
        control.send (Response (SERVICE_CLOSE, "Terminating.").getString ());
    }
}
