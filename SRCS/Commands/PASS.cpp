#include "server.hpp"

int Server::pass(int fd, std::string str)
{
	if(str != getPassword() && firstPassCall[fd] == 0)
	{
		quit(fd, "Wrong Password!!");
		return (-1);
	}
	passchc = 1;
	firstPassCall[fd] = 1;
	return (0);
}