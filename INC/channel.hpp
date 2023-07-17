#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "client.hpp"
# include <map>
# define MAXUSER 100

typedef std::map<int, Client>::iterator				clientIterator;

class Channel
{
    private:
        int         password; // -1 is not a password, it shows that the channel has no password
        std::string name;
        Client      &admin;
        int         maxUserCount;
        bool        inviteChannel;
        bool        nMode;
    public:
        std::map<int, Client>   invited;
        std::map<int, Client>   channel_clients;

        Channel(std::string name, int pass, int fd, Client &admin);

        void            setPassword(int pass);
        void            setAdmin(Client &admin);
        void            setName(std::string name);
        void            setInvite(bool statu);
        int             getMax();
        int             getPassword();
        std::string     getName();
        bool            getInvite();
        std::map<int, Client>::iterator getAdmin();

        int     addClient(int fd, Client &cli);
        void    delClient(int fd);
        int     adminDropped();
};

int sendToClient(int fd, std::string msg);

#endif // !CHANNEL_HPP