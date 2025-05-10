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

    // Позиции и размеры
    int field_box_y = 1, 
	field_box_x = 2;
    int field_box_height = FIELD_SIZE + 2;
    int field_box_width  = FIELD_SIZE * CELL_WIDTH * 2 + 6; 

    Game settings;
    init_game(&settings);

    Cursor cursor = { 0, 9, PLAYER_FIELD, VERT };

    while (settings.game_mode != GAME_OVER) {
	clear();
	
	render_ui(field_box_y,
	          field_box_x,
	          field_box_height,
	          field_box_width,
	          &settings,
	          &cursor);

	refresh();

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
