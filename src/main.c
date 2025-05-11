#include "io.h"
#include "game.h"
#include "handler.h"

int main() {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    cbreak();
    start_color();
    
    init_pair(1, COLOR_BLUE, COLOR_BLACK);    // Вода
    init_pair(2, COLOR_GREEN, COLOR_BLACK);   // Корабль
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);  // Попадание
    init_pair(4, COLOR_RED, COLOR_BLACK);     // Уничтожен
    init_pair(5, COLOR_WHITE, COLOR_BLACK);   // Промах

    Game settings;
    init_game(&settings);

    Cursor cursor = { 0, 9, PLAYER_FIELD, VERT };

    while (settings.game_mode != GAME_OVER) {
	redraw_screen(&settings,
		      &cursor);

	int key = getch();
	key_handler(key,
	            &cursor,
	            &settings);
	
	stage_handler(&settings,
		      &cursor);
    }

    game_over(&settings);

    endwin();

    return 0;
}
