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

    int screen_height, 
	screen_width;
    getmaxyx(stdscr, screen_height, screen_width);

    // Позиции и размеры
    int field_box_y = 1, 
	field_box_x = 2;
    int field_box_height = FIELD_SIZE + 2;
    int field_box_width  = FIELD_SIZE * CELL_WIDTH * 2 + 6; // 2 поля + пробел

    Cell player1_field[FIELD_SIZE][FIELD_SIZE];
    init_field(player1_field);

    Cell player2_field[FIELD_SIZE][FIELD_SIZE];
    init_field(player2_field);

    Game settings = { player1_field,
    		      player2_field,
    		      PLACEMENT_MODE,
    		      PLAYER1_SCREEN };

    Cursor cursor = { 0, 9, PLAYER_FIELD, VERT };

    Ship* cruiser1   = malloc(sizeof(Ship));
    cruiser1->length = 4;
    cruiser1->hp     = 4;

    Ship* cruiser2   = malloc(sizeof(Ship));
    cruiser2->length = 4;
    cruiser2->hp     = 4;

    while (1) {
        clear();

        // Нарисовать рамку
        draw_border(field_box_y, 
		    field_box_x, 
		    field_box_height, 
		    field_box_width);

        // Нарисовать поля
        draw_field(field_box_y + 1, 
		   field_box_x + 2, 
		   settings.p1_field, 
		   SHOW_SHIPS, 
		   &cursor);
        
	draw_field(field_box_y + 1, 
		   field_box_x + FIELD_SIZE * CELL_WIDTH + 4, 
		   settings.p2_field, 
		   HIDE_SHIPS, 
		   &cursor);

        // Кнопки
        draw_buttons(field_box_y + field_box_height + 1, 
		     settings.game_mode);

        refresh();

        // Управление
        int key = getch();
        handle_cases(key,
		     &cursor,
		     cruiser1,
		     &settings); 
    }

    free(cruiser1);
    free(cruiser2);

    endwin();

    return 0;
}
