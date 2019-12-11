#include "loaders.h"

void SetWindow(int Width, int Height, bool enableScrollBar)
{
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;
    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;
    if (enableScrollBar)
        coord.Y = 300;                               // Enable Scroll Bar
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); // Get Handle
    SetConsoleScreenBufferSize(Handle, coord);       // Set Buffer Size
    SetConsoleWindowInfo(Handle, TRUE, &Rect);       // Set Window Size
}

void Align0(std::string str, int i, bool change_line)
{
    int len = str.length();
    if (len % 2 == 0)
        str += ' ';
    std::cout << std::setw(((console_width / 2) + len / 2) - i) << str;
    if (change_line)
        std::cout << '\n';
}

void Load0(std::string str, int k, int padding_change, bool change_line)
{
    rlutil::cls();
    for (int i = 0; i < padding_vertical - padding_change; i++)
        std::cout << '\n';
    Align0(str, k, change_line);
    if (change_line)
        std::cout << '\n';
}

void Load0(std::string str1, std::string str2, int k)
{
    Load0(str1, 0, 2);
    Align0(str2, k);
}

void Load0(std::string str1, std::string str2, std::string str3, int k)
{
    Load0(str1, str2, 1);
    std::cout << '\n';
    Align0(str3, k);
}
