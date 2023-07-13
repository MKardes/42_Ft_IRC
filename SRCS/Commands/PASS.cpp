#include "server.hpp"

int Server::pass(int fd, std::string str)
{
	static int a;
	if(str != getPassword() && a == 0)
	{
		sendToClient(fd, "Wrong password!!");
		quit(fd, "Wrong Password");
		return (-1);
	}
	a++;
	return (0);
}