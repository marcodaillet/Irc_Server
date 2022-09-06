#include "../server/server.hpp"

void Server::commandjoin(User *user, std::vector<std::string> &args) // Try to join a channel
{
	if (!user->isLoggedIn()) // Needs to be logged in to join a chan
		return (message(user, 484));
	if (args.size() == 0) // Only one param expected (might be several channels but only separated by commas)
		return (message(user, 461, "JOIN"));
	std::vector<std::string> chans = getDest(args[0]);
	std::vector<std::string> pwds = args.size() > 1 ? getDest(args[1]) : std::vector<std::string>();
	std::vector<std::string>::iterator pwds_it = pwds.begin();
	for (size_t i = 0; i < chans.size(); i++) // Run through the vector of destinations of command
	{
		if (chans[i][0] != '#')
		{
			message(user, 476, chans[i]);
			continue;
		}
		Channel *tmp = this->findChannel(chans[i]); // Looks to see if there is a match
		if (tmp == NULL)
			tmp = this->createChannel(user, chans[i]); // If no chan join creates a chan with the user as op
		else
		{
			std::string key = pwds_it != pwds.end() ? *pwds_it++ : "";
			if (tmp->userExist(user->getNick()))
			{
				message(user, 443, user->getNick(), tmp->getName());
				continue;
			}
			if (tmp->getMode('i') && !tmp->isInv(user))
			{
				message(user, 473);
				continue;
			}
			if (tmp->getMode('k') && key != tmp->getPassword())
			{
				message(user, 475, tmp->getName(), user->getNick());
				continue;
			}
			if (tmp->getMode('l') && tmp->getNumberUser() == tmp->getLimit())
			{
				message(user, 471);
				continue;
			}
			user->addChannel(tmp); // Add
			tmp->addUser(user); // Add
			if (tmp->getMode('i'))
				tmp->deleteInv(user);
		}
		std::string mode;
		if (tmp->getMode('s'))
			mode = "@";
		else
			mode = "=";
		if (tmp->getTopic().length())
			message(user, 332, tmp->getName(), tmp->getTopic());
		message(user, 353, mode, tmp->getName(), this->getUserNames(tmp, user));
		message(user, 366, tmp->getName());
		tmp->messageChannel2("JOIN :" + tmp->getName(), user);
	}
}
