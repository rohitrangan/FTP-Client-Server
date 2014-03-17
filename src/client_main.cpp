/*
    CS349 Assignment3 - client_main.cpp
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the main function for the FTP client.
*/

#include "../include/client.h"

#include <ctime>
#include <cstdlib>

int main (int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Usage: ./client HOST-NAME PORT-NUMBER\n\n";
        return 0;
    }

    int port = atoi (argv[2]);
    if (!port)
    {
        cout << "ERROR! Invalid port number\n\n";
        return 1;
    }

    srand (time (NULL));
    int dataport = rand () % 60000;
    dataport += 5000;
    FTPClient client (string (argv[1]), port, dataport);
    bool quit = false;
    string command;
    while (!quit)
    {
        cout << "ftp> ";
        getline (cin, command);
        char tmp_str[1000];
        strncpy (tmp_str, command.c_str (), command.length ());
        tmp_str[command.length ()] = '\0';
        quit = client.processRequest (tmp_str);
    }

    return 0;
}
