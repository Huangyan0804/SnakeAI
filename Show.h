#pragma once
#include <Windows.h>
static void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}
class Show {

public:
    
    void show_start();
    void show_map();
    void show_score();
    void show_last_score();
    void show_gameinfo();
    void show_game_over();
    
    
};