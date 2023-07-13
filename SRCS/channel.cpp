#include "channel.hpp"

Channel::Channel(std::string _name, int _pass, int fd, Client &_admin): admin(_admin), password(_pass), name(_name), maxUserCount(MAXUSER)
{
    setAdmin(admin);
    addClient(fd, admin);
}

void Channel::setPassword(int pass)
{
    password = pass;
}

void Channel::setAdmin(Client &_admin)
{
    admin = _admin;
}

void Channel::setName(std::string _name)
{
    name = _name;
}

int Channel::getMax()
{
    return (maxUserCount);
}

int Channel::getPassword()
{
    return (password);
}

std::map<int, Client>::iterator Channel::getAdmin()
{
    return (channel_clients.begin());    
}

std::string Channel::getName()
{
    return (name);
}

// returns -1 if the client has already joined to that channel
int Channel::addClient(int fd, Client &cli)
{
    for(std::map<int, Client>::iterator it = channel_clients.begin(); it != channel_clients.end(); it++)
    {
        if (it->second.getNick() == cli.getNick())
        {
            return (-1);
        }
    }
    channel_clients[fd] = cli;
    return (0);
}

void    Channel::delClient(int fd)
{
    channel_clients.erase(fd);
}

// returns -1 if there is no user left to be admin
// otherwise 0
int Channel::adminDropped()
{
    std::map<int, Client>::iterator it = channel_clients.begin();
    it++;
    if (it == channel_clients.end())
        return (-1);
    else
        setAdmin(it->second);
    channel_clients.erase(channel_clients.begin());

    std::cout << "New Admin is " << getAdmin()->second.getNick() << std::endl;
    return 0;
}
