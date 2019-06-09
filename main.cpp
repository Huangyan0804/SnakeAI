#pragma once

/* coding: UTF-8 */

#include "Food.h"
#include "GameSetting.h"
#include "Show.h"
#include "Snake.h"
#include <Windows.h>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <tchar.h>
#include <vector>

using namespace std;

/*

	Editer: HUANG Yan
	Time: 2019:6:7
	project: Snake

*/

int main()
{
    GameSetting setting;
    Show show;
    Snake snake;

    setting.init();
    show.show_start(snake);
    show.show_map();
    snake.food.show_food();
    show.show_last_score();
    show.show_gameinfo();

    while (true) {
        show.show_score(snake);
        if (snake.get_model()) {
            snake.man_make_move();
        } else {
            snake.ai_find_path();
            snake.ai_listen_keboard();
        }
        if (!snake.is_alive() || !snake.get_snake_live()) {
            if (show.show_game_over()) {
                break;
            }
        }
        Sleep(snake.get_speed());
    }
    return 0;
}