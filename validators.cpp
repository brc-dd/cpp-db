bool isValidName(string name)
{
    for(char &a: name)
        if(!(isalpha(a) or isspace(a)))
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

bool isValidBlood(string blood)
{
    if(iequals(blood, string("ABP")) or iequals(blood, string("ABN")) or iequals(blood, string("AP"))
    or iequals(blood, string("AN")) or iequals(blood, string("BP")) or iequals(blood, string("BN"))
    or iequals(blood, string("OP")) or iequals(blood, string("ON")))
        return true;
    return false;
}

bool isValidAddress(string address)
{
    for(char &a: address)
        if(!(isalnum(a) or isspace(a)))
            return false;
    return true;
}
