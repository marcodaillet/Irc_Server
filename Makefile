NAME = ircserv

SRCS := srcs/main.cpp\
        srcs/server/server.cpp\
        srcs/server/server_utils.cpp\
	srcs/user/user.cpp\
	srcs/channel/channel.cpp\
	srcs/utils/messages.cpp\
	srcs/utils/getMessages.cpp\
	srcs/utils/err.cpp\
	srcs/utils/utils.cpp\
	srcs/commands/away.cpp\
    	srcs/commands/join.cpp\
      	srcs/commands/list.cpp\
      	srcs/commands/names.cpp\
      	srcs/commands/notice.cpp\
      	srcs/commands/pass.cpp\
   	srcs/commands/quit.cpp\
     	srcs/commands/user.cpp\
	srcs/commands/invite.cpp\
      	srcs/commands/kick.cpp\
      	srcs/commands/nick.cpp\
     	srcs/commands/part.cpp\
    	srcs/commands/privmsg.cpp\
      	srcs/commands/topic.cpp\
      	srcs/commands/mode.cpp\
      	srcs/commands/help.cpp\
      	srcs/commands/motd.cpp\
      	srcs/commands/whois.cpp\

COMP = c++ -Wall -Wextra -Werror -std=c++98

.cpp.o:
	$(COMP) -c $< -o $(<:.cpp=.o)

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(COMP) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS) 

fclean: clean
	rm -rf $(NAME)

re: fclean all 

.PHONY: all clean fclean re bonus
