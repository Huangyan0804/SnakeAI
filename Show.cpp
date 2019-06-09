#pragma once
#include "Show.h"
#include "Food.h"
#include "GameSetting.h"
#include "Snake.h"
#include <Windows.h>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

extern int score;
void Show::show_start(Snake& snake)
{
    gotoxy(0, 5);
    printf("  ########################################\n");
    printf("  #                                      #\n");
    printf("  #         欢迎来到贪吃蛇游戏           #\n");
    printf("  #                                      #\n");
    printf("  #           请选择游戏模式：           #\n");
    printf("  #                                      #\n");
    printf("  #           1. 手动操作模式            #\n");
    printf("  #                                      #\n");
    printf("  #           2. AI智能模式              #\n");
    printf("  #                                      #\n");
    printf("  ########################################\n");

    while (true) {
        gotoxy(12, 17);

        char input = _getch();
        if (input == '1') {
            snake.model = true;
            break;
        } else if (input == '2') {
            snake.model = false;
            break;
        } else {
            cout << "输入错误，请重新输入" << endl;
        }
    }
    system("cls");
    gotoxy(0, 5);
    printf("  ########################################\n");
    printf("  #                                      #\n");
    printf("  #        键盘 W A S D 控制方向         #\n");
    printf("  #                                      #\n");
    printf("  #         + / - 控制游戏速度           #\n");
    printf("  #                                      #\n");
    printf("  #         空格切换AI/手动模式          #\n");
    printf("  #                                      #\n");
    printf("  #          按任意键开始游戏            #\n");
    printf("  #                                      #\n");
    printf("  ########################################\n");
    _getch();
    system("cls");
}
void Show::show_map()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 119); // 设置白色
    // 上边框
    for (int i = 0; i < GameSetting::window_width; i++) {

        cout << "#";
    }
    // 左边框
    for (int i = 1; i < GameSetting::window_height - 1; i++) {
        gotoxy(0, i);
        cout << "#";
    }

    // 中间分界线
    for (int i = 1; i < GameSetting::window_height - 1; i++) {
        gotoxy(GameSetting::window_width - 21, i);
        cout << "#";
    }
    for (int i = GameSetting::window_width - 21; i < GameSetting::window_width; i++) {
        gotoxy(i, GameSetting::window_height - 9);

        cout << "#";
    }

    // 右边框
    for (int i = 1; i < GameSetting::window_height - 1; i++) {
        gotoxy(GameSetting::window_width - 1, i);
        cout << "#";
    }

    // 下边框
    gotoxy(0, GameSetting::window_height - 1);
    for (int i = 0; i < GameSetting::window_width; i++) {
        cout << "#";
    }
    SetConsoleTextAttribute(handle, 7);
}
void Show::show_score(Snake& s)
{

    gotoxy(GameSetting::window_width - 19, 2);
    cout << "当前游戏速度: " << setfill('0') << setw(3) << 100 - (s.get_speed() / 10) << endl;
    gotoxy(GameSetting::window_width - 19, 4);
    cout << "当前玩家分数: " << score << endl;
}

int last_score[10] = { 0 };
void Show::show_last_score()
{
    gotoxy(GameSetting::window_width - 18, 6);
    cout << "历史分数排行榜: " << endl;
    int num = 3;
    int k = 1;
    ifstream fin("last-score.txt");
    for (int i = 0; i < num; i++) {
        fin >> last_score[i];
    }
    fin.close();
    for (int i = 8; i < 8 + 2 * num; i += 2, k++) {
        gotoxy(GameSetting::window_width - 14, i);
        cout << k << ": " << last_score[k - 1] << endl;
    }
}

void Show::show_gameinfo()
{
    gotoxy(GameSetting::window_width - 17, GameSetting::window_height - 7);
    cout << "游戏操作说明：" << endl;
    gotoxy(GameSetting::window_width - 20, GameSetting::window_height - 5);
    cout << "W 上 S 下 A 左 D 右" << endl;
    gotoxy(GameSetting::window_width - 20, GameSetting::window_height - 4);
    cout << "  +  加速 -  减速" << endl;
    gotoxy(GameSetting::window_width - 20, GameSetting::window_height - 3);
    cout << "   空格 切换模式" << endl;
}

bool Show::show_game_over()
{
    system("cls");
    //HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(handle, 119);
    last_score[3] = score;
    sort(last_score, last_score + 4, greater<int>());
    ofstream fout("last-score.txt");
    if (fout) {
        for (int i = 0; i < 3; i++) {
            fout << last_score[i] << endl;
        }
    }
    fout.close();

    gotoxy(0, 7);
    printf("  ########################################\n");
    printf("  #                                      #\n");
    printf("  #             本次游戏结束             #\n");
    printf("  #                                      #\n");
    printf("  #           本次得分：%03d 分           #\n", score);
    printf("  #                                      #\n");
    printf("  #           按回车键结束游戏           #\n");
    printf("  #                                      #\n");
    printf("  ########################################\n");

    char input = '1';
    while (input != 13) {
        input = _getch();
    }
    return true;
    //SetConsoleTextAttribute(handle, 7);
}
