bool caller3(bool userisAdmin)
{
    char choice, ch;
    bool bipass;
    do
    {
        cout<<"\n\nEnter your choice: ";
        cin>>choice;
        cout<<endl;
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
                bipass=true;
                ch='Y';
                break;
            }
        default:
            cout<<"\nWrong Choice!";
            break;
        }
        if(not bipass)
        {
            cout<<"\n\nContinue? (y/n) ";
            cin.clear();cin.sync();
            cin.get(ch);
        }
        if(ch=='Y' or ch=='y')
            return true;
        else break;
    } while(true);
    return false;
}
