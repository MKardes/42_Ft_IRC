#include "server.hpp"

// /kick [channel] [nick] [comment]

// returns
// 1 if the channel is deleted
// -1 Channel not found
// -2 The client is not admin
int Server::kick(int fd, std::string str)
{
    int                         chaDeleted = 0;
    std::string                 reason;
    std::vector<std::string>    tokens = split_by_n_r(str);
    channelIterator             cha = channels.find(tokens[0]);
    if (cha == channels.end())
    {
        sendToClient(fd, "Channel not found!");
        return (-1);
    }
    if (cha->second.getAdmin() != clients[fd].getNick())
    {
        sendToClient(fd, "Kick command requires Admin authority.");
        return (-2);
    }

    if (tokens.size() >= 3)
        reason = tokens[2]; // tek kelime,
    if(tokens[2] != "QUIT_USER")
    {
        clientIterator  it = cha->second.channel_clients.begin();
        for(; it != cha->second.channel_clients.end(); it++)
        {
            sendToClient(it->first, KICK(clients[fd].rplFirst(), tokens[0], tokens[1], reason));
        }
    }

    clientIterator  channelClients = cha->second.channel_clients.begin();
    for (; channelClients != cha->second.channel_clients.end(); channelClients++)
    {
        if (channelClients->second.getNick() == tokens[1])
        {
            // drop the client from channel
            if (cha->second.getAdmin() == tokens[1])
            {
                // if the client is the admin
                if (cha->second.channel_clients.size() == 1)
                {
                    // There is no one to be Admin
                    std::cout << "There is no member to be Admin in the channel.\n" << cha->second.getName() << " is deleting..." << std::endl;
                    cha->second.channel_clients.clear();
                    cha->second.invited.clear();
					channels.erase(cha);
                    chaDeleted++;
                }
                else
                {
                    // The new Admin;
                    std::cout << "Admin is changing..." << std::endl;
                    clientIterator  it = cha->second.channel_clients.begin();
                    for(; it != cha->second.channel_clients.end(); it++)
                    {
                        if (it->second.getNick() == cha->second.getAdmin())
                        {
                            cha->second.channel_clients.erase(it->first);
                            break ;
                        }
                    }
                    cha->second.setAdmin(cha->second.channel_clients.begin()->second.getNick());
                    std::cout << "The new Admin is " << cha->second.getAdmin() << std::endl;
                }
            }
            else // if the client is not the admin
                cha->second.channel_clients.erase(channelClients);
            break ;
        }
    }

    if (!chaDeleted)
    {
        clientIterator  invitedClients = cha->second.invited.begin();
        for (; invitedClients != cha->second.invited.end(); invitedClients++)
        {
            if (invitedClients->second.getNick() == tokens[1])
            {
                cha->second.invited.erase(invitedClients);
                break ;
            }
        }
    }
    
    clientIterator  allClientsIT = clients.begin();
    for (; allClientsIT != clients.end(); allClientsIT++)
    {
        if (allClientsIT->second.getNick() == tokens[1])
        {
            allClientsIT->second.channelNames.erase(std::find(allClientsIT->second.channelNames.begin(), allClientsIT->second.channelNames.end(), tokens[0]));
        }
    }

    return (0);
}