#include "admin.h"

bool AdminChoiceProcessor()
{
    char ch;
    bool x = true;
choice:
    std::cout << "\n\nEnter your choice: ";
    std::cin >> ch;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << '\n';
    switch (ch)
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
        std::cout << "\n\n";
        if (system("type logs.dat"))
            system("cat logs.cat");
        break;
    case '5':
        return false;
        break;
    default:
        std::cout << "\nWrong Choice!";
        goto choice;
        break;
    }
    std::cout << "\n\nContinue? (y/n) ";
    std::cin >> ch;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (ch == 'Y' or ch == 'y')
        return true;
    else
        std::exit(0);
}

void AdminMenuLoader()
{
    rlutil::hidecursor();
    int i = 0;
    std::string str = "Welcome to Admin Panel!";
    Load0(str, 0, 1);
    std::this_thread::sleep_for(1s);
    str = "Loading";
    Load0(str, 1, 1, false);
    for (i = 0; i < 4; i++)
    {
        std::cout << '.';
        std::this_thread::sleep_for(1s);
    }
    do
    {
        rlutil::cls();
        str = "Central Investigation Department";
        std::cout << '\n';
        Align0(str, -2);
        std::cout << '\n';
        for (i = 0; i < console_width; i++)
            std::cout << '*';
        std::cout << '\n';
        for (i = 1; i <= 5; i++)
        {
            switch (i)
            {
            case 1:
                str = "1. Add new database user ";
                break;
            case 2:
                str = "2. Delete a database user";
                break;
            case 3:
                str = "3. Modify user's password";
                break;
            case 4:
                str = "4. Print access logs     ";
                break;
            case 5:
                str = "5. Return to main menu   ";
                break;
            }
            std::cout << '*';
            Align0(str, (str.length() / 2 + 1) - padding_horizontal, false);
            std::cout << std::setw((console_width - str.length()) / 2) << '*' << "\n\n";
        }
        for (i = 0; i < console_width; i++)
            std::cout << '*';
        rlutil::showcursor();
    } while (AdminChoiceProcessor());
}
