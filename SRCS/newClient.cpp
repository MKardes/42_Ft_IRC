#include "server.hpp"

void	Server::newClient()
{
	int	addr_len = sizeof(address);
	new_socket = accept(socket_fd, (struct sockaddr*)&address, (socklen_t *)&addr_len);
	if (new_socket < 0)
	{
		std::cerr << "Accept failed" << std::endl;
		return ;
	}
	pollfds.push_back((pollfd){new_socket, POLLIN, 0});
}
