#include "server.hpp"

void	Server::parser(int fd)
{
    std::string str = buffer;
	int	del_place = str.find(" ");
	std::string token = str.substr(0, del_place);
	std::string args = str.substr(del_place + 1);

	std::cout << "Token recieved: [" << token << "]"<< std::endl;
	// std::cout << "Arg recieved: [" << args << "]"<< std::endl;

	std::string my_array[] = {"ADD", "JOIN", "CAP", "QUIT", "EXIT"};
	std::vector<std::string> my_vec(my_array, my_array + 5);
	if (std::find(my_vec.begin(), my_vec.end(), token) == my_vec.end())
		return ;
	(this->*capls_map[token])(fd, args);
}

void	Server::executeCommand(int fd)
{
	// if (buffer.find("\n\r"))
	// {
	// buffer.clear();
	char buff[BUFFER_SIZE];
	memset(buff, 0, BUFFER_SIZE);
	int bytes_received = recv(fd, buff, BUFFER_SIZE, 0); 
	if (bytes_received < 0)
	{
		std::cerr << "Receive failed" << std::endl;
		return ;
	}
	buffer = std::string(buff);
	parser(fd);
	// } 
}
