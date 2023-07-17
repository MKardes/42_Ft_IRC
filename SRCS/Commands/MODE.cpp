#include "server.hpp"

// returns
// -1 if the channel couldn't be found
int Server::mode(int fd, std::string str)
{
    std::vector<std::string>    tokens = split_by_n_r(str);
    std::string                 channel, mode, client;

    if (tokens.size() < 2)
        return (0);
    channel = tokens[0];
    mode = tokens[1];
    if (mode == "+p")
    {
        channelIterator it = channels.find(channel);
        if (it == channels.end())
        {
            sendToClient(fd, "No such Channel!");
            return (-1);
        }
        it->second.setInvite(true);
    }
    return (0);
}
