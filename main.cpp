#include <bits/stdc++.h>

#include "admin.h"
#include "callers.h"
#include "constants.h"
#include "credentials.h"
#include "criminals.h"
#include "loaders.h"
#include "shade.h"
#include "users.h"
#include "validators.h"

int main()
{
    SetWindow(80, 20);
    rlutil::hidecursor();
    bool bypass = false;
    credentials logon = caller1();
    extern xCredentials xDefault;
    xDefault.__init__(encrypt(logon.user), encrypt(logon.pwd));
    if(not xDefault._Check()) return 1;
    std::this_thread::sleep_for(1s);
    lb:
    caller2(xDefault.userisAdmin(), bypass);
    rlutil::showcursor();
    if(caller3(xDefault.userisAdmin()))
    {
        bypass = true;
        goto lb;
    }
    return 0;
}