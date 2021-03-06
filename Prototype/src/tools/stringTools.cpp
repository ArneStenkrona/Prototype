#include "stringTools.h"
#include <iostream>

std::vector<std::string> stringSplitter(std::string input, char c)
{
    std::vector<std::string> vec;
    std::string buffer;

    for (unsigned int i = 0; i < input.length(); i++) {
        if (input[i] == c) {
            vec.push_back(buffer);
            buffer = "";
        }
        else {
            buffer += input[i];
        }
    }
    if (buffer.size() > 0) vec.push_back(buffer);

    return vec;
}


