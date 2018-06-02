#pragma once
#include <string>
#include <vector>

//tools used for manipulating strings

//splits string by char c (c will be removed from the string)
//This broken version of the function is buggy but because of
//bad software design I'm still dependent on this in room.cpp
std::vector<std::string> brokenStringSplitter(std::string input, char c);

//splits string by char c (c will be removed from the string)
std::vector<std::string> stringSplitter(std::string input, char c);