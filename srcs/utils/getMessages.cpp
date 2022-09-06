#include "../server/server.hpp"

std::string Server::getCodeMessage(User* user, unsigned short code, std::string argument1, std::string argument2, std::string argument3, std::string argument4, std::string argument5, std::string argument6, std::string argument7)
{
	std::string u = user->getNick();
	u += " ";
	switch (code)
	{
		case 001:
			return (u + RPL_WELCOME(argument1));
		case 221:
			return (u + RPL_UMODEIS(argument1));
		case 301:
			return (u + RPL_AWAY(argument1, argument2));
		case 305:
			return (u + RPL_UNAWAY());
		case 306:
			return (u + RPL_NOWAWAY());
		case 311:
			return (u + RPL_WHOISUSER(argument1, argument2, argument3, argument4));
	        case 312:
	                return (u + RPL_WHOISSERVER(argument1, argument2, argument3));
		case 313:
			return (u + RPL_WHOISOPERATOR(argument1));
	        case 315:
	                return (u + RPL_ENDOFWHO(argument1));
		case 318:
			return (u + RPL_ENDOFWHOIS(argument1));
		case 319:
			return (u + RPL_WHOISCHANNELS(argument1, argument2));
		case 331:
			return (u + RPL_NOTOPIC(argument1));
		case 321:
			return (u + RPL_LISTSTART());
		case 322:
			return (u + RPL_LIST(argument1, argument2, argument3));
		case 323:
			return (u + RPL_LISTEND());
		case 324:
			return (u + RPL_CHANNELMODEIS(argument1, argument2, argument3));
		case 332:
			return (u + RPL_TOPIC(argument1, argument2));
		case 341:
			return (u + RPL_INVITING(argument1, argument2));
		case 352:
			return (u + RPL_WHOREPLY(argument1, argument2, argument3, argument4, argument5, argument6, argument7));
		case 353:
			return (u + RPL_NAMREPLY(argument1, argument2, argument3));
		case 366:
			return (u + RPL_ENDOFNAMES(argument1));
		case 372:
			return (u + RPL_MOTD(argument1));
		case 375:
			return (u + RPL_MOTDSTART(argument1));
		case 376:
			return (u + RPL_ENDOFMOTD());
		case 401:
			return (u + ERR_NOSUCHNICK(argument1));
		case 403:
			return (u + ERR_NOSUCHCHANNEL(argument1));
		case 404:
			return (u + ERR_CANNOTSENDTOCHAN(argument1));
		case 421:
			return (u + ERR_UNKNOWNCOMMAND(argument1));
		case 431:
			return (u + ERR_NONICKNAMEGIVEN());
		case 432:
			return (u + ERR_ERRONEUSNICKNAME(argument1));
		case 433:
			return (u + ERR_NICKNAMEINUSE(argument1));
		case 441:
			return (u + ERR_USERNOTINCHANNEL(argument1, argument2));
		case 442:
			return (u + ERR_NOTONCHANNEL(argument1));
		case 443:
			return (u + ERR_USERONCHANNEL(argument1, argument2));
		case 461:
			return (u + ERR_NEEDMOREPARAMS(argument1));
		case 462:
			return (u + ERR_ALREADYREGISTERED());
		case 471:
			return (u + ERR_CHANNELISFULL(argument1));
		case 472:
			return (u + ERR_UNKNOWNMODE(argument1));
		case 473:
			return (u + ERR_INVITEONLYCHAN(argument1));
		case 475:
			return (u + ERR_BADCHANNELKEY(argument1));
		case 476:
			return (u + ERR_BADCHANMASK(argument1));
		case 482:
			return (u + ERR_CHANOPRIVSNEEDED(argument1));
		case 484:
			return (u + ERR_RESTRICTED());
		case 485:
			return (u + ERR_PASSWDMISMATCH());
		case 501:
       			return (u + ERR_UMODEUNKNOWNFLAG());
		case 502:
			return (u + ERR_USERSDONTMATCH());
		default:
			return (u + argument1);
	}
}
