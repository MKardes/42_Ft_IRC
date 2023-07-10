#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "client.hpp"
# include <map>

class Channel
{
    private:
        int         password; // -1 is not a password, it shows that the channel has no password
        Client      &admin;
        std::string name;
    public:
        std::map<int, Client> channel_clients;

        Channel(std::string name, int pass, int fd, Client admin);

        void        setPassword(int pass);
        void        setAdmin(Client &admin);
        void        setName(std::string name);
        int         getPassword();
        Client      getAdmin();
        std::string getName();

        int addClient(int fd, Client cli);
};

int sendToClient(int fd, std::string msg);

#endif // !CHANNEL_HPP