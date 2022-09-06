#pragma once

#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP

#include "../utils/libs.hpp"
#include "../user/user.hpp"
#include "../channel/channel.hpp"

class User;
class Channel;

class Server
{
	private:
		int _socketfd;
		int _counter;
		const std::string _port;
		const std::string _pwd;

		std::vector<pollfd> _pollfds;
		std::vector<User *> _users;
		std::vector<Channel *> _channels;
		typedef void(Server::*command)(User*, std::vector<std::string> &args);
		std::map<std::string, command> _cmds;
	public:
		Server(const std::string &port, const std::string &pwd);
		~Server();
		void deleteUser(User *user);

		void init();
		void exec();
		void manageEvent();
		
		User* findUserByFd(int userFd) const;
		User* findUserByName(const std::string &name) const;
		Channel* findChannel(const std::string &name) const;
		std::vector<User *> getUsers() const;

		void removeUser(User *user);
		void removePollfd(int fd);
		void removeClientBySocket(int socketFd);
		void removeChannel(Channel *channel); 
		int removeClient(pollfd currfd, int index);

		std::string receiveMessage(int socketFd);
		void commandManager(User *user, std::string str);
		Channel *createChannel(User *creator, std::string name);
		int acceptClient(pollfd currFd);	
		void displayState();

		std::vector<std::string> getDest(std::string &arg);
		std::vector<std::string> getArgs(std::string message);
		std::vector<std::string> getChanNames(void);
		std::string getUserNames(Channel *chan, User *user);
		std::string getLeavingMessage(std::vector<std::string> &args, User *user, std::string chan);
		std::string getCodeMessage(User* user, unsigned short code, std::string arg1, std::string arg2, std::string arg3, std::string arg4, std::string arg5, std::string arg6, std::string arg7 = "");
		void message(User *user, unsigned short code, std::string arg1 = "", std::string arg2 = "", std::string arg3 = "", std::string arg4 = "", std::string arg5 = "", std::string arg6 = "", std::string arg7 = "");

		void commandpass(User *user, std::vector<std::string> &args);
		void commanduser(User *user, std::vector<std::string> &args);
		void commandnick(User *user, std::vector<std::string> &args);
		void commandprivmsg(User *user, std::vector<std::string> &args);
		void commandjoin(User *user, std::vector<std::string> &args);
		void commandlist(User *user, std::vector<std::string> &args);
		void commandnotice(User *user, std::vector<std::string> &args);
		void commandkick(User *user, std::vector<std::string> &args);
		void commandaway(User *user, std::vector<std::string> &args);
		void commandtopic(User *user, std::vector<std::string> &args);
		void commandquit(User *user, std::vector<std::string> &args);
		void commandpart(User *user, std::vector<std::string> &args);
		void commandinvite(User *user, std::vector<std::string> &args);
		void commandnames(User *user, std::vector<std::string> &args);
		void commandmode(User *user, std::vector<std::string> &args);
		void userMode(User *user, User *tmp, std::vector<std::string> &args);
		void channelMode(User *user, Channel *tmp, std::vector<std::string> &args);
		void commandhelp(User *user, std::vector<std::string> &args);
		void commandmotd(User *user, std::vector<std::string> &args);
		void commandwhois(User *user, std::vector<std::string> &args);
		void commandDeope(bool b, User *user);

		std::string RPL_WELCOME(std::string prefix);
		std::string RPL_UMODEIS(std::string mode);
		std::string RPL_AWAY(std::string nick, std::string message);
		std::string RPL_UNAWAY();
		std::string RPL_NOWAWAY();
		std::string RPL_WHOISUSER(std::string nick, std::string user, std::string host, std::string real);
		std::string RPL_WHOISOPERATOR(std::string nick);
		std::string RPL_ENDOFWHOIS(std::string nick);
		std::string RPL_WHOISCHANNELS(std::string nick, std::string channel);
		std::string RPL_LISTSTART();
		std::string RPL_LIST(std::string channel, std::string nbrUser, std::string topic);
		std::string RPL_LISTEND();
		std::string RPL_CHANNELMODEIS(std::string channel, std::string mode, std::string params);
		std::string RPL_NOTOPIC(std::string channel);
		std::string RPL_TOPIC(std::string channel, std::string topic);
		std::string RPL_INVITING(std::string channel, std::string nick);
		std::string RPL_INVITELIST(std::string channel, std::string inviter);
		std::string RPL_ENDOFINVITELIST(std::string channel);
		std::string RPL_WHOREPLY(std::string channel, std::string user, std::string host, std::string server, std::string nick, std::string state, std::string real);
		std::string RPL_NAMREPLY(std::string chan_mod, std::string channel, std::string nick_list);
		std::string RPL_ENDOFNAMES(std::string channel);
		std::string RPL_ENDOFWHOWAS(std::string nick);
		std::string RPL_MOTD(std::string text);
		std::string RPL_MOTDSTART(std::string server);
		std::string RPL_ENDOFMOTD();
		std::string RPL_USERS();
		std::string RPL_ENDOFUSERS();
		std::string RPL_NOUSERS();
		std::string RPL_WHOISSERVER(std::string nick, std::string server, std::string info);
		std::string RPL_WHOWASUSER(std::string nick, std::string user, std::string host, std::string real);
		std::string RPL_ENDOFWHO(std::string name);
		std::string ERR_NOSUCHNICK(std::string nickname);
		std::string ERR_NOSUCHSERVER(std::string server);
		std::string ERR_NOSUCHCHANNEL(std::string channel);
		std::string ERR_CANNOTSENDTOCHAN(std::string channel);
		std::string ERR_TOOMANYCHANNELS(std::string channel);
		std::string ERR_WASNOSUCHNICK(std::string nickname);
		std::string ERR_NORECIPIENT(std::string command);
		std::string ERR_NOTEXTTOSEND();
		std::string ERR_BADCHANMASK(std::string mask);
		std::string ERR_UNKNOWNCOMMAND(std::string command);
		std::string ERR_NONICKNAMEGIVEN();
		std::string ERR_ERRONEUSNICKNAME(std::string nick);
		std::string ERR_NICKNAMEINUSE(std::string nick);
		std::string ERR_USERNOTINCHANNEL(std::string nick, std::string channel);
		std::string ERR_NOTONCHANNEL(std::string channel);
		std::string ERR_USERONCHANNEL(std::string user, std::string channel);
		std::string ERR_NOLOGIN(std::string user);
		std::string ERR_NOTREGISTERED();
		std::string ERR_NEEDMOREPARAMS(std::string command);
		std::string ERR_ALREADYREGISTERED();
		std::string ERR_PASSWDMISMATCH();
		std::string ERR_KEYSET(std::string channel);
		std::string ERR_CHANNELISFULL(std::string channel);
		std::string ERR_UNKNOWNMODE(std::string c);
		std::string ERR_INVITEONLYCHAN(std::string channel);
		std::string ERR_BANNEDFROMCHAN(std::string channel);
		std::string ERR_BADCHANNELKEY(std::string channel);
		std::string ERR_RESTRICTED();
		std::string ERR_CHANOPRIVSNEEDED(std::string channel);
		std::string ERR_UNIQOPPRIVSNEEDED();
		std::string ERR_NOOPERHOST();
		std::string ERR_UMODEUNKNOWNFLAG();
		std::string ERR_USERSDONTMATCH();
};

#endif
