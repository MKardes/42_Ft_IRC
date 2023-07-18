#include "server.hpp"

void	Server::getOutChannels(int fd, Client &cli)
{
	std::vector<std::string>::iterator it = cli.channelNames.begin();
	for (; it != cli.channelNames.end(); it = cli.channelNames.begin())
		kick(fd, *it + " " + cli.getNick() + " QUIT_USER");
}

std::string delr(std::string str)
{
	std::string::iterator	it = str.begin();
	std::string				res;
	while(it != str.end())
	{
		if (*it != '\r')
			res += *it;
		it++;
	}
	return res;
}

std::vector<std::string>	split_by_n_r(std::string str)
{
	std::istringstream ss(str);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, ' ')) {
		std::istringstream nl(token);
		while(std::getline(nl, token, '\n')) {
			token = delr(token);
        	tokens.push_back(token);
		}
    }
	return tokens;
}

// Adds the and of the message "\r\n" and then send's it to the fd
// returns 1 if message send successfully, otherwise 0
int	sendToClient(int fd, std::string msg)
{
	msg += "\r\n";
	return (send(fd, msg.c_str(), msg.size(), 0) == (int)msg.size() ? 1 : 0);
}

void	printChannel(Channel &cha)
{
	std::cout << "New channel: " << cha.getName() << "\n";
    std::cout << "Password: " << cha.getPassword() << "\n";
    std::cout << "Admin: " << cha.getAdmin() << "\n\n";
    std::map<int, Client>::iterator it = cha.channel_clients.begin();
    while (it != cha.channel_clients.end())
    {
        std::cout << "User: " << it->second.getNick() << "\n";
        it++;
    }
}

void	Server::print()
{
	int	i = 1;
	for(std::map<std::string, Channel>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		std::cout << "\n" << i << ". ";
		printChannel(it->second);
		std::cout << "\n";
		i++;
	}
}
