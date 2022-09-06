#include "../server/server.hpp"

void Server::commandinvite(User *user, std::vector<std::string> &args)
{
        if (!user->isLoggedIn()) // need to be logged in
                return (this->message(user, 484));
        if (args.size() < 2) // Only need the name of the channel(s)
                return (this->message(user, 461, "INVITE"));
        if (args[1][0] != '#')
                return (message(user, 476, args[1]));
        Channel *tmp = this->findChannel(args[1]);
        if (tmp == NULL)
                return (this->message(user, 403, args[1]));
        else if (!tmp->userExist(user->getNick()))
                return (this->message(user, 442, args[1]));
        else if (!tmp->isOperator(user))
                return (this->message(user, 482, args[1]));
        User *tmp2 = this->findUserByName(args[0]);
        if (tmp2 == NULL)
                return (this->message(user, 401, args[0]));
        else if (tmp->userExist(tmp2->getNick()))
                return (this->message(user, 443, args[0], args[1]));
        else
        {
                tmp->addInv(tmp2);
                tmp2->sendMessage("INVITE " + args[0] + " " + args[1], user);
                this->message(user, 341, args[0], args[1]);
                if (tmp2->getMode('a'))
                        this->message(user, 301, args[0], tmp2->getAwayMsg());
        }
}
