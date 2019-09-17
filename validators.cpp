#include "validators.h"

bool iequals(const std::string& a, const std::string& b)
{
    return std::equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b) {
                          return std::tolower(a) == std::tolower(b);
                      });
}

std::string to_upper(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

std::istream& getline(std::istream& input, std::string& str, std::string delim)
{
    str.erase();
    char ch;
    while(input and str.length()<str.max_size())
    {
        input.get(ch);
        for(int i=0; i<delim.length(); i++)
        {
            if(ch==delim.at(i))
                return input;
        }
        str.append(1, ch);
    }
    input.setstate(std::ios::failbit);
    return input;
}

bool isValidName(std::string name)
{
    for(char &a: name)
        if(!(std::isalpha(a) or std::isspace(a)))
            return false;
    return true;
}

bool isValidSex(char sex)
{
    if(sex=='m' or sex=='M' or sex=='f' or sex=='F')
        return true;
    return false;
}

bool isValidDate(date dob)
{
    if(!(1582<=dob.yyyy))
        return false;
    if(!(1<=dob.mm and dob.mm<=12))
        return false;
    if(!(1<=dob.dd and dob.dd<=31))
        return false;
    if(dob.dd==31 and (dob.mm==2 or dob.mm==4 or dob.mm==6 or dob.mm==9 or dob.mm==11))
        return false;
    if(dob.dd==30 and dob.mm==2)
        return false;
    if(dob.mm==2 and dob.dd==29 and dob.yyyy%4!=0)
        return false;
    if(dob.mm==2 and dob.dd==29 and dob.yyyy%400==0)
        return true;
    if(dob.mm==2 and dob.dd==29 and dob.yyyy%100==0)
        return false;
    if(dob.mm==2 and dob.dd==29 and dob.yyyy%4==0)
        return true;
    return true;
}

bool isValidBlood(std::string blood)
{
    return iequals(blood, std::string("ABP")) or iequals(blood, std::string("ABN"))
        or iequals(blood, std::string("AP")) or iequals(blood, std::string("AN"))
        or iequals(blood, std::string("BP")) or iequals(blood, std::string("BN"))
        or iequals(blood, std::string("OP")) or iequals(blood, std::string("ON"));
}

bool isValidAddress(std::string address)
{
    for(char &a: address)
        if(!(std::isalnum(a) or std::isspace(a)))
            return false;
    return true;
}
