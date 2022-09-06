#include "../server/server.hpp"

void Server::commandhelp(User *user, std::vector<std::string> &args)
{
	(void)args;
	user->sendMessageVanilla("PASS <password> - Enter the server's password\r\n");
	user->sendMessageVanilla("NICK <nickname> - Set or change your current nickname\r\n");
	user->sendMessageVanilla("JOIN <channel>{,<channel>} [<key>] - Create or join a channel optionnally with a key\r\n");
	user->sendMessageVanilla("KICK <channel> <user> [:<message>] - Kick an user from a channel with an optionnal message\r\n");
	user->sendMessageVanilla("LIST [<channel>{,<channel>}] - Shows a list of all the visible channels on the server and their topic\r\n");
	user->sendMessageVanilla("NOTICE <nickname/channel> :<message> - Sends a message to an user or a channel\r\n");
	user->sendMessageVanilla("PART <channel>{,<channel>} - Leave a channel\r\n");
	user->sendMessageVanilla("PRIVMSG <nickname/channel>{,<nickname/channel>} :<message> - Sends a message to a user or a channel\r\n");
	user->sendMessageVanilla("QUIT [:<message>] - Quits the server and optionnaly leaves a message\r\n");
	user->sendMessageVanilla("USER <nickname> <host> <server name> :<realname> - Register a user in the server\r\n");
	user->sendMessageVanilla("TOPIC <channel> [<topic>] - Get or set the topic of a channel\r\n");
	user->sendMessageVanilla("MODE <channel> {[+|-]|s|i|k|o} [<nickname>] [<key>]- Allow channel operator to change the channel's modes\r\n");
	user->sendMessageVanilla("MODE <nickname> {[+|-]|i|o} - Allow a user to change his own modes\r\n");
	user->sendMessageVanilla("AWAY [:<message>] - Define or remove the away from keyboard message\r\n");
	user->sendMessageVanilla("INVITE <nickname> <channel> - Invite a user on a channel if the channels mode is invite\r\n");
	user->sendMessageVanilla("NAMES <channel> {,<channel>} - Get a list of all non-invisible users on a channel\r\n");
}
