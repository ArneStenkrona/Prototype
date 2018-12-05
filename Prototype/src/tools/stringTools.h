#pragma once
#include <string>
#include <vector>
#include <algorithm> 
#include <cctype>
#include <locale>

//tools used for manipulating strings

//splits string by char c (c will not be included in the splitted strings)
std::vector<std::string> stringSplitter(std::string input, char c);

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}
