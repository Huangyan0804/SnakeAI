#pragma once


using namespace std;

struct Cor {
    int x, y;
    Cor(int a = 0, int b = 0)
    {
        x = a, y = b;
    }
};


class GameSetting {
	
public:
	// 像素宽高比 12:16
	static const int window_width = 42; // 想要的范围 + 22
	static const int window_height = 22; // 想要的范围 + 2
	// 默认范围： 20  20
	// 注意修改后屏幕信息会偏移，需要自己调整
	// bfs，食物刷新，移动范围，显示信息
	
	void init(); // 初始化
};