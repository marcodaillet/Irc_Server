#include "libs.hpp"

std::string itoa(int n)
{
        std::string ret = "";
        if (n == 0)
                return ("0");
        while (n > 0)
        {
                char c = (n % 10) + 48;
                ret = c + ret;
                n /= 10;
        }
        return (ret);
}

int atoi(std::string n)
{
        int ret = 0;
        if (n == "0")
                return (0);
        for (size_t i = 0; i < n.size(); i++)
                ret = (ret * 10) + n[i] - '0';
        return (ret);
}

std::string black(std::string str) {    return (std::string(BLACK) + str + std::string(RESET)); }
std::string red(std::string str) {      return (std::string(RED) + str + std::string(RESET)); }
std::string green(std::string str) {    return (std::string(GREEN) + str + std::string(RESET)); }
std::string yellow(std::string str) {   return (std::string(YELLOW) + str + std::string(RESET)); }
std::string blue(std::string str) {     return (std::string(BLUE) + str + std::string(RESET)); }
std::string magenta(std::string str) {  return (std::string(MAGENTA) + str + std::string(RESET)); }
std::string cyan(std::string str) {     return (std::string(CYAN) + str + std::string(RESET)); }
std::string Bblack(std::string str) {   return (std::string(BOLDBLACK) + str + std::string(RESET)); }
std::string Bred(std::string str) {     return (std::string(BOLDRED) + str + std::string(RESET)); }
std::string Bgreen(std::string str) {   return (std::string(BOLDGREEN) + str + std::string(RESET)); }
std::string Byellow(std::string str) {  return (std::string(BOLDYELLOW) + str + std::string(RESET)); }
std::string Bblue(std::string str) {    return (std::string(BOLDBLUE) + str + std::string(RESET)); }
std::string Bmagenta(std::string str) { return (std::string(BOLDMAGENTA) + str + std::string(RESET)); }
std::string Bcyan(std::string str) {    return (std::string(BOLDCYAN) + str + std::string(RESET)); }
std::string Bwhite(std::string str) {   return (std::string(BOLDWHITE) + str + std::string(RESET));}

