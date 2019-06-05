#pragma once
#include <vector>
#include"GameSetting.h"
class Food {
private:
    Cor food_pos;

public:
    Cor get_food();
    Food() {}
    void refresh_food(std::vector<Cor> &v);
    void show_food();
};