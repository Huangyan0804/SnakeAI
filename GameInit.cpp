#include "GameInit.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;
void GameInit::init()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info); //Òþ²ØÊäÈë·ûºÅ

    char buffer[32];
    sprintf_s(buffer, "mode con cols=%d lines=%d", window_width, window_height);
    system(buffer);

	srand((unsigned int)time(0));
}