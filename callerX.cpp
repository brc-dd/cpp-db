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
            std::std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get(ch);
        }
        if(ch=='Y' or ch=='y')
            return true;
        else break;
    } while(true);
    return false;
}
