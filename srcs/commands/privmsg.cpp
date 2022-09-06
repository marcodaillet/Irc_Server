#include "../server/server.hpp"

void Server::commandprivmsg(User *user, std::vector<std::string> &args) // Sends a message directly to another user
{
	if (!user->isLoggedIn()) // Still need to be logged in
                return (this->message(user, 484));
        if (args.size() < 2) // <nickname> <text>
                return (this->message(user, 461, "PRIVMSG"));
        std::vector<std::string> dest = getDest(args[0]); // Might be several dest
        for (size_t i = 0; i < dest.size(); i++) // iteration
        {
                User *tmp = this->findUserByName(dest[i]); // Looks for the name of the user
                if (tmp != NULL) // If match just send the message
                {
			tmp->sendMessage("PRIVMSG " + dest[i] + " :" + args[1], user);
			if (tmp->getMode('a'))
				this->message(user, 301, tmp->getNick(), tmp->getAwayMsg());
		}
                else // Else will look for a channel with this name
                {
                        if (dest[i][0] != '#')
			{
				message(user, 476, dest[i]);
				continue;
			}
			Channel *tmp = this->findChannel(dest[i]); // Same principle
                        if (tmp == NULL) // Mo match so error triggering
                                return (this->message(user, 401, dest[i]));
                	if (tmp->getMode('n') && !tmp->userExist(user->getNick())) 
			{
				message(user, 404, dest[i]);
				continue;
			}
                        else
                                tmp->messageChannel("PRIVMSG " + dest[i] + " :" + args[1], user);
		}
        }
}
