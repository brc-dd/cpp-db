#include "credentials.h"
#include "shade.h"
int main(int argc, char **argv)
{
    extern xCredentials xDefault;
    xDefault.__init__(encrypt("0xAdminCID"), encrypt(argv[1]));
    xDefault._Save();
    return 0;
}
