#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "client.hpp"
# include <map>
# define MAXUSER 100

typedef std::map<int, Client>::iterator				clientIterator;

class Channel
{
    private:
        std::string password; // "" is not a password, it shows that the channel has no password
        std::string name;
        std::string adminNick;
        int         maxUserCount;
        bool        inviteChannel;
        bool        nMode;
    public:
        std::map<int, Client>   invited;
        std::map<int, Client>   channel_clients;

        Channel(std::string name, std::string pass, int fd, Client &admin);

        void        setPassword(std::string pass);
        void        setAdmin(std::string admin);
        void        setName(std::string name);
        void        setInvite(bool statu);
        void        setnMode(bool statu);
        void        setMax(int);
        int         getMax();
        std::string getPassword();
        std::string getName();
        bool        getInvite();
        bool        getnMode();
        std::string getAdmin();

        int     addClient(int fd, Client &cli);
        void    delClient(int fd);
        int     adminDropped();
};

int sendToClient(int fd, std::string msg);

#endif // !CHANNEL_HPP