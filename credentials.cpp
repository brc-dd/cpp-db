#include "credentials.h"

xCredentials xDefault;

//fs::path cp=fs::current_path();

extern fs::path cp;

bool xCredentials::userisAdmin()
{
    return (user==encrypt("0xAdminCID"));
}

void xCredentials::__init__(std::string u, std::string p)
{
    user=u;
    pwd=p;
}

std::ostream& operator<<(std::ostream& out, const xCredentials& x)
{
    out<<x.user<<someRANDOMnonHexChar()<<x.pwd<<someRANDOMnonHexChar();
    return out;
}

std::istream& operator>>(std::istream& in,  xCredentials& x)
{
    extern std::string delim;
    getline(in, x.user, delim);
    getline(in, x.pwd, delim);
	return in;
}

bool xCredentials::_Check(bool doLog)
{
    std::string u=user, p=pwd;
    bool xSet=false;
    #ifdef _GCC_VERSION_LESS_THAN_8_
        std::ifstream ifile((cp/"data.dat").string());
    #elif _GCC_VERSION_MORE_THAN_8_
        std::ifstream ifile(cp/"data.dat");
    #endif
    ifile.seekg(0, std::ios::beg);
    while(ifile and not xSet)
    {
        ifile>>xDefault;
        if(u==user and p==pwd)
            xSet=true;
    }
    ifile.close();
    if(doLog)
    {
        std::string str_grant="Access Granted!", str_deny="Access Denied!";
        if(xSet)
        {
            Load0(str_grant, 0, 1);
            #ifdef _GCC_VERSION_LESS_THAN_8_
                std::ofstream ofile((cp/"logs.dat").string(), std::ios::app);
            #elif _GCC_VERSION_MORE_THAN_8_
                std::ofstream ofile(cp/"logs.dat", std::ios::app);
            #endif
            ofile<<ctime(new time_t(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())))<<'\n'<<"UserId : "<<decrypt(u)<<'\n';
            ofile.close();
            return true;
        }
        Load0(str_deny, 0, 1);
    }
    return xSet;
}

void xCredentials::_Save()
{
    #ifdef _GCC_VERSION_LESS_THAN_8_
        std::ofstream ofile((cp/"data.dat").string(), std::ios::app);
    #elif _GCC_VERSION_MORE_THAN_8_
        std::ofstream ofile(cp/"data.dat", std::ios::app);
    #endif
    ofile<<xDefault;
    ofile.close();
}

bool xCredentials::_isUserUnique()
{
    std::string u=user, p=pwd;
    #ifdef _GCC_VERSION_LESS_THAN_8_
        std::ifstream ifile((cp/"data.dat").string());
    #elif _GCC_VERSION_MORE_THAN_8_
        std::ifstream ifile(cp/"data.dat");
    #endif
    ifile.seekg(0, std::ios::beg);
    while(ifile)
    {
        ifile>>xDefault;
        if(u==user)
            return false;
    }
    ifile.close();
    __init__(u, p);
    return true;
}

bool xCredentials::_Delete()
{
    std::string u=user;
    bool isAnyChangeMade=false;
    #ifdef _GCC_VERSION_LESS_THAN_8_
        std::ifstream ifile((cp/"data.dat").string());
        std::ofstream ofile((cp/"new").string(), std::ios::out);
    #elif _GCC_VERSION_MORE_THAN_8_
        std::ifstream ifile(cp/"data.dat");
        std::ofstream ofile(cp/"new", std::ios::out);
    #endif
    ifile.seekg(0, std::ios::beg);
    while(ifile)
    {
        ifile>>xDefault;
        if(u!=user)
            ofile<<xDefault;
        else
            isAnyChangeMade=true;
    }
    ifile.close();
    ofile.close();
    fs::remove(cp/"data.dat");
    fs::rename(cp/"new", cp/"data.dat");
    return isAnyChangeMade;
}

void xCredentials::_Modify(std::string u, std::string p)
{
    #ifdef _GCC_VERSION_LESS_THAN_8_
        std::fstream f((cp/"data.dat").string(), std::ios::in|std::ios::out);
    #elif _GCC_VERSION_MORE_THAN_8_
        std::fstream f(cp/"data.dat", std::ios::in|std::ios::out);
    #endif
    f.seekg(0, std::ios::beg);
    while(f)
    {
        f>>xDefault;
        if(u==user)
        {
            f.seekg(-(xDefault.user.length()+xDefault.pwd.length()+2), std::ios::cur);
            xDefault.__init__(u, p);
            f<<xDefault;
            break;
        }
    }
    f.close();
}
