#include <algorithm>
#include <cctype>
#include <chrono>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <dos.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ratio>
#include <sstream>
#include <thread>
#include <windef.h>
#include <windows.h>
#include "rlutil.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
using namespace rlutil;

struct date
{
    unsigned short dd, mm, yyyy;
};

bool iequals(const string& a, const string& b)
{
    return equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}

string to_upper(string str)
{
    transform(str.begin(), str.end(),str.begin(), ::toupper);
    return str;
}

#include "base64.cpp"
#include "constants.cpp"
#include "shade.cpp"
#include "loaders.cpp"
#include "validators.cpp"
#include "credentials.cpp"
#include "criminals.cpp"
#include "callers.cpp"
#include "users.cpp"
#include "admin.cpp"
#include "callerX.cpp"

