#include "server.hpp"

void	Server::newClient()
{
	int	res;
	int	addr_len = sizeof(address);
	this->new_socket = accept(socket_fd, (struct sockaddr*)&address, (socklen_t *)&addr_len);
	if (this->new_socket < 0)
	{
		std::cerr << "Accept failed" << std::endl;
		return ;
	}
	pollfds.push_back((pollfd){this->new_socket, POLLIN, 0});

	res = handleMassage(this->new_socket);
	if (res == -1)
	{
		std::cout << "Wrong password!!\nGetting disconnected...\n";
		return ;
	}
	if (!isFileDescriptorOpen(this->new_socket))
		return ;

	std::map<std::string, func_ptr>::iterator it;
	it = commands.begin();
	while (it != commands.end())
	{
		std::string str = "/";
		str += it->first;
		str += "\n\r";
		if (send(this->new_socket, str.c_str(), str.size(), 0) != str.size())
			std::cerr << "Sending to client Error" << std::endl;
		++it;
	}
}
