#include "criminals.h"

namespace ch = std::chrono;

//fs::path cp=fs::current_path();

extern fs::path cp;

criminal_record criminal;

std::ostream &operator<<(std::ostream &out, const criminal_record &x)
{
    out << x.name << someRANDOMnonHexChar()
        << x.father << someRANDOMnonHexChar()
        << x.address << someRANDOMnonHexChar()
        << x.offense << someRANDOMnonHexChar()
        << x.crime_codes << someRANDOMnonHexChar()
        << x.blood << someRANDOMnonHexChar()
        << x.sex << someRANDOMnonHexChar()
        << encrypt(dateToString(x.dob)) << someRANDOMnonHexChar()
        << encrypt(std::to_string(x.reward)) << someRANDOMnonHexChar()
        << encrypt(std::to_string(x.uid)) << someRANDOMnonHexChar();
    return out;
}

std::istream &operator>>(std::istream &in, criminal_record &x)
{
    extern std::string delim;
    std::string dob, reward, uid;
    getline(in, x.name, delim);
    if (x.name.empty())
        return in;
    getline(in, x.father, delim);
    getline(in, x.address, delim);
    getline(in, x.offense, delim);
    getline(in, x.crime_codes, delim);
    getline(in, x.blood, delim);
    getline(in, x.sex, delim);
    getline(in, dob, delim);
    getline(in, reward, delim);
    getline(in, uid, delim);
    x.length = x.name.length() + x.father.length() + x.address.length() + x.offense.length() + x.crime_codes.length() + x.blood.length() + x.sex.length() + dob.length() + reward.length() + uid.length() + 10;
    x.dob = stringToDate(decrypt(dob));
    x.reward = std::stoul(decrypt(reward));
    x.uid = std::stoull(decrypt(uid));
    return in;
}

void criminal_record::_generateUID()
{
    uid = ch::system_clock::now().time_since_epoch().count() * ch::system_clock::period::num / ch::system_clock::period::den;
}

void criminal_record::_encode()
{
    name = encrypt(to_upper(name));
    father = encrypt(to_upper(father));
    address = encrypt(to_upper(address));
    offense = encrypt(to_upper(offense));
    crime_codes = encrypt(to_upper(crime_codes));
    blood = encrypt(to_upper(blood));
    sex = encrypt(to_upper(sex));
}

void criminal_record::_decode()
{
    name = decrypt(to_upper(name));
    father = decrypt(to_upper(father));
    address = decrypt(to_upper(address));
    offense = decrypt(to_upper(offense));
    crime_codes = decrypt(to_upper(crime_codes));
    blood = decrypt(to_upper(blood));
    sex = decrypt(to_upper(sex));
}

void criminal_record::_display()
{
    std::cout << "\nName of Criminal: " << decrypt(name) << " (" << uid << ")";
    std::cout << "\nSex: " << decrypt(sex);
    std::cout << "\nDate of Birth (dd mm yyyy): " << dob.dd << " " << dob.mm << " " << dob.yyyy;
    std::cout << "\nFather's Name: " << decrypt(father);
    std::cout << "\nAddress: " << decrypt(address);
    std::cout << "\nCrime: " << decrypt(offense);
    std::cout << "\nBlood Group: " << decrypt(blood);
    std::cout << "\nCharges (IPC): " << decrypt(crime_codes);
    std::cout << "\nReward (Rs.): " << reward << '\n';
}

void criminal_record::_read()
{
#ifdef _GCC_VERSION_LESS_THAN_8_
    std::ifstream ifile((cp / "cbi.dat").string());
#elif _GCC_VERSION_MORE_THAN_8_
    std::ifstream ifile(cp / "cbi.dat");
#endif
    bool present = false;
    ifile.seekg(0, std::ios::beg);
    while (ifile >> criminal)
    {
        _display();
        std::cout << '\n';
        present = true;
    }
    if (not present)
        std::cout << "No details present on this device!\n";
    ifile.close();
}

void criminal_record::_search()
{
    std::string query;
    bool found = false;
#ifdef _GCC_VERSION_LESS_THAN_8_
    std::ifstream ifile((cp / "cbi.dat").string());
#elif _GCC_VERSION_MORE_THAN_8_
    std::ifstream ifile(cp / "cbi.dat");
#endif
    std::cout << "\nEnter name of the criminal who has to be searched: ";

    std::getline(std::cin, query);
    query = encrypt(to_upper(query));
    ifile.seekg(0, std::ios::beg);
    while (ifile)
    {
        ifile >> criminal;
        if (query == name)
        {
            found = true;
            std::cout << "\nThe record(s) of the criminal(s): \n";
            _display();
        }
    }
    if (not found)
        std::cout << "\nNo record found!";
    ifile.close();
}

void criminal_record::_write()
{
namelb1:
    std::cout << "\nEnter name of the criminal: ";

    std::getline(std::cin, name);
    if (not isValidName(name))
    {
        std::cout << "\nInvalid Name!\n";
        goto namelb1;
    }
sexlb1:
    std::cout << "\nSex: ";

    std::getline(std::cin, sex);
    if (not isValidSex(sex[0]) or sex.length() != 1)
    {
        std::cout << "\nInvalid Sex!\n";
        goto sexlb1;
    }
datelb1:
    std::cout << "\nEnter date of birth (dd mm yyyy): ";

    std::cin >> dob.dd >> dob.mm >> dob.yyyy;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (not isValidDate(dob))
    {
        std::cout << "\nInvalid Date!\n";
        goto datelb1;
    }
fatherlb1:
    std::cout << "\nEnter father's name: ";

    std::getline(std::cin, father);
    if (not isValidName(father))
    {
        std::cout << "\nInvalid Name!\n";
        goto fatherlb1;
    }
addresslb1:
    std::cout << "\nEnter address: ";

    std::getline(std::cin, address);
    if (not isValidAddress(address))
    {
        std::cout << "\nInvalid Address!\n";
        goto addresslb1;
    }
    std::cout << "\nEnter crime committed: ";

    std::getline(std::cin, offense);
bloodlb1:
    std::cout << "\nEnter blood group: ";

    std::getline(std::cin, blood);
    if (not isValidBlood(std::string(blood)))
    {
        std::cout << "\nInvalid Blood!\n";
        goto bloodlb1;
    }
    std::cout << "\nEnter charges: ";

    std::getline(std::cin, crime_codes);
    std::cout << "\nEnter reward on the criminal (Rs.): ";

    std::cin >> reward;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    _encode();
    _generateUID();
#ifdef _GCC_VERSION_LESS_THAN_8_
    std::ofstream ofile((cp / "cbi.dat").string(), std::ios::app);
#elif _GCC_VERSION_MORE_THAN_8_
    std::ofstream ofile(cp / "cbi.dat", std::ios::app);
#endif
    ofile << criminal;
    ofile.close();
}

void criminal_record::_delete()
{
    unsigned long long int _uid;
    bool isAnyChangeMade = false;
    std::cout << "\nEnter the uid of the criminal whose record you want to delete: ";

    std::cin >> _uid;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#ifdef _GCC_VERSION_LESS_THAN_8_
    std::ifstream ifile((cp / "cbi.dat").string());
    std::ofstream ofile((cp / "new").string(), std::ios::trunc);
#elif _GCC_VERSION_MORE_THAN_8_
    std::ifstream ifile(cp / "cbi.dat");
    std::ofstream ofile(cp / "new", std::ios::trunc);
#endif
    ifile.seekg(0, std::ios::beg);
    while (ifile)
    {
        ifile >> criminal;
        if (_uid != uid)
        {
            ofile << criminal;
            isAnyChangeMade = true;
        }
    }
    ifile.close();
    ofile.close();
    fs::remove(cp / "cbi.dat");
    fs::rename(cp / "new", cp / "cbi.dat");
    if (not isAnyChangeMade)
        std::cout << "\nThe provided UID doesn't point to any of the criminals!";
}

void criminal_record::_modify()
{
    std::string str;
    unsigned long long int _uid;
    bool found = false;
    char choice;
#ifdef _GCC_VERSION_LESS_THAN_8_
    std::fstream f((cp / "cbi.dat").string(), std::ios::in | std::ios::out);
#elif _GCC_VERSION_MORE_THAN_8_
    std::fstream f(cp / "cbi.dat", std::ios::in | std::ios::out);
#endif
    f.seekg(0, std::ios::beg);
    std::cout << "\nEnter uid of the criminal whose record you want to modify: ";
    std::cin >> _uid;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << '\n';
    while (f)
    {
        f >> criminal;
        if (_uid == uid)
        {
            found = true;
            for (int i = 1; i <= 9; i++)
            {
                switch (i)
                {
                case 1:
                    str = "name              ";
                    break;
                case 2:
                    str = "sex               ";
                    break;
                case 3:
                    str = "date of birth     ";
                    break;
                case 4:
                    str = "father's name     ";
                    break;
                case 5:
                    str = "address           ";
                    break;
                case 6:
                    str = "crime committed   ";
                    break;
                case 7:
                    str = "blood group       ";
                    break;
                case 8:
                    str = "charges           ";
                    break;
                case 9:
                    str = "reward on criminal";
                    break;
                }
                str = std::string("Press ") + char(i + 48) + std::string(" to change ") + str;
                Align0(str, padding_horizontal);
            }
            _decode();
        beginning:
            std::cout << '\n';
            choice = _getch();
            putch(choice);
            std::cout << '\n'
                      << '\n';
            ;
            switch (choice)
            {
            case '1':
            namelb2:
                std::cout << "Enter new name: ";

                std::getline(std::cin, name);
                if (not isValidName(name))
                {
                    std::cout << "\nInvalid Name!";
                    goto namelb2;
                }
                break;
            case '2':
            sexlb2:
                std::cout << "Enter new sex: ";

                std::getline(std::cin, sex);
                if (not isValidSex(sex[0]))
                {
                    std::cout << "\nInvalid Sex!";
                    goto sexlb2;
                }
                break;
            case '3':
            doblb2:
                std::cout << "Enter new date of birth (dd mm yyyy): ";

                std::cin >> dob.mm >> dob.dd >> dob.yyyy;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (not isValidDate(dob))
                {
                    std::cout << "\nInvalid Date!";
                    goto doblb2;
                }
                break;
            case '4':
            fatherlb2:
                std::cout << "Enter new father's name: ";

                std::getline(std::cin, father);
                if (not isValidName(father))
                {
                    std::cout << "\nInvalid Name!";
                    goto fatherlb2;
                }
                break;
            case '5':
            addresslb2:
                std::cout << "Enter new address: ";

                std::getline(std::cin, address);
                if (not isValidAddress(address))
                {
                    std::cout << "\nInvalid Address!";
                    goto addresslb2;
                }
                break;
            case '6':
                std::cout << "Enter new crimes committed: ";

                std::getline(std::cin, offense);
                break;
            case '7':
            bloodlb2:
                std::cout << "Enter new blood group: ";

                std::getline(std::cin, blood);
                if (not isValidBlood(blood))
                {
                    std::cout << "\nInvalid Blood Group!";
                    goto bloodlb2;
                }
                break;
            case '8':
                std::cout << "Enter new charges: ";

                std::getline(std::cin, crime_codes);
                break;
            case '9':
                std::cout << "Enter new reward (Rs.): ";

                std::cin >> reward;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            default:
                std::cout << "\nWrong Choice!";
                goto beginning;
                break;
            }
            _encode();
            f.seekg(criminal.length, std::ios::cur);
            f << criminal;
            break;
        }
    }
    if (found == false)
        std::cout << "\nNo record found!";
    f.close();
}
