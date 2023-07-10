#include "server.hpp"

int Server::pass(int fd, std::string str)
{
    std::vector<std::string>	tokens;
	int							password;

	tokens = split_by_n_r(str);
	clients.insert(std::pair<int, Client>(fd, Client(tokens[2], tokens[4], tokens[6])));
	if(tokens[0] != getPassword())
	{
		sendToClient(fd, "Wrong password!!");
		// std::cout << "Wrong password!!\nGetting disconnected...\n";
		std::vector<pollfd>::iterator pol = pollfds.begin();
		pol++;
		while (pol != pollfds.end())
		{
			if (pol->fd == fd)
			{
				clients.erase(fd);
				close(fd);
				pol->fd = -1;
				pollfds.erase(pol);
				break ;
			}
			pol++;
		}
		tokens.clear();
		return (-1);
	}
	// std::cout << "-[" << tokens[0] << "]\n";
	// std::cout << "-[" << tokens[1] << "]\n";
	// std::cout << "-[" << tokens[2] << "]\n";
	// std::cout << "-[" << tokens[3] << "]\n";
	// std::cout << "-[" << tokens[4] << "]\n";
	// std::cout << "-[" << tokens[5] << "]\n";
	// std::cout << "-[" << tokens[6] << "]\n";
	// std::cout << "-[" << tokens[7] << "]\n";
	tokens.clear();
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
		handleMassage(fd);
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
    (void)str;
	std::cout << "Nick\n" << std::endl;
	return (0);
}

void	printChannel(Channel cha)
{
	std::cout << "New channel: " << cha.getName() << "\n";
    std::cout << "Password: " << cha.getPassword() << "\n";
    std::cout << "Admin: " << cha.getAdmin().getNick() << "\n\n";
    std::map<int, Client>::iterator it1 = cha.channel_clients.begin();
    while (it1 != cha.channel_clients.end())
    {
        std::cout << "User: " << it1->second.getNick() << "\n";
        it1++;
    }
}

// returns
// -3 if the channel has a password but the client did not type it
// -2 if the password is incorrect,
// -1 if that user olready joined to that channel 
// otherwise 0
int Server::join(int fd, std::string str)
{
	int											pass, res = 0;
	std::vector<std::string>					tokens = split_by_n_r(str);
	std::map<std::string, Channel>::iterator	it = channels.find(tokens[0]);
	pass = std::atoi(tokens[1].c_str());
	//std::map<int, Client>						the_client = clients.find(fd);
	//if (the_client == clients.end())
	//{
	//	std::cout << "There is a problem commands.cpp 82::\n";
	//	return ;
	//}
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
			channels.insert(std::pair<std::string, Channel>(tokens[0], Channel(tokens[0], pass, fd, clients[fd])));
		}
	}
	else
	{
		// there is a channel with this name
		if (tokens.size() == 2)
		{
			if (it->second.getPassword() != -1 && pass != it->second.getPassword())
			{
				sendToClient(fd, "Incorrect password for that channel.");
				res = -2;
			}
			else if (it->second.addClient(fd, clients[fd]) < 0)
			{
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
				res = -1;
			}
		}
	}
	if (res == 0)
		sendToClient(fd, JOIN(clients[fd].rplFirst(), tokens[0], clients[fd].getNick()));
	if (it)
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