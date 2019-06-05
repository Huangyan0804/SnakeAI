#pragma once
#include "GameSetting.h"
#include <Windows.h>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Food {
private:
    Cor food_pos;

public:
    Cor get_food();
    Food() {}
    void refresh_food(vector<Cor> &v);
    void show_food();
};