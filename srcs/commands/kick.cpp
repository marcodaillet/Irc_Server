#include "../server/server.hpp"

void Server::commandkick(User *user, std::vector<std::string> &args) // Needs to be an operator to kick someone
{// <channel> <user> {<comment>}
        if (!user->isLoggedIn()) // Needs to be logged in first
                return (message(user, 484));
        if (args.size() < 2) // Need at least 2 args
                return (message(user, 461, "KICK"));
	std::vector<std::string> chans = getDest(args[0]);
	std::vector<std::string> users = getDest(args[1]);
	for (size_t i = 0; i < chans.size(); i++)
	{
		if (chans[i][0] != '#')
	        {
			message(user, 476, chans[i]);
			continue;
		}
		Channel *chan = findChannel(chans[i]); // Finds the channel
	        if (chan == NULL) // If no chan with this name error
	                return (message(user, 401, chans[i]));
	        if (!chan->isOperator(user)) // Need ope rights
	        {
			message(user, 482, chans[i]);
			continue;
		}
	        else
	        {
			for (size_t i = 0; i < users.size(); i++)
			{
		                User *tmp = this->findUserByName(users[i]); // Find the target
		                if (tmp == NULL)
		                {
					message(user, 441, chans[i], users[i]);
		                        continue ;
		                }
		                else // if no match proper error sent
		                {
					chan->messageChannel2(("KICK " + chans[i] + " " + users[i] + " :" + (args.size() == 3 ? args[2] : " kicked")), user);
					chan->deleteUser(tmp);
					tmp->leaveChannel(chan->getName());
				}
			}
	        }
	}
}
