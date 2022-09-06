#include "server/server.hpp"

int stop_signal = 0;
void handler(int sig)
{
	(void)sig;
	stop_signal = 1;
}

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "How to use: ./ircserv <port> <password>\n";
		return (0);
	}
	if (strlen(av[2]) > 500)
	{
		std::cout << "Error, password is too long\n";
		return (0);
	}
	signal(SIGINT, handler);
	try
	{
		Server server(av[1], av[2]);
		server.init();
		server.displayState();
		while (!stop_signal)
			server.exec();
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << "\n";
	}
	return (0);
}
