#include "client.hpp"

Client::Client(): _nick("Empty!"), _username("Empty!"), _hostname("Empty!"), pass(0)
{
    // std::cout << "Default constructer has been called!\n";
}

Client::Client(std::string nick): _nick(nick), pass()
{
    // std::cout << "Constructer!!!\n";
}

Client::~Client()
{
}

std::string Client::getNick()
{
    return (_nick);
}

std::string Client::getUsername()
{
    return (_username);
}

std::string Client::getHostname()
{
    return (_hostname);
}

void    Client::setNick(std::string nick)
{
    _nick = nick;
}

void    Client::setUsername(std::string username)
{
    _username = username;
}

void    Client::setHostname(std::string hostname)
{
    _hostname = hostname;
}

std::string Client::rplFirst()
{
    return _nick + (_username.empty() != 1 ? ('!' + _username):_username) + (_hostname.empty() != 1 ? ('@' + _hostname):_hostname);
}
