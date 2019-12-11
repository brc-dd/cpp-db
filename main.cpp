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
    if (not xDefault._Check())
        return 1;
    std::this_thread::sleep_for(1s);
    bool userisAdmin = xDefault.userisAdmin();
lb:
    caller2(userisAdmin, bypass);
    rlutil::showcursor();
    if (caller3(userisAdmin))
    {
        bypass = true;
        goto lb;
    }
    return 0;
}