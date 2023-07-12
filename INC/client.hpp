#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <vector>
# include <iostream>

class   Client
{
    private:
	    std::string	_nick;
	    std::string	_username;
	    std::string	_hostname;
        
    public:
        std::vector<std::string>    channelNames;

        Client();
        // Client(std::string nick, std::string username, std::string hostname);
        Client(std::string nick);
        ~Client();
        
        std::string getNick();
        std::string getUsername();
        std::string getHostname();
        void        setNick(std::string);
        void        setUsername(std::string);
        void        setHostname(std::string);

        std::string rplFirst();
};

#endif