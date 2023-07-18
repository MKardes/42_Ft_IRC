 #include "server.hpp"

// adam kanalda değilse kontrol +n

// returns
// -3 if channel couldn't take message from outside
// -2 if channel couldn't be found
// -1 if message found
int Server::privmsg(int fd, std::string str)
{
	std::size_t del_place = str.find(" ");
    std::string channel, msg;
	if (del_place != std::string::npos)
	{
		channel = str.substr(0, del_place);
		msg = str.substr(del_place + 1);
	}
    else
        return (-1);
    if (channel[0] != '#')
    {
        std::map<int, Client>::iterator it = clients.begin();
        for (; it != clients.end(); it++)
            if (it->second.getNick() == channel)
                sendToClient(it->first, PRIV(clients[fd].rplFirst(), clients[fd].getNick(), msg));
    }
    else
    {
        std::map<std::string, Channel>::iterator cha = channels.find(channel);
        if (cha == channels.end())
            return (-2);
        
        clientIterator  cli = cha->second.channel_clients.find(fd);
        if (cha->second.getnMode() == true && cli == cha->second.channel_clients.end())
            return(-3);

        cli = cha->second.channel_clients.begin();
        for (; cli != cha->second.channel_clients.end(); cli++)
        {
            if (cli->first != fd)
                sendToClient(cli->first, PRIV(clients[fd].rplFirst(), channel, msg));
        }
        
    }
    return (0);
}