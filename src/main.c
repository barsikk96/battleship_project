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

    Cell player1_field[10][10];
    init_field(player1_field);

    Cell player2_field[10][10];
    init_field(player2_field);

    // Курсоры
    int cursor_y = 9, 
	cursor_x = 0;
    int on_field = PLAYER_FIELD;

    char* current_mode = "Установка кораблей";

    Ship* cruiser1   = malloc(sizeof(Ship));
    cruiser1->length = 4;
    cruiser1->hp     = 4;
    place_ship(player1_field,
	       cruiser1,
	       &player1_field[9][6],
	       HOR);

    Ship* cruiser2   = malloc(sizeof(Ship));
    cruiser2->length = 4;
    cruiser2->hp     = 4;
    place_ship(player2_field,
	       cruiser2,
	       &player2_field[9][6],
	       HOR);

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
		   player1_field, 
		   SHOW_SHIPS, 
		   cursor_y, 
		   cursor_x, 
		   on_field);
        
	draw_field(field_box_y + 1, 
		   field_box_x + FIELD_SIZE * CELL_WIDTH + 4, 
		   player2_field, 
		   HIDE_SHIPS, 
		   cursor_y, 
		   cursor_x, 
		   !on_field);

        // Кнопки
        draw_buttons(field_box_y + field_box_height + 1, 
		     current_mode);

        refresh();

        // Управление
        int ch = getch();
        handle_cases(ch,
		     &cursor_x,
		     &cursor_y,
		     &on_field); 
    }

    free(cruiser1);
    free(cruiser2);

    endwin();

    return 0;
}
