#pragma once
#include <Windows.h>
extern int game_speed;
extern int score;
extern int dx[4];
extern int dy[4];
class GameSetting {
public:
    static const int window_width = 80;
    static const int window_height = 40;
    
    void init(); // 初始化
};