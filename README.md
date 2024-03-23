# Irc_Server

An IRC (Internet Relay Chat) server crafted in C++. This endeavor explores the realms of efficient server handling, non-blocking I/O operations, and seamless compatibility with the Irssi client.

## Efficient Server Handling:

- Concurrently manages multiple clients without interruptions.
- Implements non-blocking I/O operations for a smooth user experience.
- Allows communication through TCP/IP (v4 or v6) for universal accessibility.

## IRC Commands and Features:

- Facilitates user authentication, nickname and username settings, channel joining, and private message exchanges.
- Enhances user experience with real-time message forwarding across channels.
- Introduces channel operators and regular users for effective channel management.
- Ensures flawless connectivity with the Irssi client, making it the reference for evaluation.

Channel Operator Commands:
Empowers operators with commands like KICK, INVITE, TOPIC, and MODE for dynamic channel control.

## Supported IRC Commands:
```
-> PASS password
-> NICK nickname
-> JOIN channel{,channel} [key]
-> KICK channel user [:message]
-> LIST [channel{,channel}]
-> NOTICE nickname/channel :message
-> PART channel{,channel}
-> PRIVMSG nickname/channel{,nickname/channel} :message
-> QUIT [:message]
-> USER nickname host server name :realname
-> TOPIC channel [topic]
-> MODE channel {[+|-]|s|i|k|o} [] []
-> MODE nickname {[+|-]|i|o}
-> AWAY [:message]
-> INVITE nickname channel
-> NAMES channel {,channel}
```

## Usage:

Compile the IRC server using C++ 98.
Run the server executable with specified port and password parameters.
Connect using the Irssi client to explore and interact with the IRC commands and features.

https://user-images.githubusercontent.com/55747965/147461226-e5ba03a4-5db8-4213-a5b5-47332ca9cf83.mp4
