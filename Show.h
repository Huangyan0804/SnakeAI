#pragma once
#include "GameSetting.h"
#include <Windows.h>
#include "Snake.h"
using namespace std;
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
    
    void show_start(Snake& snake);
    void show_map();
    void show_score(Snake& s);
    void show_last_score();
    void show_gameinfo();
    bool show_game_over();
    
    
};