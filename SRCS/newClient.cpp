#include "server.hpp"

void	Server::newClient()
{
	int	res;
	int	addr_len = sizeof(address);
	new_socket = accept(socket_fd, (struct sockaddr*)&address, (socklen_t *)&addr_len);
	if (new_socket < 0)
	{
		std::cerr << "Accept failed" << std::endl;
		return ;
	}
	pollfds.push_back((pollfd){new_socket, POLLIN, 0});

	// res = handleMassage(new_socket);
	// if (res == -1)
	// {
	// 	std::cout << "Wrong password!!\nGetting disconnected...\n";
	// 	return ;
	// }
	// if (!isFileDescriptorOpen(new_socket))
	// 	return ;

	// std::map<std::string, func_ptr>::iterator it;
	// it = commands.begin();
	// while (it != commands.end())
	// {
	// 	if (!sendToClient(new_socket, "/" + it->first))
	// 		std::cerr << "Sending to client Error" << std::endl;
	// 	++it;
	// }
}
//void	Server::newClient()
//{
//	static int a;
//	int	res;
//	int	addr_len = sizeof(address);
//	new_socket = accept(socket_fd, (struct sockaddr*)&address, (socklen_t *)&addr_len);
//	if (new_socket < 0)
//	{
//		std::cerr << "Accept failed" << std::endl;
//		return ;
//	}
//	pollfds.push_back((pollfd){new_socket, POLLIN, 0});
//
//    get_msg(new_socket);
//	std::cout << "Here: " << msg << std::endl;
//	if (a == 0)
//		pass(new_socket, getPassword() + " s Musab s mkardes s *");
//	if (a == 1)
//		pass(new_socket, getPassword() + " s Ali s mkardes s *");
//	if (a == 2)
//		pass(new_socket, getPassword() + " s Gülçin s mkardes s *");
//	if (a == 3)
//		pass(new_socket, getPassword() + " s Eyüp s mkardes s *");
//	std::map<std::string, func_ptr>::iterator it;
//	it = commands.begin();
//	if (!sendToClient(new_socket, "Welcome to the IRC Server dear " + clients[new_socket].getNick()))
//			std::cerr << "Sending to client Error" << std::endl;
//	while (it != commands.end())
//	{
//		if (!sendToClient(new_socket, "/" + it->first))
//			std::cerr << "Sending to client Error" << std::endl;
//		++it;
//	}
//	a++;
//}
