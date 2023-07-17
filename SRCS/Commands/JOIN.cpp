#include "server.hpp"

// returns
// -5 if the client is not invited
// -4 if the channel is full
// -3 if the channel has a password but the client did not type it
// -2 if the password is incorrect,
// -1 if that user olready joined to that channel 
// otherwise 0
int Server::join(int fd, std::string str)
{
	int											res = 0;
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
			channels.insert(std::pair<std::string, Channel>(tokens[0], Channel(tokens[0], "", fd, clients[fd])));
		}
		else
		{
			// it will have
			channels.insert(std::pair<std::string, Channel>(tokens[0], Channel(tokens[0], tokens[1], fd, clients[fd])));
		}
		it = channels.find(tokens[0]);
	}
	else
	{
		// there is a channel with this name
		if (tokens.size() == 2)
		{
			if (!it->second.getPassword().empty() && tokens[1] != it->second.getPassword())
			{
				sendToClient(fd, "Incorrect password for that channel.");
				res = -2;
			}
			else if (it->second.addClient(fd, clients[fd]) == -1)
			{
				sendToClient(fd, "You have already joined to that channel!");
				res = -1;
			}
			else if (it->second.addClient(fd, clients[fd]) == -2)
			{
				sendToClient(fd, "The channel is full");
				res = -4;
			}
		}
		else
		{
			if (it->second.getPassword() != "")
			{
				sendToClient(fd, "The channel has a password.");
				res = -3;
			}
			else if (it->second.addClient(fd, clients[fd]) == -1)
			{
				sendToClient(fd, "You have already joined to that channel!");
				res = -1;
			}
			else if (it->second.addClient(fd, clients[fd]) == -2)
			{
				sendToClient(fd, "The channel is full");
				res = -4;
			}
		}
	}
	tokens.clear();
	return (res);
}
// Message Eyüp Kemal Karaoğlu