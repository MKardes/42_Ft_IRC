#include "server.hpp"

void	Server::getOutChannels(int fd, Client &cli)
{
	// std::cout << "Get Out!!!\n";
	std::vector<std::string>::iterator it = cli.channelNames.begin();
	int		i = 0;
	for(std::vector<std::string>::iterator beg = cli.channelNames.begin(); beg != cli.channelNames.end(); beg++)
	{
		std::cout << i << " -- " << *beg << "\n";
		i++;
	}
    while (it != cli.channelNames.end())
    {
        std::map<std::string, Channel>::iterator chIt = channels.find(*it);
        if(chIt != channels.end())
        {
			if (chIt->second.getAdmin()->second.getNick() == cli.getNick())
			{
				if (chIt->second.adminDropped() < 0)
				{
					std::cout << "channel: " << chIt->first << " is removed!\n";
					chIt->second.channel_clients.clear();
					channels.erase(chIt);
				}
			}
			if (chIt->second.channel_clients.find(fd) != chIt->second.channel_clients.end())
				chIt->second.channel_clients.erase(fd);
			else
				std::cout << "Else\n";
        }
		std::cout << *it << "E\n";
		if (it == cli.channelNames.end())
			std::cout << "YES\n";
        it++;
		std::cout << "C\n";
    }
	std::cout << "geldim\n";
	cli.channelNames.clear();
}

std::string delr(std::string str)
{
	std::string::iterator	it = str.begin();
	std::string				res;
	int i = 0;
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

int isFileDescriptorOpen(int fd)
{
    int flags = fcntl(fd, F_GETFL);
    return (flags != -1);
}

// Adds the and of the message "\r\n" and then send's it to the fd
// returns 1 if message send successfully, otherwise 0
int	sendToClient(int fd, std::string msg)
{
	msg += "\r\n";
	return (send(fd, msg.c_str(), msg.size(), 0) == msg.size() ? 1 : 0);
}

void	printChannel(Channel &cha)
{
	std::cout << "New channel: " << cha.getName() << "\n";
    std::cout << "Password: " << cha.getPassword() << "\n";
    std::cout << "Admin: " << cha.getAdmin()->second.getNick() << "\n\n";
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
