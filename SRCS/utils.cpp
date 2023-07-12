#include "server.hpp"

void	Server::getOutChannels(int fd, Client &cli)
{
	// std::cout << "Get Out!!!\n";
	std::vector<std::string>::iterator it = cli.channelNames.begin();
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
			if (chIt->second.channel_clients.find(fd) != 0)
				chIt->second.channel_clients.erase(chIt->second.channel_clients.find(fd));
            cli.channelNames.erase(it);
            it = cli.channelNames.begin(); // Reset the iterator after erasing an element
        }
		else
        	it++;
    }
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
