#include "server.hpp"

// returns -1 if the nick is in use
int Server::nick(int fd, std::string str)
{
	std::map<int, Client>::iterator it = clients.find(fd);
	std::map<int, Client>::iterator cli = clients.begin();
	while (cli != clients.end())
	{
		if (cli->second.getNick() == str)
		{
			sendToClient(fd, "The Nick is in Use!");
			if (it == clients.end())
				quit(fd, "The Nick is in Use!");
			return (-1);
		}
		cli++;
	}
	if (it == clients.end())
		clients[fd] = Client(str);
	else
	{
		sendToClient(fd, NICK(clients[fd].rplFirst(), str));
		it->second.setNick(str);
	}
	return (0);
}
