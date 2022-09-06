#pragma once

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../utils/libs.hpp"
#include "../user/user.hpp"

class User;

class Channel
{
	private:
		std::string	_name;
		std::string	_topic;
		std::string	_password;
		int		_limit;

		std::vector<User *> _users;
		std::vector<User *> _operators;
		std::vector<User *> _invited;
		
		std::map<char, bool> _modes;
	public:
		Channel(const std::string name);
		~Channel();
		void freeAll();

		std::string getName() const;
		
		void	addUser(User *user);
		std::vector<User *> &getUsers();
		
		bool	isOperator(User *user);
		void	addOperator(User *user);
		void	deleteOperator(User *user);
		
		void	setMode(char c, bool b);
		bool	getMode(char c);
		std::string	getModesStr();

		int	getNumberUser();
		int	getNumberUserList();
                void	deleteUser(User *user);
   		void	deleteAllUsers();
		bool	userExist(std::string name);
		bool	empty();
		
		void	setTopic(std::string topic);
		std::string &getTopic();
		std::string &setGetTopic(std::string topic);
		
		void	messageChannel(std::string message, User *user);
		void	messageChannel2(std::string message, User *user);
		
		void	addInv(User *user);
		void	deleteInv(User *user);
		bool	isInv(User *user);
		
		int	getLimit();
		void	setLimit(int n);

		void setPassword(const std::string &pwd);
		std::string &getPassword();
};

#endif
