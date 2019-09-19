#pragma once

#include "validators.h"
#include "shade.h"
#include "loaders.h"
#include "rlutil.h"
#include "constants.h"
#include <bits/stdc++.h>
#ifdef _GCC_VERSION_LESS_THAN_8_
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#elif _GCC_VERSION_MORE_THAN_8_
    #include <filesystem>
    namespace fs = std::filesystem;
#endif

class criminal_record
{
private:
    std::string name, father, address, offense, crime_codes, blood, sex;
    date dob;
    unsigned int reward;
    unsigned long int length;
    unsigned long long int uid;
public:
    friend std::ostream& operator<<(std::ostream&, const criminal_record&);
    friend std::istream& operator>>(std::istream&,  criminal_record&);
    void _read();
    void _write();
    void _search();
    void _delete();
    void _modify();
    void _display();
    void _encode();
    void _decode();
    void _generateUID();
};

