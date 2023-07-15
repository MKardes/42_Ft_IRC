#include "server.hpp"

int Server::user(int fd, std::string str)
{
    std::vector<std::string>	tokens;
	tokens = split_by_n_r(str);
	clients[fd].setUsername(tokens[0]);
	clients[fd].setHostname(tokens[2]);

	std::map<std::string, func_ptr>::iterator it;
	it = commands.begin();
	sendToClient(new_socket, "Welcome to IRC Server dear " + clients[fd].getNick());
	while (it != commands.end())
	{
		sendToClient(new_socket, "/" + it->first);
		++it;
	}
	return 1;
}