#include "server.hpp"

Server::Server(const std::string &port, const std::string &pwd): _socketfd(-1), _counter(0),_port(port), _pwd(pwd)
{
	this->_cmds["PASS"] = &Server::commandpass;
	this->_cmds["USER"] = &Server::commanduser;
	this->_cmds["NICK"] = &Server::commandnick;
	this->_cmds["PRIVMSG"] = &Server::commandprivmsg;
	this->_cmds["JOIN"] = &Server::commandjoin;
	this->_cmds["LIST"] = &Server::commandlist;
	this->_cmds["NOTICE"] = &Server::commandnotice;
	this->_cmds["KICK"] = &Server::commandkick;
	this->_cmds["AWAY"] = &Server::commandaway;
	this->_cmds["TOPIC"] = &Server::commandtopic;
	this->_cmds["QUIT"] = &Server::commandquit;
	this->_cmds["PART"] = &Server::commandpart;
	this->_cmds["MODE"] = &Server::commandmode;
	this->_cmds["NAMES"] = &Server::commandnames;
	this->_cmds["INVITE"] = &Server::commandinvite;
	this->_cmds["HELP"] = &Server::commandhelp;
	this->_cmds["MOTD"] = &Server::commandmotd;
	this->_cmds["WHOIS"] = &Server::commandwhois;
}

Server::~Server()
{
	std::vector<User *> users = getUsers();
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
		this->deleteUser(*it);
	}
	close(this->_socketfd);
}

void Server::init() // The main goal here is to find a suitable socket for our server to use
{
	struct addrinfo *port_info = NULL; // Need those to gather the info we want on the internet adress
	struct addrinfo *ai = NULL; // The addrinfo fulfilled by getaddrinfo is a chain list, ai will be our iterator
	struct addrinfo hints; // The hints passed in our reserach getaddrinfo
	
	memset(&hints, 0, sizeof(hints)); // Hints need to be set to empty to be sure
	hints.ai_flags = AI_PASSIVE; // So the socket adresses that we will get will be able to be called with bind
	hints.ai_family = AF_INET; // We want all IPV4 and IPV6
	hints.ai_socktype = SOCK_STREAM; // Bilateral transmission of data

	if (getaddrinfo(NULL, this->_port.c_str(), &hints, &port_info) != 0) // Gathering info on the port passed et checking for error
		throw std::runtime_error("Fatal error: getaddrinfo");
	
	for (ai = port_info; ai != NULL; ai = ai->ai_next) // We are going to run through the chained list until finding a valid one
	{
		int i = 1;
		int socketfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol); // Create a socket 
		if (socketfd == -1) // Error checking
			continue;
		if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &i, sizeof(i)) == -1) // It is saying to say that we can reuse the localadress as a viable option before the required wait time expires (usefull when restarting the server)
			throw std::runtime_error("Fatal error: getaddrinfo");
		if (bind(socketfd, ai->ai_addr, ai->ai_addrlen) == 0) // Try to link the new socket with the addressinfo we found for out port. If success, we have a usable socket for our server and can get out of the init
		{
			this->_socketfd = socketfd;
			break;
		}
		close(socketfd);
	}
	if (ai == NULL) // If we at the end of the chainlist, bind didnt succeed;
		throw std::runtime_error("Fatal error: bind");
	freeaddrinfo(port_info); // Need to free the chained list
	if (listen(this->_socketfd, htons(atoi(this->_port.c_str()))) == -1)
		throw std::runtime_error("Fatal error: listen");
	if (fcntl(this->_socketfd, F_SETFL, O_NONBLOCK) == -1) // Setting our servers_socket on not_blocking when used
        	throw std::runtime_error("Fatal error: fcntl");
	pollfd spollfd; //
	spollfd.fd = this->_socketfd; // Creating the pollfd structure
	spollfd.events = POLLIN; // for our servers socket
	spollfd.revents = 0; //
	this->_pollfds.push_back(spollfd); // adding it in first place in our vector of pollfds
}	

void Server::exec()
{
	if (poll(&(*this->_pollfds.begin()), this->_pollfds.size(), -1) == -1) // poll takes a chain of fds to watch over, and wait for any of them to be ready to do some operations
		throw std::runtime_error(errnoMgmt("poll", "", errno));
	this->manageEvent(); // Calling the manager function to manage event that triggered poll unlocking
	this->displayState(); // Just beautifully display our servers state
}

void Server::manageEvent()
{
	for (size_t i = 0; i < this->_pollfds.size(); i++) // Iterate through our pollfds to check every single one of them to check if an event occured on one of them
	{
		pollfd currFd = this->_pollfds[i];
		if ((currFd.revents & POLLIN) == POLLIN) // POLLIN -> data waiting to be read
			if (this->acceptClient(currFd) == -1)
				continue;
		if ((currFd.revents & POLLHUP) == POLLHUP) // POLLHU -> deconnexion
			if (this->removeClient(currFd, i) == -1)
				continue;
	}
}

int Server::acceptClient(pollfd currFd)
{
	if (currFd.fd == this->_socketfd) // This part is to manage a new client
	{
		sockaddr_in clientAddr; // Create a client addr
		socklen_t socketLen = sizeof(clientAddr);
		memset(&clientAddr, 0, socketLen);
		int clientSocket = accept(this->_socketfd, (sockaddr*)&clientAddr, &socketLen); // removes the first in line at the listen on the server_socketfd with accept
		if (clientSocket == -1) // Error checking
			throw std::runtime_error(errnoMgmt("accept", "", errno));
		pollfd clientPollfd; // Each client get a pollfd so its in the pollfd vector (need this to communicate
		clientPollfd.fd = clientSocket; // Assigning the fd created with accept
		clientPollfd.events = POLLIN; // We starting with this flag so we expecting to read
		clientPollfd.revents = 0; // No event arrived at this point
		this->_pollfds.push_back(clientPollfd); // Putting the new struc in the vector
		if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1) // Managing the socket attributes 
			throw std::runtime_error("Fatal error: fcntl"); //so its not blocking while0 waiting for an event
		//std::cout << "New client connected. His socket: " << clientSocket << "\n";
		User* newUser = new User(clientSocket); // Creating an user on the new socket basis
		this->_users.push_back(newUser);
	}
	else // This part is to manage a message coming from an already existing client
	{
		try
		{
			User *currUser = findUserByFd(currFd.fd); // Run through our user vector
			this->commandManager(currUser, receiveMessage(currUser->getSocketFd())); // Call the command manager
		}
		catch (std::runtime_error &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return (0);
}

void Server::commandManager(User *user, std::string msg) // get the splitted arguments and call the _commands map
{
	size_t idx = 0;
	std::string delimiter = "\r\n";
	std::vector<std::string> split;
	while ((idx = msg.find(delimiter)) != std::string::npos)
	{
		split.push_back((msg.substr(0, idx) + "\n"));
		msg.erase(0, idx + delimiter.length());
	}
	if (split.empty())
		split.push_back(msg);
	for (size_t i = 0; i < split.size(); i++)
	{
		std::vector<std::string> args = getArgs(split[i]);
		//std::cout << "Message from " << user->getSocketFd() << " -> " << split[i];
		if (args.empty())
			return;
		std::string command = args[0];
		args.erase(args.begin());
		if (this->_cmds.count(command))
		{
			(this->*_cmds[command])(user, args);
			this->_counter++;
		}
		else if (command != "CAP" && command != "PING")
			this->message(user, 421, command);
	}
}

std::string Server::receiveMessage(int socketFd) // Receives and print the message from the client on the server
{
	char buffer[1048];
	memset(buffer, '\0', sizeof(buffer));
	ssize_t ret = recv(socketFd, buffer, sizeof(buffer), 0); // receives a message from socketfd and store it in the buffer
	if (ret <= 0)
	{
		this->deleteUser(this->findUserByFd(socketFd));
		throw std::runtime_error(errnoMgmt("recv", itoa(socketFd), errno)); // Error if ret is -1;
	}
	User *u = this->findUserByFd(socketFd);
	u->setInput(u->getInput() + buffer);
	if ((u->getInput().find("\n", 0) == std::string::npos))
		throw std::runtime_error("Incomplete cmd from the " + itoa(socketFd) + " file descriptor");
	std::string tmp = u->getInput();
	u->setInput("");
	return (tmp); 
}

void Server::deleteUser(User *user)
{
	std::vector<User *> users = std::vector<User *>();
	users.push_back(user);
        for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i]->userExist(user->getNick()))
		{
			std::vector<User*> tmp =this->_channels[i]->getUsers();
			for (size_t i = 0; i < tmp.size(); i++)
				if (std::find(users.begin(), users.end(), tmp[i]) == users.end())
					users.push_back(tmp[i]);
		}
	}
	std::vector<Channel *> chans = user->getChannels();
	for (size_t i = 0; i < chans.size(); i++)
	{
		user->leaveChannel(chans[i]->getName());
		chans[i]->deleteUser(user);
		if (chans[i]->empty())
			this->removeChannel(chans[i]);
	}
	std::string message = "QUIT :" + user->getDelMessage();
	for (size_t i = 0; i < users.size(); i++)
		users[i]->sendMessageVanilla(":" + user->getPrefix() + " " + message + "\r\n");
        for (std::vector<pollfd>::iterator it = this->_pollfds.begin(); it != this->_pollfds.end(); ++it)
        {
		if ((*it).fd == user->getSocketFd())
                {
			close(user->getSocketFd());
                        this->_pollfds.erase(it);
                        break;
                }
	}
	for (size_t i = 0; i < this->_users.size(); i++)
	{
		if (this->_users[i] == user)
		{
			this->_users.erase(this->_users.begin() + i);
			break;
		}
	}
        delete user;
}
