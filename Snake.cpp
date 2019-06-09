
#include "Snake.h"
#include "Food.h"
#include "GameSetting.h"
#include "Show.h"
#include <Windows.h>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int score = 0;
#define FOOD 0
#define UNDEFINE int(1e7)
#define SNAKE int(2e7)
const int ERR = -233;

int dir[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

Snake::Snake()
{
    model = true;
    move_size.x = GameSetting::window_width - 21; // [1 , size.x]
    move_size.y = GameSetting::window_height - 1; // [1 , size.y]
    tempsnake.clear();
    snake_body.clear();
    memset(map, 0, sizeof map);
    memset(tmap, 0, sizeof tmap);
    food.refresh_food(snake_body);
    food.show_food();
    // 移动方向向右
    head_dir = 2;
    ai_speed = 50;
    man_speed = 150;
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

int Snake::get_speed()
{
    if (get_model()) {
        return man_speed;
    } else {
        return ai_speed;
    }
}

bool Snake::get_model()
{
    return model;
}

bool Snake::is_eat_food()
{
    Cor food_pos = food.get_food();
    if (snake_body[0].x == food_pos.x && snake_body[0].y == food_pos.y) {
        map[food_pos.x][food_pos.y] = SNAKE;
        food.refresh_food(snake_body);
        score++;
        return true;
    } else {
        map[snake_body.back().x][snake_body.back().y] = UNDEFINE;
        snake_body.pop_back();

        return false;
    }
}

void Snake::show_snake()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 87); // 设置绿色 34/47 纯蓝51 *55 红 6x 纯紫色 85 *87
    gotoxy(snake_body[0].x, snake_body[0].y);
    cout << "*";
    SetConsoleTextAttribute(handle, 47);
    for (int i = 1; i < snake_body.size(); i++) {
        gotoxy(snake_body[i].x, snake_body[i].y);
        cout << "*";
    }

    SetConsoleTextAttribute(handle, 7); // 恢复颜色
}

void Snake::snake_erase()
{
    gotoxy(snake_body.back().x, snake_body.back().y);
    cout << " ";
}
bool Snake::is_alive()
{
    if (snake_body[0].x < 1 || snake_body[0].x > move_size.x - 1
        || snake_body[0].y < 1 || snake_body[0].y > move_size.y - 1) {
        snake_live = false;
        return false;
    }
    if (model) {
        for (int i = 1; i < snake_body.size(); i++) {
            if (snake_body[0].x == snake_body[i].x && snake_body[0].y == snake_body[i].y) {
                snake_live = false;
                return false;
            }
        }
    }
    return true;
}

void Snake::is_body(vector<Cor>& snake, int pmap[][100])
{
    // 看传的参数
    for (int i = 0; i < snake.size(); i++) {
        pmap[snake[i].x][snake[i].y] = SNAKE;
    }
}

bool Snake::can_move(Cor pos)
{
    //
    if (pos.x < 1 || pos.x > move_size.x - 1 || pos.y < 1 || pos.y > move_size.y - 1) {
        return false;
    }
    return true;
}

void Snake::map_reset(vector<Cor>& snake, int pmap[][100])
{
    // psnake pmap

    Cor f = food.get_food();
    for (int i = 1; i < move_size.x; i++) {
        for (int j = 1; j < move_size.y; j++) {
            /*
			if (i == f.x && j == f.y) {
                pmap[i][j] = FOOD;
            } else if (is_body(i, j, snake)) {
                pmap[i][j] = SNAKE;
            } else {
                pmap[i][j] = UNDEFINE;
            }
			*/

            pmap[i][j] = UNDEFINE;
        }
    }
    is_body(snake, pmap);

    pmap[f.x][f.y] = FOOD;
}

bool Snake::map_bfs(Cor pfood, vector<Cor>& snake, int pmap[][100])
{
    queue<Cor> q;
    Cor snake_head = snake[0];
    q.push(pfood);
    // 随尺寸变化
    bool vis[30][30] = { 0 };
    bool found = false;
    while (!q.empty()) {
        Cor front = q.front();
        q.pop();

        if (vis[front.x][front.y])
            continue;
        vis[front.x][front.y] = 1;
        for (int i = 0; i < 4; i++) {
            Cor temp(front.x + dir[i][0], front.y + dir[i][1]);
            if (can_move(temp)) {
                if (temp.x == snake_head.x && temp.y == snake_head.y)
                    found = true;
                if (pmap[temp.x][temp.y] < SNAKE) {
                    if (pmap[temp.x][temp.y] > pmap[front.x][front.y] + 1) {
                        pmap[temp.x][temp.y] = pmap[front.x][front.y] + 1;
                    }
                    if (!vis[temp.x][temp.y]) {
                        q.push(temp);
                    }
                }
            }
        }
    }
    return found;
}

int Snake::find_short_path(vector<Cor>& snake, int pmap[][100])
{
    int best_move = ERR;
    int min_step = SNAKE;
    Cor snake_head = snake[0];
    for (int i = 0; i < 4; i++) {
        Cor temp(snake_head.x + dir[i][0], snake_head.y + dir[i][1]);
        if (can_move(temp) && pmap[temp.x][temp.y] < min_step) {
            min_step = pmap[temp.x][temp.y];
            best_move = i;
        }
    }
    return best_move;
}

int Snake::find_long_path(vector<Cor>& snake, int pmap[][100])
{
    int best_move = ERR;
    int max_step = -1000;
    Cor snake_head = snake[0];
    for (int i = 0; i < 4; i++) {
        Cor temp(snake_head.x + dir[i][0], snake_head.y + dir[i][1]);
        if (can_move(temp) && pmap[temp.x][temp.y] < UNDEFINE && pmap[temp.x][temp.y] > max_step) {
            max_step = pmap[temp.x][temp.y];
            best_move = i;
        }
    }
    return best_move;
}

bool Snake::find_path_to_tail()
{

    // tmap
    Cor f = food.get_food();
    tmap[tempsnake.back().x][tempsnake.back().y] = FOOD;
    tmap[f.x][f.y] = SNAKE;
    bool result = map_bfs(tempsnake.back(), tempsnake, tmap);
    for (int i = 0; i < 4; i++) {
        Cor temp(tempsnake[0].x + dir[i][0], tempsnake[0].y + dir[i][1]);
        if (can_move(temp) && (temp.x == tempsnake.back().x && temp.y == tempsnake.back().y) && tempsnake.size() > 3) {
            result = false;
        }
    }
    return result;
}

int Snake::move_to_tail()
{

    // tmap
    tempsnake.assign(snake_body.begin(), snake_body.end());
    map_reset(tempsnake, tmap);
    tmap[tempsnake.back().x][tempsnake.back().y] = FOOD;
    tmap[food.get_food().x][food.get_food().y] = SNAKE;
    map_bfs(tempsnake.back(), tempsnake, tmap);
    tmap[tempsnake.back().x][tempsnake.back().y] = SNAKE;
    return find_long_path(tempsnake, tmap);
}

int Snake::go_any()
{
    int best_move = ERR;
    map_reset(snake_body, map);
    map_bfs(food.get_food(), snake_body, map);
    int min_step = SNAKE;
    Cor snake_head = snake_body[0];
    for (int i = 0; i < 4; i++) {
        Cor temp(snake_head.x + dir[i][0], snake_head.y + dir[i][1]);
        if (can_move(temp) && map[temp.x][temp.y] < min_step) {
            min_step = map[temp.x][temp.y];
            best_move = i;
        }
    }
    return best_move;
}

void Snake::ai_make_move(int move)
{
    Cor temphead = snake_body[0];
    temphead.x += dir[move][0];
    temphead.y += dir[move][1];
    snake_body.insert(snake_body.begin(), temphead);
    show_snake();
    if (temphead.x == food.get_food().x && temphead.y == food.get_food().y) {
        map[temphead.x][temphead.y] = SNAKE;
        score++;
        food.refresh_food(snake_body);
        food.show_food();
    } else {
        map[temphead.x][temphead.y] = SNAKE;
        map[snake_body.back().x][snake_body.back().y] = UNDEFINE;
        snake_erase();
        snake_body.pop_back();
    }
    head_dir = move + 1;
}

void Snake::man_listen_keyboard()
{
    char input;
    if (_kbhit()) {
        input = _getch();
        if (input == 'w' && head_dir != 4) {
            this->head_dir = 3;
        } else if (input == 's' && head_dir != 3) {
            this->head_dir = 4;
        } else if (input == 'a' && head_dir != 2) {
            this->head_dir = 1;
        } else if (input == 'd' && head_dir != 1) {
            this->head_dir = 2;
        } else if (input == '-') {
            man_speed += 50;
            if (man_speed > 1000)
                man_speed = 1000;
        } else if (input == '+') {
            man_speed -= 50;
            if (man_speed < 0)
                man_speed = 0;
        } else if (input == ' ') {
            model = !model;
        }
    }
    Cor head = snake_body[0];
    if (head_dir == 1) {
        head.x--;
    } else if (head_dir == 2) {
        head.x++;
    } else if (head_dir == 3) {
        head.y--;
    } else if (head_dir == 4) {
        head.y++;
    }
    snake_body.insert(snake_body.begin(), head);
}

void Snake::man_make_move()
{
    food.show_food();
    snake_erase();
    is_eat_food();
    man_listen_keyboard();
    show_snake();
}

void Snake::ai_listen_keboard()
{
    char input;
    if (_kbhit()) {
        input = _getch();
        if (input == '-') {
            ai_speed += 50;
            if (ai_speed > 1000)
                ai_speed = 1000;
        } else if (input == '+') {
            ai_speed -= 50;
            if (ai_speed < 0)
                ai_speed = 0;
        } else if (input == ' ') {
            model = !model;
        }
    }
}

void Snake::vertual_short_move()
{
    tempsnake.assign(snake_body.begin(), snake_body.end());
    memcpy(tmap, map, sizeof tmap);
    map_reset(tempsnake, tmap);

    bool eat_food = false;

    while (!eat_food) {
        map_bfs(food.get_food(), tempsnake, tmap);
        int move = find_short_path(tempsnake, tmap);
        
        Cor temphead = tempsnake[0];
        temphead.x += dir[move][0];
        temphead.y += dir[move][1];
        tempsnake.insert(tempsnake.begin(), temphead);

        if (tempsnake[0].x == food.get_food().x && tempsnake[0].y == food.get_food().y) {
            map_reset(tempsnake, tmap);
            tmap[food.get_food().x][food.get_food().y] = SNAKE;
            eat_food = true;
        } else {
            tmap[tempsnake[0].x][tempsnake[0].y] = SNAKE;
            tmap[tempsnake.back().x][tempsnake.back().y] = UNDEFINE;
        }
    }
}

int Snake::find_path()
{
    int best_move = ERR;
    vertual_short_move();
    if (find_path_to_tail() ) {
        return find_short_path(snake_body, map);
    } else {
        best_move = move_to_tail();
    }

    return best_move;
}

void Snake::ai_find_path()
{
    map_reset(snake_body, map);
    int best_move = ERR;
    if (map_bfs(food.get_food(), snake_body, map)) {
        best_move = find_path();
    } else {
        best_move = move_to_tail();
    }
    if (best_move == ERR) {
        best_move = go_any();
    }
    if (best_move != ERR) {
        ai_make_move(best_move);

    } else {
        
        snake_live = false;
        return;
    }
}