#include "../server/server.hpp"

void Server::commandDeope(bool b, User *user)
{
	if (b == true)
		return ;
	for (size_t i = 0; i < this->_channels.size(); i++)
		this->_channels[i]->deleteOperator(user);
}

void Server::userMode(User *user, User *tmp, std::vector<std::string> &args)
{
	if (tmp->getNick() != user->getNick())
		return (message(user, 502));
	else if (args[1].size() < 2)
		return (message(user, 461, "MODE"));
	else
	{
		bool b = args[1][0] == '-' ? false : true;
		for (size_t i = 1; i < args[1].size(); i++)
		{
			if (args[1][i] == 'o')
				this->commandDeope(b, user);
			else if (args[1][i] == 'i' || args[1][i] == 'a')
				user->setMode(args[1][i], b);
			else
				return (message(user, 472, ""));
		}
	}
	std::string m = user->getModesStr();
	return (message(user, 221, "+" + m));
}

void Server::channelMode(User *user, Channel *tmp, std::vector<std::string> &args)
{
	if (args.size() > 1)
	{
		if (!tmp->isOperator(user))
			return (message(user, 482, user->getNick()));
		size_t opt = 0;
		bool b = args[1][0] == '-' ? false : true;
		std::set<char> tmp_s;
		for (size_t i = 1; i < args[1].size(); i++)
		{
			tmp_s.insert(args[1][i]);
			if ((b == true && (args[1][i] == 'k' || args[1][i] == 'l')) || args[1][i] == 'o')
				opt++;
		}
		std::vector<std::string> options;
		if (opt && args.size() < 3)
			return (message(user, 461, "MODE"));
		options = getDest(args[2]);
		for (size_t i = 0; i < options.size(); i++)
			std::cout << options[i] << "\n";
		if (opt && (options.size() != opt))
			return (message(user, 461, "MODE"));
		opt = 0;
		for (std::set<char>::iterator it = tmp_s.begin(); it != tmp_s.end(); it++)
		{
			if (*(it) == 'o')
			{
				User *tmp2 = this->findUserByName(options[opt]);
				if (tmp2 == NULL)
					return (message(user, 401, options[opt]));
				else if (!tmp->userExist(tmp2->getNick()))
					return (message(user, 442, options[opt]));
				else if (b == false && !tmp->isOperator(tmp2))
					return (message(user, 482, options[opt]));
				b == true ? tmp->addOperator(tmp2) : tmp->deleteOperator(tmp2);
				opt++;
			}
			else if (*(it) == 'k')
			{
				tmp->setMode('k', b);
				tmp->setPassword(b == true ? options[opt++] : "");
			}
			else if (*(it) == 'l')
			{
				tmp->setMode('l', b);
				tmp->setLimit(b == true ? atoi(options[opt++]) : 2147483647);
			}
			else if (*(it) != 's' && *(it) != 't' && *(it) != 'i' && *(it) != 'n')
				return (message(user, 472, ""));
			else
				tmp->setMode(*(it), b);
		}
	}
	std::string m = tmp->getModesStr();
	return (message(user, 324, args[0], "+" + m, ""));
}

void Server::commandmode(User *user, std::vector<std::string> &args)
{
	if (!user->isLoggedIn())
		return (message(user, 484));
	if (args.size() == 0)
		return (message(user, 461, "MODE"));
	User *tmp = this->findUserByName(args[0]);
	if (tmp != NULL)
		this->userMode(user, tmp, args);
	else
	{
		if (args[0][0] != '#')
			return (message(user, 476, args[0]));
		Channel *tmp = this->findChannel(args[0]);
		if (tmp != NULL)
			this->channelMode(user, tmp, args);
		else
			return (message(user, 403, args[0]));
	}
}
