#include "server.hpp"

void	Server::loop()
{
	while (1)
	{
		poll(pollfds.data(), pollfds.size(), -1);
		for (size_t i = 0 ; i < pollfds.size() ; i++)
		{
			if (pollfds[i].revents & POLLHUP)
			{
				// a client has been disconnected
				quit(pollfds[i].fd, "");
				print();
				break ;
			}
			if (pollfds[i].revents == POLLIN)
			{
				if (pollfds[i].fd == pollfds[0].fd)
				{
					// new connection has been occured
					newClient();
				}
				else
				{
					// the existing client will be proceed
					handleMassage(pollfds[i].fd);
				}
				print();
				break ;
			}
		}
	}
}
