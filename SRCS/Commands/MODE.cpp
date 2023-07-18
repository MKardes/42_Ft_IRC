#include "server.hpp"

// returns
// -1 if the channel couldn't be found
// -2 max size
// -3 it is not an admin
int Server::mode(int fd, std::string str)
{
    std::vector<std::string>    tokens = split_by_n_r(str);
    std::string                 channel, mode, client;

    if (tokens.size() < 2)
        return (0);
    channel = tokens[0];
    mode = tokens[1];

    channelIterator it = channels.find(channel);
    if (it == channels.end())
    {
        sendToClient(fd, "No such Channel!");
        return (-1);
    }

    if (it->second.getAdmin() != clients[fd].getNick())
    {
        sendToClient(fd, "Kick command requires Admin authority.");
        return (-3);
    }

	if (mode == "+p")
	{
		it->second.setInvite(true);
	}
	if (mode == "+n")
	{
		it->second.setnMode(true);
	}
	if (mode == "+k" )
	{
		it->second.setPassword(tokens[2]);
    }
	if(mode == "+l")
	{
        if((int)(it->second.channel_clients.size()) <= std::atoi(tokens[2].c_str()))
			{
				it->second.setMax(std::atoi(tokens[2].c_str()));
        }
		else
		{
			sendToClient(fd, "Wrong size!");
			return (-2);
		}
    }
    return (0);
}
