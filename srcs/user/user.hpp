#pragma once

#ifndef USER_HPP
#define USER_HPP

#include "../utils/libs.hpp"
#include "../channel/channel.hpp"

class Channel;

class User
{
	protected:
		int _socketfd;
		std::string _nick;
	private:
		std::string _awayMsg;	
		std::string _userName;
		std::string _realName;
		std::string _host;
		std::string _delMsg;
		std::string _lastChan;

		bool _hasNick;
		bool _hasPassword;
		bool _isLoggedIn;
		std::map<char, bool> _modes;

		std::vector<Channel *> _channels;
		std::string _input;
	public:
		User(int _socketfd);
		~User();
		//Get
		int getSocketFd() const;
		std::string getNick() const;
		std::string getUserName() const;
		std::string getRealName() const;
		std::string getHost() const;
		std::string getAwayMsg() const;
		std::string getLastChanName() const;
		bool hasNick() const;
		bool hasPassword() const;
		bool isLoggedIn() const;
		bool getMode(char c);
		std::string getModesStr();
		Channel* getLastChan() const;
		std::string getPrefix() const;
		std::string getDelMessage() const;
		std::vector<Channel *> getChannels() const;
		std::string getInput() const;
		//Set
		void setNick(const std::string nick);
		void setUserName(const std::string name);
		void setRealName(const std::string name);
		void setHost(const std::string host);
		void setLastChanName(const std::string name);
		void setAwayMsg(const std::string awayMsg);
		void setHasNick(bool b);
		void setHasPassword(bool b);
		void setIsLoggedIn(bool b);
		void setMode(char c, bool b);
		void setDelMessage(std::string msg);
		void setInput(std::string str);
		//Other
		void addChannel(Channel *channel);
		void leaveChannel(std::string name);
		void leaveAllChannels();
		void sendMessage(std::string msg, User *user);
		void sendMessageVanilla(std::string msg);
		void freeAll();
};

#endif
