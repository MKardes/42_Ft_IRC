#include "server.hpp"

int Server::user(int fd, std::string str)
{
    std::vector<std::string>	tokens;
	tokens = split_by_n_r(str);
	clients[fd].setUsername(tokens[0]);
	clients[fd].setHostname(tokens[2]);

	std::map<std::string, func_ptr>::iterator it;
	sendToClient(new_socket, "Welcome to IRC Server dear " + clients[fd].getNick());
	it = commands.begin();
	while (it != commands.end())
	{
		if (!IGNORE)
			sendToClient(new_socket, "/" + it->first);
		++it;
	}
	return 0;
}