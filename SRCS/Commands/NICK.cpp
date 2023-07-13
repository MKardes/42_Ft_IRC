#include "server.hpp"

int Server::nick(int fd, std::string str)
{
	// ! double nick detection
	std::cout << "Nick: " << str << "\n";
	clients[fd] = Client(str);
	return (0);
}
