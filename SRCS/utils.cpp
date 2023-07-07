#include "server.hpp"

std::string delr(std::string str)
{
	std::string::iterator	it = str.begin();
	std::string				res;
	int i = 0;
	while(it != str.end())
	{
		if (*it != '\r')
			res += *it;
		it++;
	}
	return res;
}

std::vector<std::string>	split_by_n_r(std::string str)
{
	std::istringstream ss(str);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, ' ')) {
		std::istringstream nl(token);
		while(std::getline(nl, token, '\n')) {
			token = delr(token);
        	tokens.push_back(token);
		}
    }
	return tokens;
}

int isFileDescriptorOpen(int fd)
{
    int flags = fcntl(fd, F_GETFL);
    return (flags != -1);
}
