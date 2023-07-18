#include "server.hpp"

std::string	Server::get_msg(int fd)
{
    int			bytes_received;
	char		buff[BUFFER_SIZE];
	std::string	res;
	
	while (msg.find("\r\n") == std::string::npos)
	{
		memset(buff, 0, BUFFER_SIZE);
		bytes_received = recv(fd, buff, BUFFER_SIZE, 0);
		if (bytes_received == 0)
		{
			quit(fd, "Disconnected ()");
			return "";
		}
		if (bytes_received < 0)
		{
			std::cerr << "Receive failed" << std::endl;
			return "";
		}
		msg += buff;

	}
	res = msg.substr(0, msg.find("\r\n"));
	msg = msg.substr(msg.find("\r\n") + 2, msg.size() - (msg.find("\r\n") + 2));

	// std::cout << "res: [" << res << "]"<< std::endl;
    // std::cout << msg.empty() << "msg: [" << msg << "]"<< std::endl;
	return res;
}

std::string toUpper(const std::string& str)
{
    std::string result;
    std::string::const_iterator it;
    for (it = str.begin(); it != str.end(); ++it) {
        result += std::toupper(*it);
    }
    return result;
}

void	Server::parser(std::string str, std::string &token, std::string &args)
{
	std::size_t	del_place = str.find(" ");
	if (del_place != std::string::npos)
	{
		token = str.substr(0, del_place);
		args = str.substr(del_place + 1);
		token = toUpper(token);
	}
	else
	{
        // Handle the case when space is not found
		token = toUpper(str);
        args = "";
    }
}

// -11 if couldn't be found the command
int	Server::executeCommand(int fd, std::string token, std::string args)
{
	std::string my_array[] = COMMANDS;
	std::vector<std::string> my_vec(my_array, my_array + COMMANDCOUNT);
	if (std::find(my_vec.begin(), my_vec.end(), token) == my_vec.end())
		return (-11);
	return ((this->*commands[token])(fd, args));
}

int    Server::handleMassage(int fd)
{
    std::string token, args, str;
	int			res = 0;

	str = get_msg(fd);
	while (!str.empty())
	{
    	parser(str, token, args);
		std::cout << "Token: (" << token << ") Args: (" << args << ")\n"; 
		res = executeCommand(fd, token, args);
		if (res == -11 && token != "WHO")
			sendToClient(fd, "Command not found!");
		else if (res != 0 && token != "WHO")
			std::cout << token << ": Error code: " << res << std::endl;
		if(msg.empty())
			return 1;
		str = get_msg(fd);
	}
    return (1);
}
