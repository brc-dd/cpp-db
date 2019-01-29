#include "initialise.cpp"

int main()
{
    SetWindow(80, 20);
    hidecursor();
    bool bipass=false;
    credentials logon=caller1();
    xDefault.construct(logon.user, logon.pwd);
    if(not xDefault._Check()) return 1;
    sleep_until(system_clock::now()+seconds(1));
    lb:
    caller2(xDefault.userisAdmin, bipass);
    showcursor();
    if(caller3(xDefault.userisAdmin))
    {
        bipass=true;
        goto lb;
    }
    return 0;
}