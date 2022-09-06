#include "../server/server.hpp"

void Server::commandnotice(User *user, std::vector<std::string> &args) // Like a a PRIVMSG but it doesnt trigger an automated reply
{
        if (!user->isLoggedIn()) // Still need to be logged in
        	return (this->message(user, 484));
	if (args.size() < 2) // <nickname> <text>
                return (this->message(user, 461, "NOTICE"));
	std::vector<std::string> dest = getDest(args[0]); // Might be several dest
        for (size_t i = 0; i < dest.size(); i++) // iteration
        {
                User *tmp = this->findUserByName(dest[i]); // Looks for the name of the user
                if (tmp != NULL) // If match just send the message
			tmp->sendMessage("NOTICE " + dest[i] + " :" + args[1], user);
                else // Else will look for a channel with this name
                {
                        if (dest[i][0] != '#')
			{
				message(user, 476, dest[i]);
				continue;
			}
			Channel *tmp = this->findChannel(dest[i]); // Same principle
                        if (tmp == NULL) // Mo match so error triggering
                        	message(user, 401, dest[i]);
                        if (tmp->getMode('n') && !tmp->userExist(user->getNick())) 
			{
				message(user, 404, dest[i]);
				continue;
			}
                        else
                                tmp->messageChannel("NOTICE " + dest[i] + " :" + args[1], user);
                }
        }
}
