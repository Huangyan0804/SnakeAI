#pragma once
#include <Windows.h>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct Point {
    int x, y;
    Point(int a = 0, int b = 0)
    {
        x = a, y = b;
    }
};
class AI {
public:
    bool find_path_to_food(Point start, Point food);
    bool find_path_to_tail(Point start, Point tail);
    Point find_short_path(vector<Point> &tempsnake, int **map);
    Point find_long_path(vector<Point>& tempsnake, int** map);
    void temp_snake_move();
    void go_any();
};