#include "../server/server.hpp"

bool isAlpha(char c) { return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'); }
bool isSpecialChar(char c) { return (c >= '[' && c <= '`') || (c >= '{' && c <= '}'); }
bool isDigit(char c) { return (c >= '0' && c <= '9'); }

void Server::commandnick(User *user, std::vector<std::string> &args) // Set the nickname
{
	if (!user->hasPassword())
		return (message(user, 484));
        if (args.empty())
                return (message(user, 431));
	if (args[0].size() > 9 || (!isAlpha(args[0][0]) && !isSpecialChar(args[0][0])))
		return (message(user, 432, args[0]));
	for (size_t i = 0; i < args[0].size(); i++)
		if (!isAlpha(args[0][i]) && !isSpecialChar(args[0][i]) && !isDigit(args[0][i]) && args[0][i] != '-')
			return (message(user, 432, args[0]));
        if (this->findUserByName(args[0])) // Cannot have 2 same nick_named users
                return (message(user, 433, (args[0])));
	std::vector<User *> users = std::vector<User *>();
	users.push_back(user);
	for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i]->userExist(user->getNick()))
		{
			std::vector<User *> tmp = this->_channels[i]->getUsers();
			for (size_t i = 0; i < tmp.size(); i++)
				users.push_back(tmp[i]);
		}
	}
	std::string msg = ":" + user->getPrefix() + " " + "NICK :" + args[0] + "\r\n";
	for (size_t i = 0; i < users.size(); i++)
		users[i]->sendMessageVanilla(msg);
	user->setNick(args[0]);
        user->setHasNick(true);
}
