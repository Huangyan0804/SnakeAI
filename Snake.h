#pragma once
#include "Food.h"
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