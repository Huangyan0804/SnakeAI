#pragma once
#include <Windows.h>

class GameInit {
public:
    const int window_width = 80;
    const int window_height = 40;

    void init()
    {
        CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info); //Òþ²ØÊäÈë·ûºÅ
    }
};