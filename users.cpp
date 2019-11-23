#include "users.h"

extern xCredentials xDefault;

void user_create()
{
    credentials new_user=caller1(false);
    std::string str="Creating";
    Load0(str, 1, 1, false);
    std::cout<<'\b';
    for(int i=0; i<4; i++)
    {
        std::cout<<'.';
        std::this_thread::sleep_for(1s);
    }
    if(new_user.confirm==new_user.pwd)
    {
        xDefault.__init__(new_user.user, new_user.pwd);
        if(xDefault._isUserUnique())
        {
            xDefault._Save();
            str="New user account successfully created!";
            Load0(str, 0, 1);
            getch();
        }
        else
        {
            str="Error! The user already exists!";
            Load0(str, 0, 1);
            getch();
        }
    }
    else
    {
        str="Error! The passwords do not match!";
        Load0(str, 0, 1);
        getch();
    }
    AdminMenuLoader(true);
}

void user_delete()
{
    std::string query;
    std::cout<<"\nEnter the name of the user you want to delete: ";
    std::cin>>query;
    xDefault.__init__(query, std::string(" "));
    if(xDefault.userisAdmin())
        std::cout<<"\nSorry admin account cannot be deleted!";
    else if(xDefault._Delete())
        std::cout<<"\nUser account successfully deleted!";
    else
        std::cout<<"\nNo such user exists!";
    getch();
    AdminMenuLoader(true);
}

void user_modify()
{
    credentials modified_user=caller1(true, true);
    std::string str="Working on it";
    Load0(str, 1, 1, false);
    for(int i=0; i<4; i++)
    {
        std::cout<<'.';
        std::this_thread::sleep_for(1s);
    }
    xDefault.__init__(modified_user.user, modified_user.pwd);
    if(xDefault._Check(false))
    {
        if(modified_user.confirm==modified_user.newpwd)
        {
            xDefault._Modify(modified_user.user, modified_user.newpwd);
            str="User's credentials successfully modified!";
            Load0(str, 0, 1);
            getch();
        }
        else
        {
            str="Error! The passwords do not match!";
            Load0(str, 0, 1);
            getch();
        }
    }
    else
    {
        str="User's original credentials are not correct!";
        Load0(str, 0, 1);
        getch();
    }
    AdminMenuLoader(true);
}
