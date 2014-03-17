/*
    CS349 Assignment3 - server.cpp
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the definitions for the FTP server.
*/

#include "../include/server.h"

void sigchld_handler(int s)
{
    (void) s;
    while (waitpid (-1, NULL, WNOHANG) > 0);
}

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

FTPServer::FTPServer () : listenPort (0), listenSocket (), dataSocket ()
{
}

FTPServer::FTPServer (int port) : listenPort (port), listenSocket (),
                                  dataSocket ()
{
}

int FTPServer::start ()
{
    int status;
    if ((status = listenSocket.bind (listenPort)) < 0)
        return status;
    if ((status = listenSocket.listen (BACKLOG)) < 0)
        return status;

    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset (&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction (SIGCHLD, &sa, NULL) == -1)
    {
        cerr << "ERROR! sigaction failed.\n";
        exit(1);
    }

    cout << "Server Initialized!\n\n";
    while (true)
    {
        Socket incoming = listenSocket.accept ();
        cout << "Accepted connection from - " << incoming.getDestAddr ();
        cout << ":" << incoming.getDestPort () << "\n\n";
        if (!fork ())
        {
            listenSocket.close ();
            serveConnection (incoming);
            exit (0);
        }
        incoming.close ();
    }

    return 0;
}

void FTPServer::serveConnection (Socket control)
{
    /* Sending a reply. */
    string recv_data;
    char recv_data_str[RECV_SIZE];
    control.send (Response (SERVICE_READY, SERVER_NAME).getString ());

    while ((recv_data = control.recv (RECV_SIZE)).length () > 0)
    {
        strcpy(recv_data_str, recv_data.c_str());
        Request r1;
        r1.parseControlMessage(recv_data_str);
        if (processRequest (r1.getCommand (), r1.getArg (), control))
        {
            cout << "Connection closed from - " << control.getDestAddr ();
            cout << ":" << control.getDestPort () << "\n\n";
            control.close ();
            break;
        }
    }
}

/*
 * Returns true if request processed and no more requests are expected (QUIT)
 * and false if further requests are expected.
 */
bool FTPServer::processRequest (commands command, string args, Socket control)
{
    if (command == CWD)
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
    else if (command == PWD)
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
    else if (command == LIST)
    {
        control.send (Response (OPENING_DATA,
                                "Sending Directory Information").getString ());
        string ls_data = ls (args);
        dataSocket.send (ls_data);
        dataSocket.close ();
        control.send (Response (DATA_CONN_CLOSE, "Success").getString ());
    }
    else if (command == RETR)
    {
        ifstream in_file;
        in_file.open (args.c_str (), ios::in | ios::ate);
        if (!in_file.is_open ())
        {
            dataSocket.close ();
            control.send (Response (FILE_NOT_FOUND,
                                    "File not found").getString ());
        }
        else {
            control.send (Response (TRANSFER_START,
                                    "Sending file").getString ());
            int file_len = (int)in_file.tellg ();
            in_file.seekg (0, ios::beg);
            char* file_data = new char[file_len] ();
            in_file.read (file_data, file_len);
            dataSocket.send (file_data, file_len);
            dataSocket.close ();
            control.send (Response (DATA_CONN_CLOSE,
                                    "File send success").getString ());
            in_file.close ();
            delete[] file_data;
        }
    }
    else if (command == STOR)
    {
        ofstream out_file;
        out_file.open (args.c_str (), ios::out);
        if (!out_file.is_open ())
        {
            dataSocket.close ();
            control.send (Response (FILE_NOT_FOUND,
                                    "File open error").getString ());
        }
        else {
            char file_data[RECV_SIZE];
            control.send (Response (TRANSFER_START,
                                    "Start file send").getString ());
            int recv_len;
            while ((recv_len = dataSocket.recv (file_data, RECV_SIZE)) > 0)
            {
                out_file.write (file_data, recv_len);
            }
            dataSocket.close ();
            out_file.close ();
            control.send (Response (DATA_CONN_CLOSE,
                                    "File receive success").getString ());
        }
    }
    else if (command == PORT)
    {
        stringstream s_ip, s_port1, s_port2;
        char argstring[RECV_SIZE];
        strcpy(argstring, args.c_str());
        s_ip << strtok(argstring, ",") << ".";
        s_ip << strtok(NULL, ",") << ".";
        s_ip << strtok(NULL, ",") << ".";
        s_ip << strtok(NULL, ",");
        s_port1 << strtok(NULL, ",");
        s_port2 << strtok(NULL, ",");
        int port = atoi(s_port1.str().c_str())*256 + atoi(s_port2.str().c_str());
        string ip = s_ip.str();
        if (dataSocket.connect (ip, port) < 0)
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
    else if (command == QUIT)
    {
        control.send (Response (SERVICE_CLOSE, "Terminating").getString ());
        return true;
    }
    else
    {
        control.send (Response (GENERIC_ERROR,
                      "Unknown Command").getString ());
    }
    return false;
}

void FTPServer::stop ()
{
    listenSocket.close ();
    dataSocket.close ();
}
