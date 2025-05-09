#include "io.h"

void draw_border(int starty, 
		 int startx, 
		 int height, 
		 int width) {
    mvaddch(starty, startx,             ACS_ULCORNER);
    mvhline(starty, startx + 1,         ACS_HLINE, width - 2);
    mvaddch(starty, startx + width - 1, ACS_URCORNER);

    mvvline(starty + 1, startx,             ACS_VLINE, height - 2);
    mvvline(starty + 1, startx + width - 1, ACS_VLINE, height - 2);

    mvaddch(starty + height - 1, startx,             ACS_LLCORNER);
    mvhline(starty + height - 1, startx + 1,         ACS_HLINE, width - 2);
    mvaddch(starty + height - 1, startx + width - 1, ACS_LRCORNER);
}

void draw_field(int  	starty, 
		int  	startx, 
		Cell 	field[FIELD_SIZE][FIELD_SIZE], 
		int  	is_own_field, 
		Cursor* cursor,
		int	current_field) {
    for (int y = 0; y < FIELD_SIZE; y++) {
        for (int x = 0; x < FIELD_SIZE; x++) {
            char ch = '~'; // по умолчанию вода
            switch (field[y][x].status) {
                case WATER: ch = '~'; break;
                case SHIP:  ch = is_own_field ? '#' : '~'; break;
                case HIT:   ch = '*'; break;
                case KILL:  ch = 'x'; break;
                case MISS:  ch = '^'; break;
            }

            if (cursor->y == y && 
		cursor->x == x && 
		cursor->on_field == current_field) {
                attron(A_REVERSE);
                mvprintw(starty + y, startx + x * CELL_WIDTH, "%c ", ch);
                attroff(A_REVERSE);
            } else {
                mvprintw(starty + y, startx + x * CELL_WIDTH, "%c ", ch);
            }
        }
    }
}

void draw_buttons(int  starty, 
	    	  char mode) {
    char* mode_name; 
    if(mode == PLACEMENT_MODE)
	mode_name = "Расстановка кораблей";
    if(mode == BATTLE_MODE)
	mode_name = "Сражение";

    mvprintw(starty, 2, "[Режим: %s]", mode_name);
    mvprintw(starty + 1, 2, "Стрелки — перемещение");
    mvprintw(starty + 2, 2, "Enter — действие / установка");
    mvprintw(starty + 3, 2, "Ctrl+C — выход");
}

void mv_up_cursor(Cursor* cursor) {
    if(cursor->y > 0)
	(cursor->y)--;
}

void mv_down_cursor(Cursor* cursor) {
    if(cursor->y < FIELD_SIZE - 1)
	(cursor->y)++;
}

void mv_left_cursor(Cursor* cursor) {
    if(cursor->x > 0)
	(cursor->x)--;
}

void mv_right_cursor(Cursor* cursor) {
    if(cursor->x < FIELD_SIZE - 1)
	(cursor->x)++;
}

void mv_field_cursor(Cursor* cursor) {
    cursor->on_field = (cursor->on_field == PLAYER_FIELD) 
	    				  ? 
	    		      ENEMY_FIELD : PLAYER_FIELD;
}

void choose_ship_dir(Cursor* cursor) {
    cursor->direction = (cursor->direction == VERT) 
	      				    ?
	    				HOR : VERT;
}
