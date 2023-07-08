#ifndef SERVER_HPP
# define SERVER_HPP

# include <cstring>
# include <sstream>
# include <cstdlib>
# include <iostream>
# include <string>
# include <vector>
# include <sys/socket.h>
# include <netinet/in.h> /* for struct sockaddr_in */
# include <unistd.h>
# include <fcntl.h>
# include <netdb.h> /* struct hostent *server */
# include <sys/poll.h>
# include <algorithm>
# include <map>
# include "client.hpp"

# define BUFFER_SIZE 1024
# define MAX_USR 100

# define COMMANDS {"ADD", "PASS", "JOIN", "CAP", "QUIT", "EXIT"}
# define COMMANDCOUNT 6

/* 	A sockaddr_in is a structure containing an internet
	address. This structure is defined in <netinet/in.h>.
	Here is the definition:
struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
}; 

!!! 	struct sockaddr_in   -->   struct sockaddr
In memory, the struct sockaddr_in is the same size as struct sockaddr,
and you can freely cast the pointer of one type to the other without any harm

*/

/* --System args--
   argv[0] = filename
   argv[1] = port
   argv[2] = password */

/* struct pollfd {
         int    fd;        file descriptor 
         short  events;    events to look for 
         short  revents;   events returned 
     }; */



class Server
{
	public:
		typedef int (Server::*func_ptr)(int, std::string);

	private:
		int			port;
		std::string	password;
		Server();

	public:
		int								new_socket;
		int								socket_fd;
		struct sockaddr_in				address;
		std::string						msg;
		std::vector<pollfd>				pollfds; // the first poll is the soket_fd
		std::vector<Client>				clients;
		std::map<std::string, func_ptr> commands;

		Server(int, char **);
		~Server();

		void	appointment(int argc, char **argv);
		void	socketOperations();
		void	socketOperations2();

		int		handleMassage(int fd);
		void	get_msg(int fd);
		void	parser(int fd, std::string &token, std::string &args);
		int		executeCommand(int fd, std::string token, std::string args);
		void	newClient();
		void	loop();

		int	add(int fd, std::string);
		int	cap(int fd, std::string);
		int	pass(int fd, std::string);
		int	nick(int fd, std::string);
		int	join(int fd, std::string);
		int	quit(int fd, std::string);

		/* Getter and setter */
		int			getPort();
		std::string	getPassword();
};

std::string					delr(std::string str);
std::vector<std::string>	split_by_n_r(std::string str);
int							isFileDescriptorOpen(int fd);

#endif