#include "../server/server.hpp"

void Server::commandtopic(User *user, std::vector<std::string> &args) // Gets the topic if size == 1 or set it if topic == 2
{
        if (!user->isLoggedIn()) // Needs to be logged in
                return (message(user, 484));
        if (args.size() == 0) // Checking the number of args
                return (message(user, 461, "TOPIC"));
        if (args[0][0] != '#')
		return (message(user, 476, args[0]));
	Channel *tmp = this->findChannel(args[0]); // Look for the chan
        if (tmp != NULL)
        {
		if (tmp->getMode('t') == true && !tmp->isOperator(user) && args.size() == 2)
			return (message(user, 482, tmp->getName()));
                if (tmp->userExist(user->getNick())) // Check that the the user is in channel
                {
                        std::string topic = args.size() == 1 ? tmp->getTopic() : tmp->setGetTopic(args[1]);
                        if (args.size() == 1)
                                return(message(user, 332, tmp->getName(), topic)); // ret to user
                        else {
                                std::vector<User *> u = tmp->getUsers();
                                for (size_t i = 0; i < u.size(); i++)
                                        message(u[i], 332, tmp->getName(), topic); // ret to user
                                return ;
                        }
                }
                else
                	return (message(user, 442, args[0])); // error chan doesnt exist
        }
        else
                return (message(user, 403, args[0])); // error chan doesnt exist
}