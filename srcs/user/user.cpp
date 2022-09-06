#include "user.hpp"

User::User(int socketfd): _socketfd(socketfd), _nick("*"), _awayMsg(""), _userName(""), _realName(""), _host(""), _lastChan("*"),_hasNick(false), _hasPassword(false), _isLoggedIn(false) 
{
	this->_modes['i'] = false;
	this->_modes['a'] = false;
}

User::~User()
{}
//GET
int User::getSocketFd() const { return (this->_socketfd); }
std::string User::getNick() const { return (this->_nick); }
std::string User::getUserName() const { return (this->_userName); }
std::string User::getRealName() const { return (this->_realName); }
std::string User::getHost() const { return (this->_host); }
std::string User::getAwayMsg() const { return (this->_awayMsg); }
std::string User::getDelMessage() const { return (this->_delMsg); }
std::string User::getLastChanName() const { return (this->_lastChan); }
std::string User::getInput() const { return (this->_input); }
bool User::hasNick() const { return (this->_hasNick); }
bool User::hasPassword() const { return (this->_hasPassword); }
bool User::isLoggedIn() const { return (this->_isLoggedIn); }
bool User::getMode(char c)
{
	if (c == 'o')
	{
		std::vector<Channel *> chans = this->getChannels();
		for (size_t i = 0; i < chans.size(); i++)
			if (chans[i]->isOperator(this))
				return (true);
		return (false);
	}
	else if (this->_modes.count(c))
		return (this->_modes[c]);
	else
		return (false);
}
std::string User::getModesStr()
{
	std::string ret = "";
	if (this->_modes.count('a'))
		if (this->getMode('a'))
			ret += "a";
	if (this->_modes.count('i'))
		if (this->getMode('i'))
		ret += "i";
	return (ret);
}
Channel* User::getLastChan(void) const { return (!_channels.empty() ? this->_channels[_channels.size() - 1] : NULL); };
std::vector<Channel *> User::getChannels(void) const { return (this->_channels); }
//SET
void User::setNick(const std::string nick) { this->_nick = nick; }
void User::setUserName(const std::string name) { this->_userName = name; }
void User::setRealName(const std::string name) { this->_realName = name; }
void User::setHost(const std::string host) { this->_host = host; }
void User::setLastChanName(const std::string name) { this->_lastChan = name; }
void User::setAwayMsg(const std::string awayMsg) { this->_awayMsg = awayMsg; }
void User::setHasNick(bool b) { this->_hasNick = b; }
void User::setHasPassword(bool b) { this->_hasPassword = b; }
void User::setIsLoggedIn(bool b) { this->_isLoggedIn = b; }
void User::setMode(char c, bool b) { this->_modes[c] = b; }
void User::setDelMessage(std::string msg) { this->_delMsg = msg; }
void User::setInput(std::string str) { this->_input = str; }
//OTHER
void User::addChannel(Channel *channel)
{
	this->_channels.push_back(channel);
}
void User::leaveChannel(std::string name)
{
	size_t i;
	for (i = 0; i < this->_channels.size(); i++)
	{
		if (name == this->_channels[i]->getName())
		{
			this->_channels.erase(this->_channels.begin() + i);
			break;
		}
	}
}
void User::leaveAllChannels()
{
	for (size_t i = 0; i < this->_channels.size(); i++)
		this->_channels[i]->deleteUser(this);
	this->_channels.clear();
}

void User::sendMessage(std::string msg, User *user)
{
	msg = ":" + user->getPrefix() + " " + msg + "\r\n";
	if (send(this->_socketfd, msg.c_str(), msg.size(), 0) == -1)
		throw std::runtime_error(errnoMgmt("send", itoa(this->_socketfd), errno));
}

void User::sendMessageVanilla(std::string msg)
{
	if (send(this->_socketfd, msg.c_str(), msg.size(), 0) == -1)
		throw std::runtime_error(errnoMgmt("send", itoa(this->_socketfd), errno));
}

std::string User::getPrefix() const
{
	if (this->_hasPassword == false || this->_isLoggedIn == false)
                return std::string("");

        std::string prefix = this->getNick();
        if (getHost().length())
        {
                if (getUserName().length())
                        prefix += "!" + getUserName();
                prefix += "@" + getHost();
        }
        return prefix;
}
