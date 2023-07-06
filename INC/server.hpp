#ifndef SERVER_HPP
# define SERVER_HPP

# include <cstring>
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
# define PORT 8080
# define BUFFER_SIZE 1024
# define MAX_USR 100

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
		typedef void (Server::*func_ptr)(int, std::string);

	private:
		int			port;
		std::string	password;
		Server();

	public:
		int								new_socket;
		int								socket_fd;
		struct sockaddr_in				address;
		std::string						buffer;
		std::vector<pollfd>				pollfds; // the first poll is the soket_fd
		std::vector<Client>				clients;
		std::map<std::string, func_ptr> capls_map;

		Server(int, char **);
		~Server();

		void	appointment(int argc, char **argv);
		void	socketOperations();
		void	socketOperations2(char **argv);
		void	parser(int fd);

		void	newClient();
		void	executeCommand(int fd);
		void	loop();

		void	add(int fd, std::string);
		void	cap(int fd, std::string);
		void	nick(int fd, std::string);
		void	join(int fd, std::string);
		void	quit(int fd, std::string);

		/* Getter and setter */
		int			getPort();
		std::string	getPassword();
};


#endif