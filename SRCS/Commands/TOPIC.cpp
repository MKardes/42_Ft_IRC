#include "server.hpp"

// returns -1 if the channel does not exist
int Server::topic(int fd, std::string str)
{
    std::size_t del_place = str.find(" ");
    std::string channel, topic;
	if (del_place != std::string::npos)
	{
		channel = str.substr(0, del_place);
		topic = str.substr(del_place + 1);
	}
    std::map<std::string, Channel>::iterator cha = channels.find(channel);
    if (cha == channels.end())
    {
        sendToClient(fd, "This channel does not exist!");
        sendToClient(fd, "Usage: /topic [channel] [<topic>]");
        return (-1);
    }
    std::map<int, Client>::iterator it = cha->second.channel_clients.begin();
    for (; it != cha->second.channel_clients.end(); it++)
    {
        sendToClient(it->first, TOPIC(clients[fd].rplFirst(), channel, topic));
    }
    return (0);
}
