#include "server.hpp"

int Server::user(int fd, std::string str)
{
    std::vector<std::string>	tokens;
	tokens = split_by_n_r(str);
	clients[fd].setUsername(tokens[0]);
	clients[fd].setHostname(tokens[2]);

	std::map<std::string, func_ptr>::iterator it;
	it = commands.begin();
	while (it != commands.end())
	{
		if (!sendToClient(new_socket, "/" + it->first))
			std::cerr << "Sending to client Error" << std::endl;
		++it;
	}
	return 1;
}

int Server::pass(int fd, std::string str)
{
    // std::vector<std::string>	tokens;
	// int							password;

	// tokens = split_by_n_r(str);
	// clients.insert(std::pair<int, Client>(fd, Client(tokens[0], tokens[2], tokens[6])));
	if(str != getPassword())
	{
		sendToClient(fd, "Wrong password!!");
		// std::cout << "Wrong password!!\nGetting disconnected...\n";
		quit(fd, "Wrong Password");
		//std::vector<pollfd>::iterator pol = pollfds.begin();
		//pol++;
		//while (pol != pollfds.end())
		//{
		//	if (pol->fd == fd)
		//	{
		//		clients.erase(fd);
		//		close(fd);
		//		pol->fd = -1;
		//		pollfds.erase(pol);
		//		break ;
		//	}
		//	pol++;
		//}
		// tokens.clear();
		return (-1);
	}
	// tokens.clear();
	return (0);
}

int Server::cap(int fd, std::string str)
{
	//if (str != "LS\r\n")
	//{
	//	std::cerr << "Connection includes an error!!\n";
	//	return (-2);
	//}
	//else
	//{
		// handleMassage(fd);
	//}
	return (0);
}

int Server::add(int fd, std::string str)
{
    (void)str;
	std::cout << "Add: " << std::endl;
	return (0);
}

int Server::nick(int fd, std::string str)
{
	std::cout << "Nick: " << str << "\n";
	clients.insert(std::pair<int, Client>(fd, Client(str)));
	return (0);
}

void	printChannel(Channel &cha)
{
	std::cout << "New channel: " << cha.getName() << "\n";
    std::cout << "Password: " << cha.getPassword() << "\n";
    std::cout << "Admin: " << cha.getAdmin()->second.getNick() << "\n\n";
    std::map<int, Client>::iterator it = cha.channel_clients.begin();
    while (it != cha.channel_clients.end())
    {
        std::cout << "User: " << it->second.getNick() << "\n";
        it++;
    }
}

// returns
// -4 if the channel is full
// -3 if the channel has a password but the client did not type it
// -2 if the password is incorrect,
// -1 if that user olready joined to that channel 
// otherwise 0
int Server::join(int fd, std::string str)
{
	// ! maxUserCount check
	int											pass, res = 0;
	std::vector<std::string>					tokens = split_by_n_r(str);
	std::map<std::string, Channel>::iterator	it = channels.find(tokens[0]);
	// std::cout << tokens[0] << "  client: " << clients[fd].getNick() << " " << clients[fd].getUsername() << " " << clients[fd].getHostname() << "\n";
	tokens[0] = tokens[0].find("#") != 0 ? "#" + tokens[0] : tokens[0];
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
		std::map<std::string, Channel>::iterator	it = channels.begin();
		for(; it != channels.end(); it++)
		{
			if (it->second.getName() == tokens[0])
				printChannel(it->second);
		}
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
		sendToClient(fd, JOIN(clients[fd].rplFirst(), tokens[0], clients[fd].getNick()));
		clients[fd].channelNames.push_back(tokens[0]);
	}
	if (it != channels.end())
		printChannel(it->second);
	tokens.clear();
	return (res);
}

int Server::quit(int fd, std::string str)
{
    (void)str;
	std::vector<pollfd>::iterator	it;

	it = pollfds.begin();
	while (it != pollfds.end())
	{
		if (it->fd == fd)
		{
			getOutChannels(fd, clients[fd]);
			clients.erase(fd);
			close(it->fd);
			it->fd = -1;
			pollfds.erase(it);
			std::cout << "\033[1;91mA client has disconnected!\033[0m" << std::endl;
			break ;
		}
		it++;
	}
	return (0);
}