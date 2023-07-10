#include "channel.hpp"

Channel::Channel(std::string _name, int _pass, int fd, Client _admin): admin(_admin), password(_pass), name(_name)
{
    addClient(fd, admin);
    std::cout << "New channel: " << getName() << "\n";
    std::cout << "Password: " << getPassword() << "\n";
    std::cout << "Admin: " << getAdmin().getNick() << "\n\n";
    std::map<int, Client>::iterator it = channel_clients.begin();
    while (it != channel_clients.end())
    {
        std::cout << "User: " << it->second.getNick() << "\n";
        it++;
    }
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

int Channel::getPassword()
{
    return (password);
}

Client Channel::getAdmin()
{
    return (admin);    
}

std::string Channel::getName()
{
    return (name);
}

// returns -1 if the client has already joined to that channel
int Channel::addClient(int fd, Client cli)
{
    std::map<int, Client>::iterator it = channel_clients.find(fd);
    if (it != channel_clients.end())
    {
        sendToClient(fd, "You have already joined to that channel!");
        return (-1);
    }
    channel_clients.insert(std::pair<int, Client>(fd, cli));
    return (0);
}
