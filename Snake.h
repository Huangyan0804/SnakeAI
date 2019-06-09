#pragma once
#include "Food.h"
#include "GameSetting.h"
#include <vector>

using namespace std;

class Snake :public Food{
private:
    int head_dir;
    bool snake_live;
    Cor move_size;
    
    int ai_speed, man_speed;
	

public:
    bool model;
    Food food;
    bool get_model();
    bool get_snake_live();
    int get_speed();
    int map[100][100], tmap[100][100]; // 估价
    vector<Cor> snake_body;
    vector<Cor> tempsnake;
    Snake();
    void show_snake();
    void man_listen_keyboard();
    bool is_eat_food();
    void snake_erase();
    bool is_alive();
    void is_body(vector<Cor>& snake, int pmap[][100]);
    bool can_move(Cor pos);
    void map_reset( vector<Cor>& snake, int pmap[][100]);
    bool map_bfs(Cor food, vector<Cor>& snake, int pmap[][100]);
    int find_short_path(vector<Cor>& snake, int pmap[][100]);
    int find_long_path(vector<Cor>& snake, int pmap[][100]);
    bool find_path_to_tail();
    int move_to_tail();
    int go_any();
    void vertual_short_move();
    int find_path();
    void ai_find_path();
    void ai_make_move(int move);
    void ai_listen_keboard();
    void man_make_move();
};
