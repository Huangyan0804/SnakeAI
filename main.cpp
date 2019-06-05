#include "GameSetting.h"
#include "Show.h"
#include "Snake.h"
#include "Food.h"
#include <Windows.h>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

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