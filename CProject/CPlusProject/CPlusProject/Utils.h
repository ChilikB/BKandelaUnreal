#pragma once

#include <iostream>
#include <windows.h> 

static class Utils
{
public:
    static void SetConsoleColor(int textColor, int bgColor) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
    }
public:
    static void ResetConsoleColor() {
        SetConsoleColor(7, 0);
	}
};

