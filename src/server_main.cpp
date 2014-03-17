/*
    CS349 Assignment3 - server_main.cpp
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the main function for the FTP server.
*/

#include "../include/server.h"

#include <csignal>

FTPServer server;

/* This function shuts down all the server connections and the server
 * itself.
 */
void my_sigint_handler (int s)
{
    (void) s;
    cout << "\n";
    cout << "Initiating Server Shutdown...\n";
    cout << "Closing All Connections... ";
    server.stop ();
    cout << "Success!\n\n";
    cout << "All Connections Closed. Exiting...\n\n";
    exit (EXIT_SUCCESS);
}

int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Usage: ./server PORT_NUMBER\n\n";
        return 0;
    }

    int port = atoi (argv[1]);
    if (!port)
    {
        cout << "ERROR! Invalid port number\n\n";
        return 1;
    }

    /* Starting a signal handler for graceful shutdown. This only occurs if
     * the user types CTRL+C to interrupt the program.
     */
    struct sigaction sigint_handler;
    sigint_handler.sa_handler = my_sigint_handler;
    sigemptyset (&sigint_handler.sa_mask);
    sigint_handler.sa_flags = 0;
    if (sigaction(SIGINT, &sigint_handler, NULL) < 0)
    {
        int errsv = errno;
        cerr << "ERROR! Cannot Start Signal Handler, Error ";
        cerr << errsv << "\n";
        return 1;
    }

    server = FTPServer (port);
    int status = server.start ();
    if (status < 0)
    {
        cout << "ERROR! Server could not start\n\n";
        return 1;
    }

    return 0;
}
