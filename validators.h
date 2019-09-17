#pragma once

#include <algorithm>
#include <cctype>
#include <string>

struct date
{
    unsigned short dd, mm, yyyy;
};

bool iequals(const std::string&, const std::string&);
std::string to_upper(std::string);
std::istream& getline(std::istream&, std::string&, std::string);

bool isValidName(std::string);
bool isValidSex(char);
bool isValidDate(date);
bool isValidBlood(std::string);
bool isValidAddress(std::string);
