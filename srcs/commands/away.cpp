#include "../server/server.hpp"

void Server::commandaway(User *user, std::vector<std::string> &args) // Set a user as AFK (or unset it)
{
        if (!user->isLoggedIn()) // Still needs to be logged in
                return (message(user, 482));
        if (args.size() == 1) // Case setting AFK
        {
                user->setAwayMsg(args[0]); // Set away message
		user->setMode('a', true);
		return (message(user, 306));
        }
        else if (args.empty()) // Case unsetting AFK
        {
                user->setAwayMsg(""); // Set message to nothing
		user->setMode('a', false);
                return (message(user, 305));
        }
	else
                return (message(user, 461, "AWAY"));
}
