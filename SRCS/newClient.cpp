#include "server.hpp"

void	Server::newClient()
{
	// buffer.clear();
	int	addr_len = sizeof(address);
	this->new_socket = accept(socket_fd, (struct sockaddr*)&address, (socklen_t *)&addr_len);
	if (this->new_socket < 0)
	{
		std::cerr << "Accept failed" << std::endl;
		return ;
	}
	pollfds.push_back((pollfd){this->new_socket, POLLIN, 0});
	char buff[BUFFER_SIZE];
	memset(buff, 0, BUFFER_SIZE);
	int bytes_received = recv(socket_fd, buff, BUFFER_SIZE, 0); 
	if (bytes_received < 0)
	{
		std::cerr << "Receive failed" << std::endl;
		return ;
	}
	buffer = std::string(buff);
	std::cout << "This:: "<< buffer << std::endl;
	// pollfds.push_back(())
	std::map<std::string, func_ptr>::iterator it;
	it = capls_map.begin();
	while (it != capls_map.end())
	{
		std::string str = "/";
		str += it->first;
		str += "\n\r";
		if (send(this->new_socket, str.c_str(), str.size(), 0) != str.size())
			std::cerr << "Error" << std::endl;
		++it;
	}
}
