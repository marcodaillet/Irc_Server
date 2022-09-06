#pragma once

#ifndef LIBS_HPP
#define LIBS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <netdb.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <map>
#include <set>
#include <arpa/inet.h>
#include <poll.h>
#include <netdb.h>
#include <iostream>
#include <errno.h>
#include <algorithm>
//#include "nullptr.hpp"

#define RESET   	"\033[0m"
#define BLACK   	"\033[30m"      /* Black */
#define RED     	"\033[31m"      /* Red */
#define GREEN   	"\033[32m"      /* Green */
#define YELLOW  	"\033[33m"      /* Yellow */
#define BLUE    	"\033[34m"      /* Blue */
#define MAGENTA 	"\033[35m"      /* Magenta */
#define CYAN    	"\033[36m"      /* Cyan */
#define WHITE   	"\033[37m"      /* White */
#define BOLDBLACK   	"\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     	"\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   	"\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  	"\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    	"\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA 	"\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    	"\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   	"\033[1m\033[37m"      /* Bold White */

std::string getErr(const std::string &function, std::string socketFd, const std::string &msg);
std::string errnoMgmt(const std::string &function, std::string socketFd, int err);
std::string itoa(int i);
int atoi(std::string s);

std::string black(std::string str);
std::string red(std::string str);
std::string green(std::string str);
std::string yellow(std::string str);
std::string blue(std::string str);
std::string magenta(std::string str);
std::string cyan(std::string str);
std::string Bblack(std::string str);
std::string Bred(std::string str);
std::string Bgreen(std::string str);
std::string Byellow(std::string str);
std::string Bblue(std::string str);
std::string Bmagenta(std::string str);
std::string Bcyan(std::string str);
std::string Bwhite(std::string str);

#endif
