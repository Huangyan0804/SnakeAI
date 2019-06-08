#pragma once
#include <Windows.h>
#include<ctime>
#include "GameSetting.h"
#include <cstdio>

using namespace std;

void GameSetting::init()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info); //隐藏输入符号

	char buffer[32];
	sprintf_s(buffer, "mode con cols=%d lines=%d", window_width + 2, window_height + 1);
	system(buffer);
	::SetConsoleOutputCP(936);
	srand((unsigned int)time(0));

	// 修改字体获得更好体验
	CONSOLE_FONT_INFOEX font;
        font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
        font.nFont = 0;
        font.dwFontSize.X = 12;
        font.dwFontSize.Y = 16;
        font.FontWeight = 200;
        wchar_t str[] = L"Terminal";
        wcscpy_s(font.FaceName, str);
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetCurrentConsoleFontEx(handle, FALSE, &font);
}