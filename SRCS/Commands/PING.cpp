#include "server.hpp"

int Server::ping(int fd, std::string str)
{
    sendToClient(fd, PING(clients[fd].rplFirst(), str));
    return (0);
}
