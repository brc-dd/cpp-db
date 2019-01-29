struct credentials
{
    string user;
    string pwd;
    string newpwd;
    string confirm;
};

class xCredentials
{
    char user[maxlen], pwd[maxlen];
public:
    bool userisAdmin;
    void construct(string u, string p)
    {
        strcpy(user, encrypt(u).c_str());
        strcpy(pwd, encrypt(p).c_str());
        if(u==encrypt(string("0xAdminCID")))
            userisAdmin=true;
        else
            userisAdmin=false;
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
                Load0(str_grant, 0, 1);
                //duration< int,ratio<60*60*24> > one_day(1);
                system_clock::time_point today=system_clock::now();
                time_t tt=system_clock::to_time_t(today);
                ofstream ofile("logonDetails", ios::app);
                ofile<<endl<<ctime(&tt)<<endl<<"UserId : "<<decrypt(u)<<endl;
                if(u==encrypt(string("0xAdminCID")))
                    userisAdmin=true;
                else
                    userisAdmin=false;
                return true;
            }
        Load0(str_deny, 0, 1);
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
    construct(decrypt(u), decrypt(p));    //Reset the values of xDefault
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
    u=encrypt(u);
    fstream f("data", ios::in|ios::out|ios::binary);
    f.seekg(0,ios::beg);
    f.read((char*)&xDefault, sizeof(xDefault));
    int a=f.tellg();
    while(f)
    {
        if(u==string(user))
        {
            xDefault.construct(decrypt(u), p);
            f.seekg(a-sizeof(xDefault), ios::beg);
            f.write((char*)&xDefault, sizeof(xDefault));
            break;
        }
        f.read((char*)&xDefault, sizeof(xDefault));
    }
    f.close();
}