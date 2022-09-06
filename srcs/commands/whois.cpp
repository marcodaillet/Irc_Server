#include "../server/server.hpp"

void Server::commandwhois(User *user, std::vector<std::string> &args)
{
	if (args.size() == 0)
		return (message(user, 431));
	std::string channel_names;
	std::vector<std::string> dest = getDest(args[0]);
	for (size_t i = 0; i < dest.size(); i++)
	{
		std::string tmp2 = dest[i];
		User *target = findUserByName(tmp2);
		if (target == NULL)
		{
			message(user, 401, tmp2);
			message(user, 318, tmp2);
			continue ;
		}
		message(user, 311, tmp2, target->getUserName(), target->getHost(), target->getRealName());
		for (size_t i = 0; i < this->_channels.size(); i++)
		{	
			Channel* tmp = this->_channels[i];
			if (tmp->userExist(tmp2) && !target->getMode('i'))
				channel_names += tmp->getName() + " ";
		}
		if (channel_names.length())
			message(user, 319, channel_names);
		message(user, 318, tmp2);
	}
}
