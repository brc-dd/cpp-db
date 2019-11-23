#pragma once
#pragma GCC diagnostic ignored "-Wnarrowing"

#include <bits/stdc++.h>

struct date
{
    unsigned short dd, mm, yyyy;
};

std::string dateToString(date);
date stringToDate(std::string);
bool iequals(const std::string&, const std::string&);
std::string to_upper(std::string);
std::istream& getline(std::istream&, std::string&, std::string);

bool isValidName(std::string);
bool isValidSex(char);
bool isValidDate(date);
bool isValidBlood(std::string);
bool isValidAddress(std::string);
