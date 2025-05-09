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
		int	current_field,
		Cursor* cursor,
		Ship*   active_ship) {
    for (int y = 0; y < FIELD_SIZE; y++) {
        for (int x = 0; x < FIELD_SIZE; x++) {
	    int screen_y = starty + y;
            int screen_x = startx + x * 2;
            char ch = '~'; // по умолчанию вода
            switch (field[y][x].status) {
                case WATER: ch = '~'; break;
                case SHIP:  ch = is_own_field ? '#' : '~'; break;
                case HIT:   ch = '*'; break;
                case KILL:  ch = 'x'; break;
                case MISS:  ch = '^'; break;
            }

            // Проверка: наводится ли курсор на это поле
            int is_cursor_here = (cursor->x == x && cursor->y == y && cursor->on_field == current_field);

            // Проверка: входит ли эта ячейка в зону предпросмотра корабля
            int draw_preview = 0;
            if (is_own_field && cursor->on_field == current_field && active_ship != NULL) {
                for (int i = 0; i < active_ship->length; i++) {
                    int px = cursor->x;
                    int py = cursor->y;

                    if (cursor->direction == VERT)
                        py -= i;
                    else
                        px += i;

                    if (px == x && py == y &&
                        px >= 0 && px < FIELD_SIZE &&
                        py >= 0 && py < FIELD_SIZE) {
                        draw_preview = 1;
                        break;
                    }
                }
            }

            // Отрисовка
            if (is_cursor_here) {
                attron(A_REVERSE);
                mvprintw(screen_y, screen_x, "%c", draw_preview ? '#' : ch);
                attroff(A_REVERSE);
            } else {
                mvprintw(screen_y, screen_x, "%c", draw_preview ? '#' : ch);
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
