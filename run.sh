#!/bin/sh

echo "Compiling..."
make -s re
echo "Compilation done !"

echo "Hi and welcome to our IRC server, please follow instructions to get started"
sleep 1
echo -n "Enter the port where the server will be listening: "
read port
echo -n "Enter the password you want to use: "
read password

echo "Starting server..."
sleep 1

valgrind --track-fds=yes ./ircserv $port $password
