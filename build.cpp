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

int main(int argc, char **argv)
{
    extern xCredentials xDefault;
    xDefault.__init__(encrypt("0xAdminCID"), encrypt(argv[1]));
    xDefault._Save();
    return 0;
}
