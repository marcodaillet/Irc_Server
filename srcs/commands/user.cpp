#include "../server/server.hpp"

void Server::commanduser(User *user, std::vector<std::string> &args) // Log In command <nickname> <host> <server_name> <real_name>
{
	if (!user->hasNick()) // To enter the user details, the user need to set its nickname firts
                return (this->message(user, 484));
        if (args.size() < 4) // Need the right number of info
                return (this->message(user, 461, "USER"));
        if (user->isLoggedIn()) // Cannot log in two times
                return (this->message(user, 462));
        user->setUserName(args[0]);
        user->setHost(args[1]);
	user->setRealName(args[3]); // Gives us the right name
        user->setIsLoggedIn(true); // Set the bool to true
	this->commandmotd(user, args);
}
