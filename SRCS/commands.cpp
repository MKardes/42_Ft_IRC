#include "server.hpp"

int Server::pass(int fd, std::string str)
{
    std::vector<std::string>	tokens;
	int							password;

	tokens = split_by_n_r(str);
	clients.push_back(Client(tokens[2], tokens[4], tokens[6]));
	if(tokens[0] != getPassword())
	{
		send(fd, "Wrong password!!\n\r", 18, 0);
		// std::cout << "Wrong password!!\nGetting disconnected...\n";
		std::vector<pollfd>::iterator pol = pollfds.begin();
		pol++;
		std::vector<Client>::iterator cli = clients.begin();
		while (pol != pollfds.end())
		{
			if (pol->fd == fd)
			{
				close(fd);
				pol->fd = -1;
				pollfds.erase(pol);
				clients.erase(cli);
				break ;
			}
			pol++;
			cli++;
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
	if (str != "LS\r\n")
	{
		std::cerr << "Connection includes an error!!\n";
		return (-2);
	}
	else
	{
		handleMassage(fd);
	}
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

int Server::join(int fd, std::string str)
{
	(void)str;
	std::cout << "func3: " << std::endl;
	return (0);
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