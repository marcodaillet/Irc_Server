#include "channel.hpp"
//
Channel::Channel(const std::string name): _name(name), _topic(""), _password(""), _limit(2147483647)
{
	_modes['s'] = false;
	_modes['i'] = false;
	_modes['t'] = false;
	_modes['k'] = false;
	_modes['l'] = false;
	_modes['n'] = false;
}
Channel::~Channel() {}
//
std::string Channel::getName() const {
	return (this->_name);
}
//
void Channel::addUser(User *user) {
	this->_users.push_back(user);
}
std::vector<User *> &Channel::getUsers(){
        return (this->_users);
}   
//
bool Channel::isOperator(User *user) {
        for (size_t i = 0; i < this->_operators.size(); i++)
                if (user == this->_operators[i])
                        return (true);
        return (false);
}
void Channel::addOperator(User *user) {
	if (this->userExist(user->getNick()))
		this->_operators.push_back(user);
}
void Channel::deleteOperator(User *user) {
	if (!this->userExist(user->getNick()))
		return ;
	for (size_t i = 0; i < this->_operators.size(); i++)
	{
		if (user == this->_operators[i])
		{
			this->_operators.erase(this->_operators.begin() + i);
			break ;
		}
	}
}
//
void Channel::setMode(char c, bool b)
{
	if (c == 'i' && b == false)
		this->_invited.clear();
        this->_modes[c] = b;
}
bool Channel::getMode(char c)
{
	if (this->_modes.count(c))
        	return (this->_modes[c]);
	return (false);
}
std::string Channel::getModesStr()
{
    std::string tmp = "sitkln";
	std::string ret = "";
	for (size_t i = 0; i < tmp.size(); i++){
		if (this->_modes.count(tmp[i])) {
			if (this->getMode(tmp[i]) == true)
				ret += tmp[i];
		}
	}
        return (ret);
}
//
int Channel::getNumberUser()
{
        return (this->_users.size());
}
int Channel::getNumberUserList()
{
	int ret = 0;
	for (size_t i = 0; i < this->_users.size(); i++)
			if (!this->_users[i]->getMode('i'))
				ret++;
	return (ret);
}
void Channel::deleteUser(User *user)
{
	size_t idx;
        for (idx = 0; idx != this->_users.size(); idx++) 
                if (this->_users[idx]->getNick() == user->getNick())
                        break;
	if (idx == this->_users.size())
		return ;
	this->deleteOperator(user);
        this->_users.erase(_users.begin() + idx);
}
void Channel::deleteAllUsers()
{
        for (size_t i = 0; i < this->_users.size(); i++)
		this->_users[i]->leaveChannel(this->getName());	
	this->_users.clear();
}
bool Channel::userExist(std::string name)
{
	for (size_t i = 0; i < this->_users.size(); i++)
		if (this->_users[i]->getNick() == name)
			return (true);
	return (false);
}
bool Channel::empty()
{
	return (this->_users.empty());
}
//
void Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}
std::string &Channel::getTopic()
{
	return (this->_topic);
}
std::string &Channel::setGetTopic(std::string newTopic)
{
	this->setTopic(newTopic);
	return (this->_topic);
}
//
void Channel::messageChannel(std::string message, User *sender)
{
	message = ":" + sender->getPrefix() + " " + message + "\r\n";
	for (size_t i = 0; i < this->_users.size(); i++)
		if (this->_users[i] != sender)
			this->_users[i]->sendMessageVanilla(message);
}
void Channel::messageChannel2(std::string message, User *sender)
{
	message = ":" + sender->getPrefix() + " " + message + "\r\n";
	for (size_t i = 0; i < this->_users.size(); i++)
		this->_users[i]->sendMessageVanilla(message);
}
//
void Channel::addInv(User *user)
{
	this->_invited.push_back(user);
}
void Channel::deleteInv(User *user)
{
	for (size_t i = 0; i < this->_invited.size(); i++)
	{
		if (this->_invited[i] == user)
		{
			this->_invited.erase(this->_invited.begin() + i);
			break;
		}
	}
}
bool Channel::isInv(User *user)
{
	for (size_t i = 0; i < this->_invited.size(); i++)
                if (this->_invited[i] == user)
			return (true);
	return (false);
}
//
void Channel::setPassword(const std::string &pwd)
{
	this->_password = pwd;
}
std::string &Channel::getPassword()
{
	return (this->_password);
}
void Channel::setLimit(int limit)
{
	this->_limit = limit;
}
int Channel::getLimit()
{
	return (this->_limit);
}
void Channel::freeAll()
{
	this->_users.clear();
	this->_operators.clear();
	this->_invited.clear();
	this->_modes.clear();
}
