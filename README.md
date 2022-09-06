# Irc_Server

Implementation of a C++ Internet Relay Chat server handling multiples connections at the same time.  
This project has been done using the Irssi IRC client, but all events are managed through a thorough parsing process.  
The user can create and join chats to share informations with other users connected to the server by using different commands (Listed below).  
 
This project got me acquainted with socket communication, which is very useful the rest of my learning.

Here is a list of commands you can use: 
  -> PASS <password> - Enter the server's password  
  -> NICK <nickname> - Set or change your current nickname  
  -> JOIN <channel>{,<channel>} [<key>] - Create or join a channel optionnally with a key  
  -> KICK <channel> <user> [:<message>] - Kick an user from a channel with an optionnal message  
  -> LIST [<channel>{,<channel>}] - Shows a list of all the visible channels on the server and their topic  
  -> NOTICE <nickname/channel> :<message> - Sends a message to an user or a channel  
  -> PART <channel>{,<channel>} - Leave a channel  
  -> PRIVMSG <nickname/channel>{,<nickname/channel>} :<message> - Sends a message to a user or a channel  
  -> QUIT [:<message>] - Quits the server and optionnaly leaves a message  
  -> USER <nickname> <host> <server name> :<realname> - Register a user in the server  
  -> TOPIC <channel> [<topic>] - Get or set the topic of a channel  
  -> MODE <channel> {[+|-]|s|i|k|o} [<nickname>] [<key>]- Allow channel operator to change the channel's modes  
  -> MODE <nickname> {[+|-]|i|o} - Allow a user to change his own modes  
  -> AWAY [:<message>] - Define or remove the away from keyboard message  
  -> INVITE <nickname> <channel> - Invite a user on a channel if the channels mode is invite  
  -> NAMES <channel> {,<channel>} - Get a list of all non-invisible users on a channel  
    
How to use : ./run.sh  

