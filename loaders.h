#pragma once

#include <bits/stdc++.h>
#include <windef.h>
#include <windows.h>
#include "constants.h"

void ClearScreen();
void SetWindow(int Width, int Height, bool enableScrollBar=false);
void Align0(std::string str, int i, bool change_line=true);
void Load0(std::string str, int k, int padding_change, bool change_line=true);
void Load0(std::string, std::string, int);
void Load0(std::string, std::string, std::string, int);
