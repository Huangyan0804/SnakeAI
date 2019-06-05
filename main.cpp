#include "Show.h"
#include "GameSetting.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <Windows.h>

using namespace std;

int main() {
    GameSetting setting;
    setting.init();
    Show show;
    show.show_map();
    show.show_last_score();
    while (true) {
        show.show_score();
        show.show_gameinfo();
        Sleep(game_speed);
    }
	return 0;
}