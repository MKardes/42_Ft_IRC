#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class   Client
{
    private:
	    std::string	_nick;
	    std::string	_username;
	    std::string	_hostname;
        
    public:
        Client(std::string nick, std::string username, std::string hostname);
        ~Client();

};

#endif
