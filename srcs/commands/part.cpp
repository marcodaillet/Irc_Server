#include "../server/server.hpp"

void Server::commandpart(User *user, std::vector<std::string> &args) // Quit a channel
{
        if (!user->isLoggedIn()) // need to be logged in
                return (message(user, 484));
        if (args.size() == 0)
                return (message(user, 461, "PART"));
        std::vector<std::string> dest = getDest(args[0]);
	for (size_t i = 0; i < dest.size(); i++) // Iterate and leave all thos channels if they exist
        {
                Channel *tmp = findChannel(dest[i]);
                if (tmp == NULL)
                        message(user, 403, dest[i]);
		else
		{
			if (tmp->userExist(user->getNick())) // Needs to be inside in order to leave lol
                	{
                	        tmp->messageChannel2("PART " + tmp->getName() + (args.size() == 3 ? (" :" + args[2]) : ""), user);
                	        tmp->deleteUser(user); // Remove user
				user->leaveChannel(tmp->getName());
				if (tmp->empty())
					removeChannel(tmp);
                	}
                	else
                        	message(user, 442, dest[i]); // Error
		}
        }
}
