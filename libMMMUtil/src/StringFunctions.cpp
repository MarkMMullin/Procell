#include "StringFunctions.h"
#include<vector>
#include <string>
#include <sstream>

std::vector<std::string> splitStr(std::string src,char splitOn)
{
    std::vector<std::string> strings;
    std::istringstream f(src);

    // break down the topic string
    std::string s;
    while (getline(f, s, splitOn)) {
        strings.push_back(s);
    }
    return strings;
}
