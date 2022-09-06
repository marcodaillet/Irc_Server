#include "server.hpp"

User *Server::findUserByFd(int userFd) const // Pretty straightforward
{
	for (size_t i = 0; i < this->_users.size(); i++)
		if (this->_users[i]->getSocketFd() == userFd)
			return (this->_users[i]);
        return (NULL);
}

User *Server::findUserByName(const std::string &name) const
{
	for (size_t i = 0; i < this->_users.size(); i++)
		if (this->_users[i]->getNick() == name)
                        return (this->_users[i]);
        return (NULL);

}

Channel *Server::findChannel(const std::string &name) const
{
	for (size_t i = 0; i < this->_channels.size(); i++)
                if (this->_channels[i]->getName() == name)
                        return (this->_channels[i]);
        return (NULL);
}

int Server::removeClient(pollfd currFd, int index) // Remove a client from our lists
{
        User *user = findUserByFd(currFd.fd); // Find our User in our user vector
        if (user == NULL)
                return (-1);
        this->removeUser(user);
        close(this->_pollfds[index].fd);
        this->_pollfds.erase(this->_pollfds.begin() + index);
        return (0);
}

void Server::removeClientBySocket(int socketFd)
{
	User *user = findUserByFd(socketFd);
	if (user == NULL)
		return ;
	this->removeUser(user);
	close(socketFd);
	removePollfd(socketFd);
}

void Server::removeUser(User *user) // Also pretty straightforward
{
	for (size_t i = 0; i < this->_users.size(); i++)
	{
                if (this->_users[i] == user)
                {
                        this->_users[i]->leaveAllChannels();
                        this->_users.erase(this->_users.begin() + i);
                        break ;
                }
        }
}

void Server::removePollfd(int fd)
{
	for (size_t i = 0; i < this->_pollfds.size(); i++)
        {
                if (_pollfds[i].fd == fd)
                {
                        _pollfds.erase(_pollfds.begin() + i);
                        break;
                }
        }
}

void Server::removeChannel(Channel *channel) // Also pretty straightforward
{
	for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i] == channel)
                {
                        this->_channels[i]->deleteAllUsers();
                        this->_channels.erase(this->_channels.begin() + i);
                        break ;
                }
        }
	delete channel;
}

std::vector<std::string> Server::getDest(std::string &arg) // Splitting the args based on "," because some
{ //commands might be called on several targets sepparated by a "."
        std::vector<std::string> ret;
        size_t idx = 0;
        size_t n_idx = 0;
        size_t space = arg.size() - 1;
        while (space != 0 && arg[space] == 32) // Removing the space(s) at the end
                space--;
        if (space != 0) // Cutting the substr if spaces have been found
                arg = arg.substr(0, space + 1); 
        while (n_idx != arg.npos) // Cutting loop
        {
                n_idx = arg.find(',', idx);
                if (n_idx == arg.npos) // If we at the end we just push the rest
                        ret.push_back(arg.substr(idx));
                else
                        ret.push_back(arg.substr(idx, n_idx - idx)); // we push the in beetween ","
                idx = n_idx + 1; // Move the cursor
        }
        return (ret);
}

std::vector<std::string> Server::getChanNames(void)
{
	std::vector<std::string> ret;
	for (size_t i = 0; i < this->_channels.size(); i++)
		ret.push_back(this->_channels[i]->getName());
	return (ret);
}

std::string Server::getUserNames(Channel *chan, User *user)
{
	std::string ret = "";
	std::vector<User *> users = chan->getUsers();
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->getMode('i') && users[i] != user)
			continue;
		if (ret.size())
			ret += " ";
		if (chan->isOperator(users[i]))
			ret += "@";
		ret += users[i]->getNick();
	}
	return (ret);
}

Channel* Server::createChannel(User *creator, std::string channel_name)
{
	Channel *channel = new Channel(channel_name); // Create a new object chanel
	this->_channels.push_back(channel);
	channel->addUser(creator); // Add the creator at the list of user
        channel->addOperator(creator); // Creator will be operator
        creator->addChannel(channel); // Add the new channel at the users list
	return (channel);
}

std::vector<std::string> Server::getArgs(std::string message) // Split the string received in different arguments stored in a vector for more convenience
{
	size_t idx = 0;
	size_t n_idx = 0;
	std::vector<std::string> ret;
	std::string last;

	n_idx = message.find("\r\n");
	if (n_idx != std::string::npos)
	       message = message.substr(0, n_idx);
	else
	{
		n_idx= message.find('\n');
		if (n_idx != std::string::npos)
			message = message.substr(0, n_idx);
	}
	if (message.empty())
		return (ret);
	size_t spaces = message.length() - 1;
	while (message[spaces] == 32 && spaces != 0) // Remove spaces at the end
		spaces--;
	if (spaces != 0)
		message = message.substr(0, spaces + 1); // Cut the string properly
	n_idx = message.find(":", 0); // See the ":" role in the RFC1459
	if (n_idx != std::string::npos)
	{
		last = message.substr(n_idx + 1);
		message.erase(n_idx);
	}
	int i;
	for (i = 0; ;i++)
	{
		n_idx = message.find(' ', idx);
		if (n_idx == std::string::npos)
		{
			ret.push_back(message.substr(idx, n_idx - idx));
			break;
		}
		ret.push_back(message.substr(idx, n_idx - idx));
		while (message[n_idx + 1] && message[n_idx + 1] == 32)
			n_idx++;
		idx = n_idx + 1;
	}
	if (!last.empty())
		ret[i] = last;
	return (ret);
}

void Server::displayState(void)
{
	system("clear");
	std::cout << Bwhite("Current IRC State") << std::endl << std::endl;
	std::cout << "Number of channels: " << Bwhite(itoa(this->_channels.size())) << std::endl;
	std::cout << "Number of users: " << Bwhite(itoa(this->_users.size())) << std::endl;
	std::cout << "Number of treated commands: " << Bwhite(itoa(this->_counter)) << std::endl << std::endl;
	std::cout << "FD  |  NICKNAME" << std::endl;
	for (size_t i = 0; i < this->_users.size(); i++)
		std::cout << green(itoa(this->_users[i]->getSocketFd())) << "   |  " << cyan(this->_users[i]->getNick()) << std::endl;
}

void Server::message(User *user, unsigned short code, std::string arg1, std::string arg2, std::string arg3, std::string arg4, std::string arg5, std::string arg6, std::string arg7)
{
	std::string scode = itoa(code);
	while (scode.size() != 3)
		scode = "0" + scode;
	user->sendMessage(scode + " " + this->getCodeMessage(user, code, arg1, arg2, arg3, arg4, arg5, arg6, arg7), user);
}

std::vector<User *> Server::getUsers(void) const
{
	return (this->_users);
}
