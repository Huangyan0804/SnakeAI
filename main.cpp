#pragma once
#include "GameSetting.h"
#include "Show.h"
#include "Snake.h"
#include "Food.h"
#include <cstdlib>
#include <Windows.h>
#include <fstream>
#include <iostream>

using namespace std;
extern int game_speed;
int main()
{

    GameSetting setting;
    Show show;
    Snake snake;
    Food food;
    
    setting.init();
    food.refresh_food(snake.snake_body);
    show.show_last_score();
    show.show_gameinfo();
    while (true) {
        show.show_map();
        show.show_score();
        food.show_food();
        snake.snake_erase();
        snake.is_eat_food(food);
        food.show_food();
        snake.snake_move();
        snake.show_snake();
        if (!snake.is_alive()) {
            show.show_game_over();
            break;
		}
            
		
        Sleep(game_speed);
    }
    system("pause");
    return 0;
}