#include "Food.h"
#include "GameSetting.h"
#include "Show.h"
#include "Snake.h"
#include <Windows.h>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

Cor Food::get_food()
{
    return food_pos;
}

void Food::refresh_food(vector<Cor>& v)
{
    food_pos.x = rand() % (GameSetting::window_width - 30) + 1;
    food_pos.y = rand() % (GameSetting::window_height - 2) + 1;

    for (int i = 0; i < v.size(); i++) {
        if (v[i].x == food_pos.x && v[i].y == food_pos.y) {
            food_pos.x = rand() % (GameSetting::window_width - 30) + 1;
            food_pos.y = rand() % (GameSetting::window_height - 2) + 1;
            i = 0;
        }
    }

}
void Food::show_food() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 12); // ���ú�ɫ
    Show::gotoxy(food_pos.x, food_pos.y);
    cout << "@";
    SetConsoleTextAttribute(handle, 7); // �ָ���ɫ
}

