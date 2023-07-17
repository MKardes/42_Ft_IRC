#include "channel.hpp"

Channel::Channel(std::string _name, int _pass, int fd, Client &_admin): admin(_admin), password(_pass), name(_name)
{
    maxUserCount = MAXUSER;
    inviteChannel = false;
    nMode(false)
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

void Channel::setInvite(bool statu)
{
    inviteChannel = statu;
    std::cout << name << " is now Invite only Channel..." << std::endl;
}

bool Channel::getInvite()
{
    return (inviteChannel);
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
// returns -2 if the channel is full
// returns -3 if the client is not invited
int Channel::addClient(int fd, Client &cli)
{
    clientIterator clientIt = invited.find(fd);
    if (getInvite() == true && clientIt == invited.end())
    {
        sendToClient(fd, "You are not invited to this Channel.");
        return (-3);
    }
    if (getMax() < channel_clients.size() + 1)
        return (-2);
    for(std::map<int, Client>::iterator it = channel_clients.begin(); it != channel_clients.end(); it++)
    {
        if (it->second.getNick() == cli.getNick())
        {
            return (-1);
        }
    }
    channel_clients[fd] = cli;
	cli.channelNames.push_back(getName());
    clientIterator cha_cli = channel_clients.begin();
    for (; cha_cli != channel_clients.end(); cha_cli++)
    {
        if (cha_cli->first == fd) // for the user that has just added
            sendToClient(cha_cli->first, JOIN(cli.rplFirst(), name, cli.getNick()));
        else // other members
            sendToClient(cha_cli->first, JOIN(cli.getNick(), name, std::string()));
    }
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
