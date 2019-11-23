#include "callers.h"

extern criminal_record criminal;

credentials caller1(bool existing_user, bool modify)
{
    rlutil::hidecursor();
    std::string str1="Enter Credentials : ";
    if(not existing_user)
        str1="Enter Credentials of the New User :";
    std::string str2="UserID : ";
    std::string str3="Password : ";
    credentials logon;
    Load0(str1, str2, 0);
    for(int i=0; i<32; i++)
    {
        
        logon.user += getch();
        if(logon.user[i]=='\r')
            break;
        str2 += logon.user[i];
        Load0(str1, str2, 1);
    }
    Load0(str1, str2, str3, 0);
    for(int i=0; i<32; i++)
    {
        logon.pwd += getch();
        if(logon.pwd[i]=='\r')
            break;
        str3 += '*';
        Load0(str1, str2, str3, 1);
    }
    if(modify)
    {
        str3="Enter New Password : ";
        Load0(str1, str2, str3, 0);
        for(int i=0; i<32; i++)
        {
            logon.newpwd += getch();
            if(logon.newpwd[i]=='\r')
                break;
            str3 += '*';
            Load0(str1, str2, str3, 1);
        }
    }
    if(not existing_user or modify)
    {
        str3="Confirm Password : ";
        Load0(str1, str2, str3, 0);
        for(int i=0; i<10; i++)
        {
            logon.confirm += getch();
            if(logon.confirm[i]=='\r')
                break;
            str3 += '*';
            Load0(str1, str2, str3, 1);
        }
    }
    return logon;
}

void caller2(bool userisAdmin, bool bypass)
{
    int i=0;
    std::string str="Welcome!";
    if(not bypass)
    {
        Load0(str, 0, 1);
        std::this_thread::sleep_for(1s);
        str="Loading";
        Load0(str, 1, 1, false);
        for(i=0; i<4; i++)
        {
            std::cout<<'.';
            std::this_thread::sleep_for(1s);
        }
    }
    rlutil::cls();
    str="Central Investigation Department";
    SetWindow(80, 20, true);
    std::cout<<'\n';
    Align0(str, -2);
    std::cout<<'\n';
    for(i=0; i<console_width; i++) 
        std::cout<<'*';
    std::cout<<'\n';
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
        std::cout<<'*';
        Align0(str, (str.length()/2)-padding_horizontal, false);
        std::cout<<std::setw((console_width-str.length())/2)<<"*\n\n";
    }
    if(userisAdmin)
    {
        str="6. Open the CID admin menu ";
        std::cout<<'*';
        Align0(str, (str.length()/2)-padding_horizontal, false);
        std::cout<<std::setw((console_width-str.length())/2)<<"*\n\n";
    }
    for(i=0; i<console_width; i++) 
        std::cout<<'*';
}

bool caller3(bool userisAdmin)
{
    char choice, ch;
    bool bypass;
    do
    {
        std::cout<<"\n\nEnter your choice: ";
        std::cin>>choice;
        std::cout<<'\n';
        switch(choice)
        {
        case '1':
            criminal._read();
            break;
        case '2':
            criminal._write();
            break;
        case '3':
            criminal._search();
            break;
        case '4':
            criminal._delete();
            break;
        case '5':
            criminal._modify();
            break;
        case '6':
            if(userisAdmin)
            {
                AdminMenuLoader(false);
                bypass=true;
                ch='Y';
                break;
            }
        default:
            std::cout<<"\nWrong Choice!";
            break;
        }
        if(not bypass)
        {
            std::cout<<"\n\nContinue? (y/n) ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get(ch);
        }
        if(ch=='Y' or ch=='y')
            return true;
        else break;
    } while(true);
    return false;
}
