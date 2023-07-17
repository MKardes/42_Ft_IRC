//++ for each read \r\n control ===!!!

//++ void	Server::loop() {
//++ 	while (1)
//++ 	{
//++ 		errCheck(-1, poll(_pollfds.begin().base(), _pollfds.size(), -1), "Poll Failed");
//++ 		for (size_t i = 0 ; i < _pollfds.size() ; i++)
//++ 		{
			if (_pollfds[i].revents & POLLHUP)
			{
				std::vector<std::string> msg;
				msg.push_back("Disconnected ()");
				quit(_pollfds[i].fd, msg);
				break;
			}
//++ 			if (_pollfds[i].revents & POLLIN)
//++ 			{
//++ 				if (_pollfds[i].fd == _socketFd)
//++ 				{
//++ 					newConnection();
//++ 					break ;
//++ 				}
//++ 				readMessage(_pollfds[i].fd);
//++ 			}
//++ 		}
//++ 	}
//++ }


char hostname[1024];
	if (getnameinfo((struct sockaddr *) &s_address, sizeof(s_address), hostname, 1024, NULL, 0, NI_NUMERICSERV) != 0)
		{std::cerr << "Error: failed to get client hostname!\n"; return ;}


res = recv(...);
if (res == 0)
    std::cout << "Client Disconnected";

