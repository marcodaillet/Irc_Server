#include "../server/server.hpp"

std::string Server::RPL_WELCOME(std::string nick) {
	return (":Welcome to the Internet Relay Network " + nick); }
std::string Server::RPL_UMODEIS(std::string mode) {
	return (mode); }
std::string Server::RPL_AWAY(std::string nick, std::string message) {
	return (nick + " :" + message); }
std::string Server::RPL_UNAWAY() {
	return (":You are no longer marked as being away"); }
std::string Server::RPL_NOWAWAY() {
	return (":You have been marked as being away"); }
std::string Server::RPL_WHOISUSER(std::string nick, std::string user, std::string host, std::string real) {
	return (nick + " " + user + " " + host + " * :" + real); }
std::string Server::RPL_WHOISSERVER(std::string nick, std::string server, std::string info) {
	return (nick + " " + server + " :" + info); }
std::string Server::RPL_WHOISOPERATOR(std::string nick) {
	return (nick + " :is an IRC operator"); }
std::string Server::RPL_ENDOFWHO(std::string name) {
	return (name + " :End of /WHO list"); }
std::string Server::RPL_ENDOFWHOIS(std::string nick) {
	return (nick + " :End of /WHOIS list"); }
std::string Server::RPL_WHOISCHANNELS(std::string nick, std::string channel) {
	return (nick + " :" + channel); }
std::string Server::RPL_LISTSTART() {
	return ("Channel :Users  Name"); }
std::string Server::RPL_INVITING(std::string chan, std::string nick) {
	return (chan + " " + nick); }
std::string Server::RPL_LIST(std::string channel, std::string nbrUser, std::string topic) {
	return (channel + " " + nbrUser + " :" + topic); }
std::string Server::RPL_LISTEND() {
	return (":End of /LIST"); }
std::string Server::RPL_CHANNELMODEIS(std::string channel, std::string mode, std::string params) {
	return (channel + " " + mode + " " + params); }
std::string Server::RPL_NOTOPIC(std::string channel) {
	return (channel + " :No topic is set"); }
std::string Server::RPL_TOPIC(std::string channel, std::string topic) {
	return (channel + " :" + topic); }
std::string Server::RPL_WHOREPLY(std::string channel, std::string user, std::string host, std::string server, std::string nick, std::string state, std::string real) {
	return (channel + " " + user + " " + host + " " + server + " " + nick + " " + state + " :0 " + real); }
std::string Server::RPL_NAMREPLY(std::string chan_mod, std::string channel, std::string nick_list) {
	return (chan_mod + " " + channel + " :" + nick_list); }
std::string Server::RPL_ENDOFNAMES(std::string channel) {
	return (channel + " :End of /NAMES list"); }
std::string Server::RPL_ENDOFWHOWAS(std::string nick) {
	return (nick + " :End of WHOWAS"); }
std::string Server::RPL_MOTD(std::string text) {
	return (":- " + text); }
std::string Server::RPL_MOTDSTART(std::string server) {
	return (":- " + server + " Message of the day - "); }
std::string Server::RPL_ENDOFMOTD() {
	return (":End of /MOTD command"); }

std::string Server::ERR_NOSUCHNICK(std::string nickname) {
	return (nickname + " :No such nick/channel"); }
std::string Server::ERR_NOSUCHSERVER(std::string server) {
	return (server + " :No such server"); }
std::string Server::ERR_NOSUCHCHANNEL(std::string channel) {
	return (channel + " :No such channel"); }
std::string Server::ERR_CANNOTSENDTOCHAN(std::string channel) {
	return (channel + " :Cannot send to channel"); }
std::string Server::ERR_TOOMANYCHANNELS(std::string channel) {
	return (channel + " :You have joined too many channels"); }
std::string Server::ERR_WASNOSUCHNICK(std::string nickname) {
	return (nickname + " :There was no such nickname"); }
std::string Server::ERR_NORECIPIENT(std::string command) {
	return (":No recipient given (" + command + ")"); }
std::string Server::ERR_NOTEXTTOSEND() {
	return (":No text to send"); }
std::string Server::ERR_BADCHANMASK(std::string channel) {
	return (channel + " :Bad Channel Mask"); }
std::string Server::ERR_UNKNOWNCOMMAND(std::string command) {
	return (command + " :Unknown command"); }
std::string Server::ERR_NONICKNAMEGIVEN() {
	return (":No nickname given"); }
std::string Server::ERR_ERRONEUSNICKNAME(std::string nick) {
	return (nick + " :Erroneus nickname"); }
std::string Server::ERR_NICKNAMEINUSE(std::string nick) {
	return (nick + " :Nickname is already in use"); }
std::string Server::ERR_USERNOTINCHANNEL(std::string nick, std::string channel) {
	return (nick + " " + channel + " :They aren't on that channel"); }
std::string Server::ERR_NOTONCHANNEL(std::string channel) {
	return (channel + " :You're not on that channel"); }
std::string Server::ERR_USERONCHANNEL(std::string user, std::string channel) {
	return (user + " " + channel + " :is already on channel"); }
std::string Server::ERR_NOTREGISTERED() {
	return (":You have not registered"); }
std::string Server::ERR_NEEDMOREPARAMS(std::string command) {
	return (command + " :Not enough parameters"); }
std::string Server::ERR_ALREADYREGISTERED() {
	return (":You may not reregister"); }
std::string Server::ERR_PASSWDMISMATCH() {
	return (":Password incorrect"); }
std::string Server::ERR_CHANNELISFULL(std::string channel) {
	return (channel + " :Cannot join channel (+l)"); }
std::string Server::ERR_UNKNOWNMODE(std::string c) {
	return (c + " :is unknown mode char to me"); }
std::string Server::ERR_INVITEONLYCHAN(std::string channel) {
	return (channel + " :Cannot join channel (+i)"); }
std::string Server::ERR_BANNEDFROMCHAN(std::string channel) {
	return (channel + " :Cannot join channel (+b)"); }
std::string Server::ERR_BADCHANNELKEY(std::string channel) {
	return (channel + " :Cannot join channel (+k)"); }
std::string Server::ERR_RESTRICTED() {
	return (":Your connection is restricted!"); }
std::string Server::ERR_CHANOPRIVSNEEDED(std::string channel) {
	return (channel + " :You're not channel operator"); }
std::string Server::ERR_UMODEUNKNOWNFLAG() {
	return (":Unknown MODE flag"); }
std::string Server::ERR_USERSDONTMATCH() {
	return (":Cant change mode for other users"); }
