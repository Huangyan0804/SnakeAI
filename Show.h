#pragma once
#include <string>
using namespace std;
class Show {

public:
    
    void show_start();
    void show_map();
    void show_score();
    void show_last_score();
    void show_gameinfo();
    void show_game_over();
    static void gotoxy(int x, int y); // move Cursor
    
};