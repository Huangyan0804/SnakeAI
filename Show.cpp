#include "Show.h"
#include "GameSetting.h"
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include<fstream>
using namespace std;
void Show::show_start()
{
    gotoxy(GameSetting::window_width / 2 - 10, GameSetting::window_height / 2 - 5);
    cout << "请选择游戏模式：" << endl;
    gotoxy(GameSetting::window_width / 2 - 10, GameSetting::window_height / 2 - 3);
    cout << "1. 手动操作模式" << endl;
    gotoxy(GameSetting::window_width / 2 - 10, GameSetting::window_height / 2 - 1);
    cout << "2. AI智能模式" << endl;
    gotoxy(GameSetting::window_width / 2 - 10, GameSetting::window_height / 2 + 1);
    cout << "请输入您的选择-> ";
}
void Show::show_map()
{
    gotoxy(0, 0);
    // 上边框
    for (int i = 0; i < GameSetting::window_width; i++) {
        if (i == 0)
            cout << "┏";
        else if (i == GameSetting::window_width - 1)
            cout << "┓";
        else if (i == GameSetting::window_width - 29)
            cout << "┳";
        else
            cout << "━";
    }
    // 左边框
    for (int i = 1; i < GameSetting::window_height - 1; i++) {
        gotoxy(0, i);
        cout << "┃";
    }

    // 中间分界线
    for (int i = 1; i < GameSetting::window_height - 1; i++) {
        gotoxy(GameSetting::window_width - 29, i);
        cout << "┃";
    }
    for (int i = GameSetting::window_width - 29; i < GameSetting::window_width; i++) {
        gotoxy(i, GameSetting::window_height -10);
        if (i == GameSetting::window_width - 29)
            cout << "┣";
        else
            cout << "━";
    }

    // 右边框
    for (int i = 1; i < GameSetting::window_height - 1; i++) {
        gotoxy(GameSetting::window_width - 1, i);
        cout << "┃";
    }

    // 下边框
    gotoxy(0, GameSetting::window_height - 1);
    for (int i = 0; i < GameSetting::window_width; i++) {
        if (i == 0)
            cout << "┗";
        else if (i == GameSetting::window_width - 1)
            cout << "┛";
        else if (i == GameSetting::window_width - 29)
            cout << "┻";
        else
            cout << "━";
    }
}
void Show::show_score()
{
    gotoxy(GameSetting::window_width - 22, 4);
    cout << "当前游戏速度: " << 100 - game_speed / 10 << endl;
    gotoxy(GameSetting::window_width - 22, 6);
    cout << "当前玩家分数: " << score << endl;
}

void Show::show_last_score()
{
    gotoxy(GameSetting::window_width - 22, 10);
    cout << "历史分数排行榜: " << endl;
    int k = 1;
    int last_score[11] = { 0 };
    ifstream fin("last-score.txt");
    for (int i = 0; i < 5; i++) {
        fin >> last_score[i];
	}
    fin.close();
    for (int i = 12; i < 12 + 2 * 8; i += 2, k++) {
        gotoxy(GameSetting::window_width - 20, i);
        cout << k << ": " << last_score[k]<< endl;
    }
    
}

void Show::show_gameinfo()
{
    gotoxy(GameSetting::window_width - 22, 32);
    cout << "游戏操作说明：" << endl;
    gotoxy(GameSetting::window_width - 22, 34);
    cout << "W: 上    S: 下" << endl;
    gotoxy(GameSetting::window_width - 22, 36);
    cout << "A: 左    D: 右" << endl;
}

void Show::gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}