#include "server.hpp"

int Server::user(int fd, std::string str)
{
    std::vector<std::string>	tokens;
	tokens = split_by_n_r(str);
	clients[fd].setUsername(tokens[0]);
	clients[fd].setHostname(tokens[2]);

	std::map<std::string, func_ptr>::iterator it;
	it = commands.begin();
	while (it != commands.end())
	{
		if (!sendToClient(new_socket, "/" + it->first))
			std::cerr << "Sending to client Error" << std::endl;
		++it;
	}
	return 1;
}