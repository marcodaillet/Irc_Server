#include "../server/server.hpp"

void Server::commandmotd(User *user, std::vector<std::string> &args)
{
	(void)args;
	message(user, 375, "Tkomaris&Mdaillet's IRC");
	message(user, 372, "");
	message(user, 372, Bwhite(" ____  _  _  _____  __  __    __    ____  ____  ___"));
	message(user, 372, Bwhite("(_  _)( )/ )(  _  )(  \\/  )  /__\\  (  _ \\(_  _)/ __)"));
	message(user, 372, Bwhite("  )(   )  (  )(_)(  )    (  /(__)\\  )   / _)(_ \\__ \\"));
	message(user, 372, Bwhite(" (__) (_)\\_)(_____)(_/\\/\\_)(__)(__)(_)\\_)(____)(___/"));
	message(user, 372, Bwhite(" __  __  ____    __    ____  __    __    ____  ____ "));
	message(user, 372, Bwhite("(  \\/  )(  _ \\  /__\\  (_  _)(  )  (  )  ( ___)(_  _)"));
	message(user, 372, Bwhite(" )    (  )(_) )/(__)\\  _)(_  )(__  )(__  )__)   )(  "));
	message(user, 372, Bwhite("(_/\\/\\_)(____/(__)(__)(____)(____)(____)(____) (__) "));	
	message(user, 372, Bwhite(" __  __  ____  _____  _  _  _  _  ____  ____"));
	message(user, 372, Bwhite("(  \\/  )(  _ \\(  _  )( \\( )( \\( )( ___)(_  _)"));
	message(user, 372, Bwhite(" )    (  ) _ < )(_)(  )  (  )  (  )__)   )(  "));
	message(user, 372, Bwhite("(_/\\/\\_)(____/(_____)(_)\\_)(_)\\_)(____) (__) "));	
	message(user, 372, "");
	message(user, 372, Bwhite("Welcome to our Internet Relay Chat !"));
	message(user, 372, "Current number of users -> " + Bwhite(itoa(this->_users.size())));
	message(user, 372, "Current number of channels -> " + Bwhite(itoa(this->_channels.size()))); 
	message(user, 376);
}
