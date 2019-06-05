#pragma once
#include "Food.h"
#include "GameSetting.h"
#include "Show.h"
#include <Windows.h>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Snake {
private:
    
    int head_dir;
    bool snake_live;
    Cor move_size;

public:
    vector<Cor> snake_body;
    Snake();
    void show_snake();
    void snake_move();
    bool is_eat_food(Food& f);
    void snake_erase();
    bool is_alive();
};