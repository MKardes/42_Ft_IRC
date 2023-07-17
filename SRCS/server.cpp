#include "server.hpp"

Server::Server(int argc, char **argv)
{
	appointment(argc, argv);
	std::cout << "Starting IRC server on port " << std::endl;
	
	socketOperations();
	socketOperations2();

	for(int i = 0; i < MAX_USER; i++)
		firstPassCall[i] = 0;

	commands["CAP"]  = &Server::cap;
	commands["USER"]  = &Server::user;
	commands["PASS"]  = &Server::pass;
	commands["NICK"] = &Server::nick;
	commands["JOIN"] = &Server::join;
	commands["QUIT"] = &Server::quit;
	commands["KICK"]  = &Server::kick;
	commands["PING"]  = &Server::ping;
	//commands["PONG"]  = &Server::pong;
	commands["NOTICE"]  = &Server::notice;
	commands["PRIVMSG"]  = &Server::privmsg;
	commands["TOPIC"]  = &Server::topic;
	commands["MODE"]  = &Server::mode;
	commands["INVITE"]  = &Server::invite;
}

Server::~Server(){}

int	Server::getPort()
{
	return(this->port);
}

std::string	Server::getPassword()
{
	return(this->password);
}

void  Server::appointment(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Arg Error." << std::endl;
		exit(1);
	}
	this->port = std::atoi(argv[1]);
	this->password = argv[2];
}

/* 
int socket (
	int domain [AF_INET:	IPv4 Internet protocols],
	int type [SOCK_STREAM:	Provides sequenced, reliable, two-way, connection-based byte streams. An out-of-band data transmission mechanism may be supported.],
	int protocol [IPPROTO_TCP:	A constant value representing the Transmission Control Protocol "TCP" within the Internet Protocol "IP" suite.]) 

int setsockopt(
	int socket [An initialized socet.],
	int level [To set options at the socket level, specify the level argument as SOL_SOCKET. To set options at other levels, supply the appropriate level identifier for the protocol controlling the option.],
	int option_name [
		SO_REUSEADDR: A socket option that allows multiple sockets to bind to the same local address and port combination. It enables reusing local addresses that are in a TIME_WAIT state, which is a state that sockets enter after they are closed, to ensure reliable data transmission.
		SO_REUSEPORT: A socket option that allows multiple sockets to bind to the same port on the same IP address. It is primarily used in server applications that want to distribute incoming connections across multiple processes or threads.],
    const void *option_value [],
	socklen_t option_len []);
*/

// !! int opt = 1;
// !! if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0)

void	Server::socketOperations()
{
	/* Create a socket */
	socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket_fd < 0)
	{
		std::cerr << "Socket Failed" << std::endl;
		exit(1);
	}
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, NULL, 0) != 0)
		std::cout << "Setsockopt set up and connecting to server..." << std::endl;
	else
	{
		std::cerr << "Setsockopt couldn't connect..." << std::endl;
		exit(1);
	}
}

void	Server::socketOperations2()
{
	address.sin_family = AF_INET; //IPV4
	address.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY is a special value used in socket programming to bind a socket to any available local network interface or IP address. 
	address.sin_port = htons(getPort()); // htons(): host port to network port

	if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		std::cerr << "Error binding to port!" << std::endl;
		exit(1);
	}

	if (listen(socket_fd, MAX_USER) < 0)
	{
		std::cerr << "Listen error!!" << std::endl;
		exit(1);
	}
	pollfds.push_back((pollfd){socket_fd, POLLIN, 0});
}
