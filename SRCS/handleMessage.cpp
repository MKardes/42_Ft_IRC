#include "server.hpp"

std::string toUpper(const std::string& str) {
    std::string result;
    std::string::const_iterator it;
    for (it = str.begin(); it != str.end(); ++it) {
        result += std::toupper(*it);
    }
    return result;
}

void	Server::parser(int fd, std::string &token, std::string &args)
{
	int	res;
    std::string str = msg;
	int	del_place = str.find(" ");
	token = str.substr(0, del_place);
	args = str.substr(del_place + 1);

	token = toUpper(token);
}

// -1 for wrong password
// -2 for wrong type of input CAP LS
// -3 if couldn't be found the command
int	Server::executeCommand(int fd, std::string token, std::string args)
{
	std::string my_array[] = COMMANDS;
	std::vector<std::string> my_vec(my_array, my_array + COMMANDCOUNT);
	if (std::find(my_vec.begin(), my_vec.end(), token) == my_vec.end())
		return (-3);
	return ((this->*commands[token])(fd, args));
}

void    Server::get_msg(int fd)
{
    int		i = 0, bytes_received;
	char	buff[BUFFER_SIZE];
	
	memset(buff, 0, BUFFER_SIZE);
	bytes_received = recv(fd, buff, BUFFER_SIZE, 0); 
	if (bytes_received < 0)
	{
		std::cerr << "Receive failed" << std::endl;
		return  ;
	}
	msg = std::string(buff);
}

int    Server::handleMassage(int fd)
{
    std::string token, args;
    get_msg(fd);
    parser(fd, token, args);
    return (executeCommand(fd, token, args));
}
