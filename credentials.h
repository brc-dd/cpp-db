#pragma once

#include <bits/stdc++.h>

#include "constants.h"
#include "loaders.h"
#include "shade.h"
#include "validators.h"

#ifdef _GCC_VERSION_LESS_THAN_8_
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#elif _GCC_VERSION_MORE_THAN_8_
    #include <filesystem>
    namespace fs = std::filesystem;
#endif

struct credentials
{
    std::string user, pwd, newpwd, confirm;
};

class xCredentials
{
    std::string user, pwd;
public:
    bool userisAdmin();
    void __init__(std::string, std::string);
    friend std::ostream& operator<<(std::ostream&, const xCredentials&);
    friend std::istream& operator>>(std::istream&,  xCredentials&);
    bool _Check(bool doLog=true);
    void _Save();
    bool _isUserUnique();
    bool _Delete();
    void _Modify(std::string, std::string);
};
