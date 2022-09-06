#include "../server/server.hpp"

void Server::commandlist(User *user, std::vector<std::string> &args) // Simply list all channels that are not private
{
	if (!user->isLoggedIn()) // Needs to be logged to see the chans
                return (message(user, 484));
	message(user, 321);
	if (args.size() == 1)
	{
		std::vector<std::string> dest = getDest(args[0]);
        	for (size_t i = 0; i < dest.size(); i++) // Iterate and leave all thos channels if they exist
        	{
			if (dest[i][0] != '#')
                        	dest[i] = "#" + dest[i];
                	Channel *tmp = findChannel(dest[i]);
                	if (tmp == NULL)
				message(user, 403, dest[i]);
			if (tmp->getMode('s') && !tmp->userExist(user->getNick()))
				continue;
			message(user, 322, tmp->getName(),  itoa(tmp->getNumberUserList()), tmp->getTopic().empty() ? "No topic set" : tmp->getTopic());
		}
	}
	else
	{
		for (size_t i = 0; i < this->_channels.size(); i++) // iterate through the channels and print them at the user
	     	{
			Channel *tmp = this->_channels[i];
			if (tmp->getMode('s') && !tmp->userExist(user->getNick()))
				continue ;
			message(user, 322, tmp->getName(),  itoa(tmp->getNumberUserList()), tmp->getTopic().empty() ? "No topic set" : tmp->getTopic());
		}
	}
	message(user, 323);
}
