#include <algorithm>
//#include <base64.h>
//#include <cctype>
//#include <chrono>
#include <conio.h>
//#include <cstdio>
//#include <cstdlib>
//#include <cstring>
//#include <ctime>
//#include <dos.h>
#include <fstream>
#include <iomanip>
#include <iostream>
//#include <ratio>
#include <rlutil.h>
//#include <sstream>
#include <thread>
//#include <wincon.h>
//#include <windef.h>
//#include <windows.h>

#define console_width 80
#define padding_horizontal 13
#define padding_vertical 9
#define maxlen 80

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
using namespace rlutil;

struct date
{
    unsigned short dd, mm, yyyy;
};

bool iequals(const string& a, const string& b)
{
    return equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}

bool isValidName(string name)
{
    for(char &a: name)
        if(!(isalpha(a) or isspace(a)))
            return false;
    return true;
}

bool isValidSex(char sex)
{
    if(sex=='m' or sex=='M' or sex=='f' or sex=='F')
        return true;
    return false;
}

bool isValidDate(date dob)
{
    if(!(1582<=dob.yyyy))
        return false;
    if(!(1<=dob.mm and dob.mm<=12))
        return false;
    if(!(1<=dob.dd and dob.dd<=31))
        return false;
    if(dob.dd==31 and (dob.mm==2 or dob.mm==4 or dob.mm==6 or dob.mm==9 or dob.mm==11))
        return false;
    if(dob.dd==30 and dob.mm==2)
        return false;
    if(dob.mm==2 and dob.dd==29 and dob.yyyy%4!=0)
        return false;
    if(dob.mm==2 and dob.dd==29 and dob.yyyy%400==0)
        return true;
    if(dob.mm==2 and dob.dd==29 and dob.yyyy%100==0)
        return false;
    if(dob.mm==2 and dob.dd==29 and dob.yyyy%4==0)
        return true;
    return true;
}

bool isValidBlood(string blood)
{
    if(iequals(blood, string("ABP")) or iequals(blood, string("ABN")) or iequals(blood, string("AP"))
    or iequals(blood, string("AN")) or iequals(blood, string("BP")) or iequals(blood, string("BN"))
    or iequals(blood, string("OP")) or iequals(blood, string("ON")))
        return true;
    return false;
}

bool isValidAddress(string address)
{
    for(char &a: address)
        if(!(isalnum(a) or isspace(a)))
            return false;
    return true;
}


static const string base64_chars ="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                  "abcdefghijklmnopqrstuvwxyz"
                                  "0123456789+/";

static inline bool is_base64(unsigned char c)
{
    return (isalnum(c)||(c=='+')||(c=='/'));
}

string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len)
{
    string ret;
    int i=0;
    int j=0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    while(in_len--)
    {
        char_array_3[i++]=*(bytes_to_encode++);
        if(i==3)
        {
            char_array_4[0]=(char_array_3[0] & 0xfc) >> 2;
            char_array_4[1]=((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2]=((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3]=char_array_3[2] & 0x3f;
            for(i=0; i<4; i++)
            ret+=base64_chars[char_array_4[i]];
            i=0;
        }
    }
    if(i)
    {
        for(j=i; j<3; j++)
        char_array_3[j]='\0';
        char_array_4[0]=(char_array_3[0] & 0xfc) >> 2;
        char_array_4[1]=((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2]=((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        for (j = 0; j<(i+1); j++)
            ret+=base64_chars[char_array_4[j]];
        while((i++)<3)
          ret+='=';
    }
    return ret;
}

string base64_decode(string const& encoded_string)
{
    int in_len=encoded_string.size();
    int i=0;
    int j=0;
    int in_=0;
    unsigned char char_array_4[4], char_array_3[3];
    string ret;
    while (in_len-- and ( encoded_string[in_]!='=') and is_base64(encoded_string[in_]))
    {
        char_array_4[i++]=encoded_string[in_];
        in_++;
        if(i==4)
        {
            for (i=0; i<4; i++)
                char_array_4[i]=base64_chars.find(char_array_4[i]);
            char_array_3[0]=(char_array_4[0] << 2)+((char_array_4[1] & 0x30) >> 4);
            char_array_3[1]=((char_array_4[1] & 0xf) << 4)+((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2]=((char_array_4[2] & 0x3) << 6)+char_array_4[3];
            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    if(i)
    {
        for(j=0; j<i; j++)
            char_array_4[j]=base64_chars.find(char_array_4[j]);
        char_array_3[0]=(char_array_4[0] << 2)+((char_array_4[1] & 0x30) >> 4);
        char_array_3[1]=((char_array_4[1] & 0xf) << 4)+((char_array_4[2] & 0x3c) >> 2);
        for (j = 0; (j < i - 1); j++)
            ret+=char_array_3[j];
    }
    return ret;
}

struct credentials
{
    string user;
    string pwd;
    string newpwd;
    string confirm;
};

string to_upper(string str)
{
    transform(str.begin(), str.end(),str.begin(), ::toupper);
    return str;
}

void Align0(string str, int i, bool change_line=true)
{
    int len=str.length();
    if(len%2==0)
        str+=" ";
    cout<<setw(((console_width/2)+len/2)-i)<<str;
    if(change_line)
        cout<<endl;
}

void Load0(string str, int k, int padding_change, bool change_line=true)
{
    system("cls");
    for(int i=0; i<padding_vertical-padding_change; i++)
        cout<<'\n';
    Align0(str, k, change_line);
    if(change_line)
        cout<<endl;
}

void Load0(string str1, string str2, int k)
{
    Load0(str1, 0, 2);
    Align0(str2, k);
}

void Load0(string str1, string str2, string str3, int k)
{
    Load0(str1, str2, 1);
    cout<<endl;
    Align0(str3, k);
}

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


class xCredentials
{
    char user[maxlen], pwd[maxlen];
public:
    bool userisAdmin;
    void construct(string u, string p)
    {
        strcpy(user, base64_encode(reinterpret_cast<const unsigned char*>(u.c_str()), u.length()).c_str());
        strcpy(pwd, base64_encode(reinterpret_cast<const unsigned char*>(p.c_str()), p.length()).c_str());
    }
    bool _Check(bool);
    void _Save();
    bool _isUserUnique();
    bool _Delete();
    void _Modify(string, string);
}xDefault;

bool xCredentials::_Check(bool doLog=true)
{
    string u(user), p(pwd);
    bool xSet=false;
    ifstream ifile("data", ios::binary);
    ifile.seekg(0, ios::beg);
    ifile.read((char*)&xDefault, sizeof(xDefault));
    while(ifile and not xSet)
    {
        if(u==string(user) and p==string(pwd))
            xSet=true;
        ifile.read((char*)&xDefault, sizeof(xDefault));
    }
    if(doLog)
    {
        string str_grant="Access Granted!", str_deny="Access Denied!";
        if(xSet)
            {
                Load0(str_grant, 0, -1);
                //duration< int,ratio<60*60*24> > one_day(1);
                system_clock::time_point today=system_clock::now();
                time_t tt=system_clock::to_time_t(today);
                ofstream ofile("logonDetails", ios::app);
                ofile<<endl<<ctime(&tt)<<endl<<"UserId : "<<base64_decode(u)<<endl;
                if(u==string("MHhBZG1pbkNJRA=="))
                    userisAdmin=true;
                else
                    userisAdmin=false;
                return true;
            }
        Load0(str_deny, 0, -1);
    }
    return xSet;
}

void xCredentials::_Save()
{
    ofstream ofile("data", ios::app|ios::binary);
    ofile.write((char*)&xDefault, sizeof(xDefault));
    ofile.close();
}

bool xCredentials::_isUserUnique()
{
    string u(user), p(pwd);
    ifstream ifile("data", ios::binary);
    ifile.seekg(0, ios::beg);
    ifile.read((char*)&xDefault, sizeof(xDefault));
    while(ifile)
    {
        if(u==string(user))
            return false;
        ifile.read((char*)&xDefault, sizeof(xDefault));
    }
    construct(base64_decode(u), base64_decode(p));    //Reset the values of xDefault
    return true;
}

bool xCredentials::_Delete()
{
    string u(user);
    bool isAnyChangeMade=false;
    ifstream ifile("data", ios::binary);
    ofstream ofile("new", ios::out|ios::binary);
    ifile.seekg(0, ios::beg);
    ifile.read((char*)&xDefault, sizeof(xDefault));
    while(ifile)
    {
        if(u!=string(user))
            ofile.write((char*)&xDefault, sizeof(xDefault));
        else
            isAnyChangeMade=true;
        ifile.read((char*)&xDefault, sizeof(xDefault));
    }
    ifile.close();
    ofile.close();
    remove("data");
    rename("new", "data");
    return isAnyChangeMade;
}

void xCredentials::_Modify(string u, string p)
{
    u=base64_encode(reinterpret_cast<const unsigned char*>(u.c_str()), u.length());
    fstream f("data", ios::in|ios::out|ios::binary);
    f.seekg(0,ios::beg);
    f.read((char*)&xDefault, sizeof(xDefault));
    int a=f.tellg();
    while(f)
    {
        if(u==string(user))
        {
            xDefault.construct(base64_decode(u), p);
            f.seekg(a-sizeof(xDefault), ios::beg);
            f.write((char*)&xDefault, sizeof(xDefault));
            break;
        }
        f.read((char*)&xDefault, sizeof(xDefault));
    }
    f.close();
}

void caller2(bool userisAdmin, bool bipass)
{
    int i=0;
    string str="Welcome!";
    if(not bipass)
    {
        Load0(str, 0, -1);
        sleep_until(system_clock::now()+seconds(1));
        str="Loading";
        Load0(str, 1, -1, false);
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

class criminal_record
{
private:
    char name[maxlen], father[maxlen], address[maxlen], offense[maxlen], crime_codes[maxlen], blood[5], sex[5];
    date dob;
    unsigned int reward, uid;
public:
    void _read();
    void _write();
    void _search();
    void _delete();
    void _modify();
    void _display();
    void _encode();
    void _decode();
    void _generateUID();
} criminal;

void criminal_record::_generateUID()
{
    time_t t;
    srand((unsigned int)time(&t));
    fstream f("uids", ios::in|ios::out);
    f>>uid;
    f.close();
    f.open("uids", ios::out);
    f<<++uid;
    f.close();
    uid+=rand();
    if      (0<=uid and uid<10)         uid*=10000;
    else if(10<=uid and uid<100)        uid*=1000;
    else if(100<=uid and uid<1000)      uid*=100;
    else if(1000<=uid and uid<10000)    uid*=10;
    else if(10000<=uid and uid<100000)  uid*=1;
    else ;
    uid+=(rand()%10);
}

void criminal_record::_encode()
{
    strcpy(name, to_upper(string(name)).c_str());
    strcpy(father, to_upper(string(father)).c_str());
    strcpy(address, to_upper(string(address)).c_str());
    strcpy(offense, to_upper(string(offense)).c_str());
    strcpy(crime_codes, to_upper(string(crime_codes)).c_str());
    strcpy(blood, to_upper(string(blood)).c_str());
    strcpy(sex, to_upper(string(sex)).c_str());
    strcpy(name, base64_encode(reinterpret_cast<const unsigned char*>(name), strlen(name)).c_str());
    strcpy(father, base64_encode(reinterpret_cast<const unsigned char*>(father), strlen(father)).c_str());
    strcpy(address, base64_encode(reinterpret_cast<const unsigned char*>(address), strlen(address)).c_str());
    strcpy(offense, base64_encode(reinterpret_cast<const unsigned char*>(offense), strlen(offense)).c_str());
    strcpy(crime_codes, base64_encode(reinterpret_cast<const unsigned char*>(crime_codes), strlen(crime_codes)).c_str());
    strcpy(blood, base64_encode(reinterpret_cast<const unsigned char*>(blood), strlen(blood)).c_str());
    strcpy(sex, base64_encode(reinterpret_cast<const unsigned char*>(sex), strlen(sex)).c_str());
}

void criminal_record::_decode()
{
    strcpy(name, base64_decode(string(name)).c_str());
    strcpy(father, base64_decode(string(father)).c_str());
    strcpy(address, base64_decode(string(address)).c_str());
    strcpy(offense, base64_decode(string(offense)).c_str());
    strcpy(crime_codes, base64_decode(string(crime_codes)).c_str());
    strcpy(blood, base64_decode(string(blood)).c_str());
    strcpy(sex, base64_decode(string(sex)).c_str());
}

void criminal_record::_display()
{
    cout<<"\nName of Criminal: "<<base64_decode(string(name))<<" ("<<uid<<")";
    cout<<"\nSex: "<<base64_decode(string(sex));
    cout<<"\nDate of Birth (mm dd yyyy): "<<dob.mm<<" "<<dob.dd<<" "<<dob.yyyy;
    cout<<"\nFather's Name: "<<base64_decode(string(father));
    cout<<"\nAddress: "<<base64_decode(string(address));
    cout<<"\nCrime: "<<base64_decode(string(offense));
    cout<<"\nBlood Group: "<<base64_decode(string(blood));
    cout<<"\nCharges (IPC): "<<base64_decode(string(crime_codes));
    cout<<"\nReward (Rs.): "<<reward<<endl;
}

void criminal_record::_read()
{
    ifstream ifile("cbi", ios::binary);
    ifile.seekg(0, ios::beg);
    ifile.read((char*)&criminal, sizeof(criminal));
    while(ifile)
    {
        _display();
        ifile.read((char*)&criminal, sizeof(criminal));
        cout<<'\n';
    }
    ifile.close();
}

void criminal_record::_search()
{
    string query;
    bool found = false;
    ifstream ifile("cbi", ios::binary);
    cout<<"\nEnter name of the criminal who has to be searched: ";
    cin.clear();cin.sync();
    getline(cin, query);
    query=to_upper(query);
    query=base64_encode(reinterpret_cast<const unsigned char*>(query.c_str()), query.length());
    ifile.seekg(0, ios::beg);
    ifile.read((char*)&criminal, sizeof(this));
    while(ifile)
    {
        if(query==string(name))
        {
            found = true;
            cout<<"\nThe record(s) of the criminal(s): \n";
            _display();
        }
        ifile.read((char*)&criminal, sizeof(criminal));
    }
    if(not found) cout<<"\nNo record found!";
    ifile.close();
}

void criminal_record::_write()
{
    namelb1:
    cout<<"\nEnter name of the criminal: ";
    cin.clear();cin.sync();
    cin.get(name, maxlen);
    if(not isValidName(string(name)))
    {
        cout<<"\nInvalid Name!\n";
        goto namelb1;
    }
    sexlb1:
    cout<<"\nSex: ";
    cin.clear();cin.sync();
    cin.get(sex, 2);
    if(not isValidSex(sex[0]))
    {
        cout<<"\nInvalid Sex!\n";
        goto sexlb1;
    }
    datelb1:
    cout<<"\nEnter date of birth (mm dd yyyy): ";
    cin.clear();cin.sync();
    cin>>dob.mm>>dob.dd>>dob.yyyy;
    if(not isValidDate(dob))
    {
        cout<<"\nInvalid Date!\n";
        goto datelb1;
    }
    fatherlb1:
    cout<<"\nEnter father's name: ";
    cin.clear();cin.sync();
    cin.get(father, maxlen);
    if(not isValidName(string(father)))
    {
        cout<<"\nInvalid Name!\n";
        goto fatherlb1;
    }
    addresslb1:
    cout<<"\nEnter address: ";
    cin.clear();cin.sync();
    cin.get(address, maxlen);
    if(not isValidAddress(string(address)))
    {
        cout<<"\nInvalid Address!\n";
        goto addresslb1;
    }
    cout<<"\nEnter crime committed: ";
    cin.clear();cin.sync();
    cin.get(offense, maxlen);
    bloodlb1:
    cout<<"\nEnter blood group: ";
    cin.clear();cin.sync();
    cin.get(blood, 4);
    if(not isValidBlood(string(blood)))
    {
        cout<<"\nInvalid Blood!\n";
        goto bloodlb1;
    }
    cout<<"\nEnter charges: ";
    cin.clear();cin.sync();
    cin.get(crime_codes, maxlen);
    cout<<"\nEnter reward on the criminal (Rs.): ";
    cin.clear();cin.sync();
    cin>>reward;
    _encode();
    _generateUID();
    ofstream ofile("cbi", ios::app|ios::binary);
    ofile.write((char*)&criminal, sizeof(criminal));
    ofile.close();
}

void criminal_record::_delete()
{
    unsigned int _uid;
    cout<<"Enter the uid of the criminal whose record you want to delete: ";
    cin.clear();cin.sync();
    cin>>_uid;
    ifstream ifile("cbi", ios::binary);
    ofstream ofile("new", ios::app|ios::binary);
    ifile.seekg(0, ios::beg);
    ifile.read((char*)&criminal, sizeof(criminal));
    while(ifile)
    {
        if(_uid!=uid)
            ofile.write((char*)&criminal, sizeof(criminal));
        ifile.read((char*)&criminal, sizeof(criminal));
    }
    ifile.close();
    ofile.close();
    remove("cbi");
    rename("new", "cbi");
}

void criminal_record::_modify()
{
    string str;
    unsigned int _uid;
    bool found=false;
    char choice;
    fstream f("cbi", ios::in|ios::out|ios::binary);
    f.seekg(0, ios::beg);
    cout<<"\nEnter uid of the criminal whose record you want to modify: ";
    cin.clear();cin.sync();
    cin>>_uid;
    cout<<endl;
    f.read((char*)&criminal, sizeof(criminal));
    int a=f.tellg();
    while(f)
    {
        if(_uid==uid)
        {
            found=true;
            for(int i=1; i<=9; i++)
            {
                switch(i)
                {
                    case 1:
                        str="name              ";
                        break;
                    case 2:
                        str="sex               ";
                        break;
                    case 3:
                        str="date of birth     ";
                        break;
                    case 4:
                        str="father's name     ";
                        break;
                    case 5:
                        str="address           ";
                        break;
                    case 6:
                        str="crime committed   ";
                        break;
                    case 7:
                        str="blood group       ";
                        break;
                    case 8:
                        str="charges           ";
                        break;
                    case 9:
                        str="reward on criminal";
                        break;
                }
                str=string("Press ")+char(i+48)+string(" to change ")+str;
                Align0(str, padding_horizontal);
            }
            _decode();
            beginning:
            cout<<endl;
            choice=_getch();
            putch(choice);
            cout<<endl<<endl;;
            switch(choice)
            {
                case '1':
                    namelb2:
                    cout<<"Enter new name: ";
                    cin.clear(); cin.sync();
                    cin.get(name, maxlen);
                    if(not isValidName(string(name)))
                    {
                        cout<<"\nInvalid Name!";
                        goto namelb2;
                    }
                    break;
                case '2':
                    sexlb2:
                    cout<<"Enter new sex: ";
                    cin.clear(); cin.sync();
                    cin.get(sex, 2);
                    if(not isValidSex(sex[0]))
                    {
                        cout<<"\nInvalid Sex!";
                        goto sexlb2;
                    }
                    break;
                case '3':
                    doblb2:
                    cout<<"Enter new date of birth (mm dd yyyy): ";
                    cin.clear(); cin.sync();
                    cin>>dob.mm>>dob.dd>>dob.yyyy;
                    if(not isValidDate(dob))
                    {
                        cout<<"\nInvalid Date!";
                        goto sexlb2;
                    }
                    break;
                case '4':
                    fatherlb2:
                    cout<<"Enter new father's name: ";
                    cin.clear(); cin.sync();
                    cin.get(father, maxlen);
                    if(not isValidName(string(father)))
                    {
                        cout<<"\nInvalid Name!";
                        goto fatherlb2;
                    }
                    break;
                case '5':
                    addresslb2:
                    cout<<"Enter new address: ";
                    cin.clear(); cin.sync();
                    cin.get(address, maxlen);
                    if(not isValidAddress(string(address)))
                    {
                        cout<<"\nInvalid Address!";
                        goto addresslb2;
                    }
                    break;
                case '6':
                    cout<<"Enter new crimes committed: ";
                    cin.clear(); cin.sync();
                    cin.get(offense, maxlen);
                    break;
                case '7':
                    bloodlb2:
                    cout<<"Enter new blood group: ";
                    cin.clear(); cin.sync();
                    cin.get(blood, 3);
                    if(not isValidBlood(string(blood)))
                    {
                        cout<<"\nInvalid Blood Group!";
                        goto bloodlb2;
                    }
                    break;
                case '8':
                    cout<<"Enter new charges: ";
                    cin.clear(); cin.sync();
                    cin.get(crime_codes, maxlen);
                    break;
                case '9':
                    cout<<"Enter new reward (Rs.): ";
                    cin.clear(); cin.sync();
                    cin>>reward;
                    break;
                default:
                    cout<<"\nWrong Choice!";
                    goto beginning;
                    break;
            }
            _encode();
            f.seekg(a-sizeof(criminal), ios::beg);
            f.write((char*)&criminal, sizeof(criminal));
            break;
        }
        f.read((char*)&criminal, sizeof(criminal));
        a=f.tellg();
    }
    if(found==false)
        cout<<"\nNo record found!";
    f.close();
}

void AdminMenuLoader(bool);

void user_create()
{
    credentials new_user=caller1(false);
    string str="Creating";
    Load0(str, 1, -1, false);cout<<'\b';
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
            Load0(str, 0, -1);
            sleep_until(system_clock::now()+seconds(2));
        }
        else
        {
            str="Error! The user already exists!";
            Load0(str, 0, -1);
            sleep_until(system_clock::now()+seconds(2));
        }
    }
    else
    {
        str="Error! The passwords do not match!";
        Load0(str, 0, -1);
        sleep_until(system_clock::now()+seconds(2));
    }
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
    AdminMenuLoader(true);
}

void user_modify()
{
    credentials modified_user=caller1(true, true);
    string str="Working on it";
    Load0(str, 1, -1, false);
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
            Load0(str, 0, -1);
            sleep_until(system_clock::now()+seconds(2));
        }
        else
        {
            str="Error! The passwords do not match!";
            Load0(str, 0, -1);
            sleep_until(system_clock::now()+seconds(2));
        }
    }
    else
    {
        str="User's original credentials are not correct!";
        Load0(str, 0, -1);
        sleep_until(system_clock::now()+seconds(2));
    }
    AdminMenuLoader(true);
}

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

void AdminMenuLoader(bool bipass=false)
{
    hidecursor();
    int i=0;
    string str="Welcome to Admin Panel!";
    if(not bipass)
    {
        Load0(str, 0, -1);
        sleep_until(system_clock::now()+seconds(2));
        str="Loading";
        Load0(str, 1, -1, false);
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
                AdminMenuLoader();
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

int main()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rect;
    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = console_width;
    rect.Right = 300;
    SetConsoleWindowInfo(handle, 1, &rect);
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
