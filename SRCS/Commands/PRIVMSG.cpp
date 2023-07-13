#include "server.hpp"

// returns -1 if message found
int Server::privmsg(int fd, std::string str)
{
    int	        res;
	int	        del_place = str.find(" ");
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
    {
        if (it->first != fd)
            sendToClient(it->first, PRIV(clients[it->first].rplFirst(), channel, msg));
    }
    return (0);
}