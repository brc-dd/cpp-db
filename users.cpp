void AdminMenuLoader(bool);

void user_create()
{
    credentials new_user=caller1(false);
    string str="Creating";
    Load0(str, 1, 1, false);cout<<'\b';
    for(int i=0; i<4; i++)
    {
        cout<<'.';
        sleep_until(system_clock::now() + seconds(1));
    }
    if(new_user.confirm==new_user.pwd)
    {
        xDefault.construct(new_user.user, new_user.pwd);
        if(xDefault._isUserUnique())
        {
            xDefault._Save();
            str="New user account successfully created!";
            Load0(str, 0, 1);
            _getch();
        }
        else
        {
            str="Error! The user already exists!";
            Load0(str, 0, 1);
            _getch();
        }
    }
    else
    {
        str="Error! The passwords do not match!";
        Load0(str, 0, 1);
        _getch();
    }
    xDefault.userisAdmin=true;
    AdminMenuLoader(true);
}

void user_delete()
{
    string query;
    cout<<"\nEnter the name of the user you want to delete: ";
    cin>>query;
    xDefault.construct(query, string(" "));
    if(xDefault.userisAdmin)
        cout<<"\nSorry admin account cannot be deleted!";
    else if(xDefault._Delete())
        cout<<"\nUser account successfully deleted!";
    else
        cout<<"\nNo such user exists!";
    _getch();
    xDefault.userisAdmin=true;
    AdminMenuLoader(true);
}

void user_modify()
{
    credentials modified_user=caller1(true, true);
    string str="Working on it";
    Load0(str, 1, 1, false);
    for(int i=0; i<4; i++)
    {
        cout<<'.';
        sleep_until(system_clock::now() + seconds(1));
    }
    xDefault.construct(modified_user.user, modified_user.pwd);
    if(xDefault._Check(false))
    {
        if(modified_user.confirm==modified_user.newpwd)
        {
            xDefault._Modify(modified_user.user, modified_user.newpwd);
            str="User's credentials successfully modified!";
            Load0(str, 0, 1);
            _getch();
        }
        else
        {
            str="Error! The passwords do not match!";
            Load0(str, 0, 1);
            _getch();
        }
    }
    else
    {
        str="User's original credentials are not correct!";
        Load0(str, 0, 1);
        _getch();
    }
    xDefault.userisAdmin=true;
    AdminMenuLoader(true);
}
