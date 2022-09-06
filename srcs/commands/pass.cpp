#include "../server/server.hpp"

void Server::commandpass(User *user, std::vector<std::string> &args) // Enters the password for the server to accept the connection
{
	if (user->hasPassword() == true)
		return (message(user, 462));
        if (args.empty()) // We need a password, it cannot be empty
                return (message(user, 461, "PASS"));
        if (args[0] != this->_pwd) // If mismatch in the password we throw the erro
		return (message(user, 485));	
	user->setHasPassword(true); // If all good we sent the bool pwd on true
}
