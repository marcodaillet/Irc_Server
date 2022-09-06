#include "../server/server.hpp"

void Server::commandnames(User *user, std::vector<std::string> &args)
{
	if (!user->isLoggedIn()) // Needs to be logged to see the chans
		return (this->message(user, 484));
	std::vector<std::string> dest = args.empty() ? this->getChanNames() : this->getDest(args[0]);
	for (size_t i = 0; i < dest.size(); i++) // iterate through the channels and print them at the user
	{
		if (dest[i][0] != '#')
		{
			message(user, 476, dest[i]);
			continue ;
		}
		Channel *chan = this->findChannel(dest[i]);
		if (chan == NULL)
			return (message(user, 403, dest[i]));
		else if (chan->getMode('s') && !chan->userExist(user->getNick()))
			continue ;
		else
		{
			std::string users = this->getUserNames(chan, user);
			if (users.size())
				message(user, 353, (chan->getMode('s') ? "*" : "="), chan->getName(), users);
		}
       	}
	message(user, 366);
}
