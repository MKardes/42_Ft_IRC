#include "server.hpp"

int Server::privmsg(int fd, std::string str)
{
    sendToClient(fd, PRIV(clients[fd].rplFirst, str, str));
    return (0);
}