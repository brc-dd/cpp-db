void AdminChoiceProcessor(bool bipass)
{
    char choice, ch;
    do
    {
        if(not bipass)
        {
            cout<<"\n\nEnter your choice: ";
            cin>>choice;
            cout<<endl;
            switch(choice)
            {
            case '1':
                user_create();
                break;
            case '2':
                user_delete();
                break;
            case '3':
                user_modify();
                break;
            case '4':
                cout<<"\nFeature under development!";
                break;
            case '5':
                return;
                break;
            default:
                cout<<"\nWrong Choice!";
                break;
            }
        }
        else
        {
            cout<<"\n\nContinue? (y/n) ";
            cin.clear();cin.sync();
            cin.get(ch);
            if(ch=='Y' or ch=='y')
                bipass=false;
            else break;
        }
    } while(true);
    if(ch!='Y' or ch!='y')
        exit(0);
}

void AdminMenuLoader(bool bipass)
{
    hidecursor();
    int i=0;
    string str="Welcome to Admin Panel!";
    if(not bipass)
    {
        Load0(str, 0, 1);
        sleep_until(system_clock::now()+seconds(2));
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
                str="1. Add new database user ";
                break;
            case 2:
                str="2. Delete a database user";
                break;
            case 3:
                str="3. Modify user's password";
                break;
            case 4:
                str="4. Change admin email-id ";
                break;
            case 5:
                str="5. Return to main menu   ";
                break;
        }
        cout<<'*';
        Align0(str, (str.length()/2+1)-padding_horizontal, false);
        cout<<setw((console_width-str.length())/2)<<'*'<<endl<<endl;
    }
    for(i=0; i<console_width; i++) cout<<'*';
    showcursor();
    AdminChoiceProcessor(bipass);
}
