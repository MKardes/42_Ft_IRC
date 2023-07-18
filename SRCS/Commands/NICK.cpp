#include "server.hpp"

// returns -1 if the nick is in use
int Server::nick(int fd, std::string str)
{
	std::map<int, Client>::iterator it = clients.find(fd);
	if (it == clients.end() && passchc == 0) // checks if the pass command is executed
		quit(fd, "You need a password!");
	passchc = 0;
	std::map<int, Client>::iterator cli = clients.begin();
	while (cli != clients.end())
	{
		if (cli->second.getNick() == str)
		{
			// the new nick is found in other clients
			sendToClient(fd, "The Nick is in Use!");
			if (it == clients.end()) // if the client is a new client we should close it
				quit(fd, "");
			return (-1);
		}
		cli++;
	}
	if (it == clients.end())
		clients[fd] = Client(str);
	else
	{
		sendToClient(fd, NICK(clients[fd].rplFirst(), str));
		channelIterator	cha = channels.begin();
		for (; cha != channels.end(); cha++)
		{
			if (cha->second.getAdmin() == clients[fd].getNick())
			{
				cha->second.setAdmin(str);
			}
		}
		it->second.setNick(str);
	}
	return (0);
}
