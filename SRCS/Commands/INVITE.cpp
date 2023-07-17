#include "server.hpp"

// returns
// -2 if the channel couldn't be found
// -2 if the client couldn't be found
// -3 if the input is incorrect
int Server::invite(int fd, std::string str)
{
    std::vector<std::string>    tokens = split_by_n_r(str);
    std::string                 channel, client;
    if (tokens.size() != 2)
    {
        sendToClient(fd, "Wrong input!");
        sendToClient(fd, "Usage: /INVITE [client] [channel]");
        return (-3);
    }
    channel = tokens[1];
    client = tokens[0];
    
    std::map<std::string, Channel>::iterator    it = channels.find(channel);
    std::map<int, Client>::iterator             cli = clients.begin();

    if (it == channels.end())
    {
        sendToClient(fd, "No such Channel!");
        return (-1);
    }
    for (; cli != clients.end(); cli++)
    {
        if (cli->second.getNick() == client)
            break ;    
    }
    if (cli == clients.end())
    {
        sendToClient(fd, "No such Client!");
        return (-2);
    }
    it->second.invited.insert(std::pair<int, Client>(cli->first, cli->second));
    return (0);
}
