#include "server.hpp"

// returns -1 if message found
int Server::notice(int fd, std::string str)
{
	std::size_t del_place = str.find(" ");
    std::string channel, msg;
	if (del_place != std::string::npos)
	{
		channel = str.substr(0, del_place);
		msg = str.substr(del_place + 1);
	}
    else
        return (-1);
    std::map<int, Client>::iterator it = clients.begin();
    for (; it != clients.end(); it++)
        if (it->second.getNick() == channel)
            sendToClient(it->first, NOTICE(clients[fd].rplFirst(), clients[fd].getNick(), msg));
    return (0);
}
