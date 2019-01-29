void SetWindow(int Width, int Height, bool enableScrollBar=false)
{
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;
    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;
    if(enableScrollBar)
        coord.Y=300;                                      // Enable Scroll Bar
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size
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