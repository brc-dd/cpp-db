credentials caller1(bool existing_user=true, bool modify=false)
{
    hidecursor();
    string str1="Enter Credentials : ";
    if(not existing_user)
        str1="Enter Credentials of the New User : ";
    string str2="UserID : ";
    string str3="Password : ";
    int i=0;
    char arr1[11], arr2[11], arr3[11], arr4[11];
    Load0(str1, str2, 0);
    for(i=0; i<10; i++)
    {
        arr1[i]=_getch();
        if(arr1[i]=='\n')
            break;
        str2+=arr1[i];
        Load0(str1, str2, 1);
    }
    Load0(str1, str2, str3, 0);
    for(i=0; i<10; i++)
    {
        arr2[i]=_getch();
        if(arr2[i]=='\n')
            break;
        str3+='*';
        Load0(str1, str2, str3, 1);
    }
    if(modify)
    {
        str3="Enter New Password : ";
        Load0(str1, str2, str3, 0);
        for(int i=0; i<10; i++)
        {
            arr3[i]=_getch();
            if(arr3[i]=='\n')
                break;
            str3+='*';
            Load0(str1, str2, str3, 1);
        }
    }
    if(not existing_user or modify)
    {
        str3="Confirm Password : ";
        Load0(str1, str2, str3, 0);
        for(int i=0; i<10; i++)
        {
            arr4[i]=_getch();
            if(arr4[i]=='\n')
                break;
            str3+='*';
            Load0(str1, str2, str3, 1);
        }
    }
    arr1[10]=arr2[10]=arr3[10]=arr4[10]='\0';
    credentials logon;
    logon.user=arr1;
    logon.pwd=arr2;
    if(modify)
        logon.newpwd=arr3;
    if(not existing_user or modify)
        logon.confirm=arr4;
    return logon;
}

void caller2(bool userisAdmin, bool bipass)
{
    int i=0;
    string str="Welcome!";
    if(not bipass)
    {
        Load0(str, 0, 1);
        sleep_until(system_clock::now()+seconds(1));
        str="Loading";
        Load0(str, 1, 1, false);
        for(i=0; i<4; i++)
        {
            cout<<'.';
            sleep_until(system_clock::now() + seconds(1));
        }
    }
    system("cls");
    str="Central Investigation Department";
    SetWindow(80, 20, true);
    cout<<endl;
    Align0(str, -2);
    cout<<endl;
    for(i=0; i<console_width; i++) cout<<'*';
    cout<<'\n';
    for(i=1; i<=5; i++)
    {
        switch(i)
        {
            case 1:
                str="1. View criminal details   ";
                break;
            case 2:
                str="2. Add new criminal details";
                break;
            case 3:
                str="3. Search a criminal record";
                break;
            case 4:
                str="4. Delete a criminal record";
                break;
            case 5:
                str="5. Modify a criminal record";
                break;
        }
        cout<<'*';
        Align0(str, (str.length()/2)-padding_horizontal, false);
        cout<<setw((console_width-str.length())/2)<<'*'<<endl<<endl;
    }
    if(userisAdmin)
    {
        str="6. Open the CID admin menu ";
        cout<<'*';
        Align0(str, (str.length()/2)-padding_horizontal, false);
        cout<<setw((console_width-str.length())/2)<<'*'<<endl<<endl;
    }
    for(i=0; i<console_width; i++) cout<<'*';
}