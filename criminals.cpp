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
    strcpy(name, encrypt(string(name)).c_str());
    strcpy(father, encrypt(string(father)).c_str());
    strcpy(address, encrypt(string(address)).c_str());
    strcpy(offense, encrypt(string(offense)).c_str());
    strcpy(crime_codes, encrypt(string(crime_codes)).c_str());
    strcpy(blood, encrypt(string(blood)).c_str());
    strcpy(sex, encrypt(string(sex)).c_str());
}

void criminal_record::_decode()
{
    strcpy(name, decrypt(string(name)).c_str());
    strcpy(father, decrypt(string(father)).c_str());
    strcpy(address, decrypt(string(address)).c_str());
    strcpy(offense, decrypt(string(offense)).c_str());
    strcpy(crime_codes, decrypt(string(crime_codes)).c_str());
    strcpy(blood, decrypt(string(blood)).c_str());
    strcpy(sex, decrypt(string(sex)).c_str());
}

void criminal_record::_display()
{
    cout<<"\nName of Criminal: "<<decrypt(string(name))<<" ("<<uid<<")";
    cout<<"\nSex: "<<decrypt(string(sex));
    cout<<"\nDate of Birth (mm dd yyyy): "<<dob.mm<<" "<<dob.dd<<" "<<dob.yyyy;
    cout<<"\nFather's Name: "<<decrypt(string(father));
    cout<<"\nAddress: "<<decrypt(string(address));
    cout<<"\nCrime: "<<decrypt(string(offense));
    cout<<"\nBlood Group: "<<decrypt(string(blood));
    cout<<"\nCharges (IPC): "<<decrypt(string(crime_codes));
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
    query=encrypt(query);
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
