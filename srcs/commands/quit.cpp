#include "../server/server.hpp"

void Server::commandquit(User *user, std::vector<std::string> &args) // Simply quit the serverf
{
	user->setDelMessage(args.size() == 0 ? "Client Quit" : args[0]);
	this->deleteUser(user);
}
