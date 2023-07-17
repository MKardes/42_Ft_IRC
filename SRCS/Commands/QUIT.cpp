#include "server.hpp"

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
			sendToClient(fd, str);
			passchc = 0;
			firstPassCall[fd] = 0;
			clients.erase(fd);
			close(it->fd);
			it->fd = -1;
			pollfds.erase(it);
			std::cout << "\033[1;91mA client has disconnected!\033[0m" << std::endl;
			msg.clear();
			break ;
		}
		it++;
	}
	return (0);
}
