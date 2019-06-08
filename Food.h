#pragma once
#include "GameSetting.h"
#include <vector>
using namespace std;

class Food {
private:
    Cor food_pos;

public:
    Cor get_food();
    Food() {}
    void show_food();
    void refresh_food(std::vector<Cor> v);
    
};