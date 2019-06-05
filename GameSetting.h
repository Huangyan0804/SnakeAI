#pragma once
struct Cor {
	int x, y;
	Cor(int a = 0, int b = 0) {
		x = a, y = b;
	}
};

class GameSetting {
public:
	static const int window_width = 80;
	static const int window_height = 40;
	
	void init(); // 初始化
};