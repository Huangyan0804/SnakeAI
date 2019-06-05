#include "Snake.h"
#include "Food.h"
#include "GameSetting.h"
#include "Show.h"
#include <conio.h>
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;
int score = 0;
Snake::Snake()
{
    move_size.x = GameSetting::window_width - 30; // [1 , size.x]
    move_size.y = GameSetting::window_height - 1; // [1 ,size.y]

    // 移动方向向右
    head_dir = 4;

    snake_live = true;
    Cor snake_head;

    // 初始蛇身
    snake_head.x = move_size.x / 2;
    snake_head.y = move_size.y / 2;
    this->snake_body.push_back(snake_head);
    snake_head.x--;
    this->snake_body.push_back(snake_head);
    snake_head.x--;
    this->snake_body.push_back(snake_head);
}

bool Snake::is_eat_food(Food& f)
{
    Cor food_pos = f.get_food();
    if (snake_body[0].x == food_pos.x && snake_body[0].y == food_pos.y) {
        f.refresh_food(snake_body);
        score++;
        return true;
    }
    snake_body.pop_back();
    return false;
}

void Snake::show_snake()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 10); // 设置绿色
    for (auto i = this->snake_body.begin(); i != this->snake_body.end(); i++) {
        gotoxy(i->x, i->y);
        cout << "O";
    }
    SetConsoleTextAttribute(handle, 7); // 恢复颜色
}

void Snake::snake_move()
{
    char input;
    if (_kbhit()) {
        input = _getch();
        if (input == 'w' && head_dir != 2) {
            this->head_dir = 1;
        } else if (input == 's' && head_dir != 1) {
            this->head_dir = 2;
        } else if (input == 'a' && head_dir != 4) {
            this->head_dir = 3;
        } else if (input == 'd' && head_dir != 3) {
            this->head_dir = 4;
        }
    }
    Cor head = snake_body[0];
    if (head_dir == 1) {
        head.y--;
    } else if (head_dir == 2) {
        head.y++;
    } else if (head_dir == 3) {
        head.x--;
    } else if (head_dir == 4) {
        head.x++;
    }
    snake_body.insert(snake_body.begin(), head);
}

void Snake::snake_erase()
{
    gotoxy(snake_body.back().x, snake_body.back().y);
    cout << " ";
}
bool Snake::is_alive()
{
    if (snake_body[0].x < 1 || snake_body[0].x > move_size.x
        || snake_body[0].y < 1 || snake_body[0].y > move_size.y) {
        snake_live = false;
        return false;
    }
    for (int i = 1; i < snake_body.size(); i++) {
        if (snake_body[0].x == snake_body[i].x && snake_body[0].y == snake_body[i].y) {
            snake_live = false;
            return false;
        }
    }
    return true;
}