#include "server.hpp"

void Server::pass(int fd, std::string str)
{
	std::cout << "[" << str << "]\n";
}

void Server::cap(int fd, std::string str)
{
	if (str != "LS\r\n")
	{
		std::cerr << "Connection includes an error!!\n";
		return;
	}
	else
		executeCommand(fd);
}

void Server::add(int fd, std::string str)
{
    (void)str;
	std::cout << "Add: " << std::endl;
}

void Server::nick(int fd, std::string str)
{
    (void)str;
	std::cout << "Nick\n" << std::endl;
}

void Server::join(int fd, std::string str)
{
	(void)str;
	std::cout << "func3: " << std::endl;
}

void Server::quit(int fd, std::string str)
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
}