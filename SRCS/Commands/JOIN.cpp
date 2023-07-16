#include "server.hpp"

// returns
// -4 if the channel is full
// -3 if the channel has a password but the client did not type it
// -2 if the password is incorrect,
// -1 if that user olready joined to that channel 
// otherwise 0
int Server::join(int fd, std::string str)
{
	int											pass, res = 0;
	std::vector<std::string>					tokens = split_by_n_r(str);
	tokens[0] = tokens[0].find("#") != 0 ? "#" + tokens[0] : tokens[0];
	std::map<std::string, Channel>::iterator	it = channels.find(tokens[0]);
	if (it == channels.end())
	{
		// if there is no channel with this name
		// Create channel
		if (tokens.size() != 2)
		{
			// the channel will not have a password
			channels.insert(std::pair<std::string, Channel>(tokens[0], Channel(tokens[0], -1, fd, clients[fd])));
		}
		else
		{
			// it will have
			pass = std::atoi(tokens[1].c_str());
			channels.insert(std::pair<std::string, Channel>(tokens[0], Channel(tokens[0], pass, fd, clients[fd])));
		}
		it = channels.find(tokens[0]);
	}
	else if (it->second.channel_clients.size() + 1 <= it->second.getMax())
	{
		// there is a channel with this name
		if (tokens.size() == 2)
		{
			pass = std::atoi(tokens[1].c_str());
			if (it->second.getPassword() != -1 && pass != it->second.getPassword())
			{
				sendToClient(fd, "Incorrect password for that channel.");
				res = -2;
			}
			else if (it->second.addClient(fd, clients[fd]) < 0)
			{
				sendToClient(fd, "You have already joined to that channel!");
				res = -1;
			}
		}
		else
		{
			if (it->second.getPassword() != -1)
			{
				sendToClient(fd, "The channel has a password.");
				res = -3;
			}
			else if (it->second.addClient(fd, clients[fd]) < 0)
			{
				sendToClient(fd, "You have already joined to that channel!");
				res = -1;
			}
		}
	}
	else
	{
		sendToClient(fd, "The channel is full");
		res = -4;
	}
	if (res == 0)
	{
		it->second.channel_clients.insert(std::pair<int, Client>(fd, clients[fd]));
		clients[fd].channelNames.push_back(tokens[0]);
		std::map<int, Client>::iterator cha_cli = it->second.channel_clients.begin();
		for (; cha_cli != it->second.channel_clients.end(); cha_cli++)
		{
			if (cha_cli->first == fd) // for the user that has just added
				sendToClient(cha_cli->first, JOIN(clients[fd].rplFirst(), tokens[0], clients[fd].getNick()));
			else // other members
				sendToClient(cha_cli->first, JOIN(clients[fd].getNick(), tokens[0], std::string()));
		}
	}
	tokens.clear();
	return (res);
}