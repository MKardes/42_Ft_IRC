#include "server.hpp"

void Server::cap(int fd, std::string str)
{
	(void)str;
}

void Server::add(int fd, std::string str)
{
    (void)str;
	std::cout << "func1: " << std::endl;
	if (send(fd, "my_new_nick\r\n", 13, 0) != str.size())
			std::cerr << "Error" << std::endl;
}

void Server::nick(int fd, std::string str)
{
    (void)str;
	std::cout << "Değişti\n" << std::endl;
	if (send(fd, "/NICK ALPHA\n\r", 15, 0) != str.size())
			std::cerr << "Error" << std::endl;
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