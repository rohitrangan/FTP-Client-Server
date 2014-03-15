/*
    CS349 Assignment3 - socket.cpp
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    Contains the wrapper functions for a TCP socket.
*/

#include "../include/socket.h"

socket::socket ()
{
    /* Creating the socket. */
    int fd;
    if ((fd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    {
        int errsv = errno;
        std::cerr << CLIENT_DISP_ERR << "Cannot Create Socket, Error ";
        std::cerr << errsv << "\n";
        exit (1);
    }
    socketFD = fd;
}

socket::socket (int socketfd)
{
    socketFD = socketfd;
}

int socket::connect (string host, int port)
{
    /* Determining server's IP address. */
    const char* server_addr = host.c_str ();
    stringstream s1;
    s1 << port;
    const char* give_port = s1.str ().c_str ();
    int status;
    addrinfo hints;
    addrinfo* servinfo;
    memset (&hints, 0, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if ((status = getaddrinfo (server_addr, give_port, &hints,
                               &servinfo)) != 0)
        return status;

    /* Connecting to the server. */
    return ::connect (socketFD, serv_info->ai_addr, serv_info->ai_addrlen);
}

int socket::send (string data)
{
    return ::send (socketFD, data.c_str (), data.length (), 0);
}

int socket::send (char* data, int size)
{
    return ::send (socketFD, data, size, 0);
}

string socket::recv (int len)
{
    char* recv_buf = new char[len + 1];
    int recv_len = ::recv (socketFD, recv_buf, len, 0);
    if (recv_len < 0)
        return NULL;
    recv_buf[recv_len] = '\0';
    return string (recv_buf);
}

ssize_t socket::recv (char* data, int len)
{
    return ::recv (sockFD, data, len, 0);
}

int socket::bind ()
{
    sockaddr_in myaddr;
    memset ((char*)&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl (INADDR_ANY);
    myaddr.sin_port = htons (port);
    return ::bind (socketFD, (sockaddr *)&myaddr, sizeof (myaddr));
}

int socket::listen (int backlog)
{
    return ::listen (sockFD, backlog);
}

socket socket::accept ()
{
    sockaddr_storage incoming;
    socklen_t addr_size;
    return (socket (::accept (socketFD, (sockaddr*)&incoming, &addr_size)));
}

string socket::getSourceAddr ()
{
    char src[INET_ADDRSTRLEN];
    sockaddr_t src_addr;
    socklen_t addr_size;
    getsockname (sockFD, (sockaddr*)&src_addr, &addr_size);
    inet_ntop (AF_INET, &src_addr.sin_addr, src, sizeof (src));
    return string (src);
}

int socket::getSourcePort ()
{
    sockaddr_t src_addr;
    socklen_t addr_size;
    getsockname (sockFD, (sockaddr*)&src_addr, &addr_size);
    return ntohs (src_addr.sin_port);
}

string socket::getDestAddr ()
{
    char dest[INET_ADDRSTRLEN];
    sockaddr_t dest_addr;
    socklen_t addr_size;
    getpeername (sockFD, (sockaddr*)&dest_addr, &addr_size);
    inet_ntop (AF_INET, &dest_addr.sin_addr, dest, sizeof (dest));
    return string (dest);
}

int socket::getDestPort ()
{
    sockaddr_t dest_addr;
    socklen_t addr_size;
    getpeername (sockFD, (sockaddr*)&dest_addr, &addr_size);
    return ntohs (dest_addr.sin_port);
}

socket::~socket ()
{
    freeaddrinfo (serverAddrinfo);
}
