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

void draw_field(int  starty, 
		int  startx, 
		Cell field[FIELD_SIZE][FIELD_SIZE], 
		int  show_ships, 
		int  cursor_y, 
		int  cursor_x, 
		int  active) {
    for (int y = 0; y < FIELD_SIZE; y++) {
        for (int x = 0; x < FIELD_SIZE; x++) {
            char ch = '~'; // по умолчанию вода
            switch (field[y][x].status) {
                case WATER: ch = '~'; break;
                case SHIP:  ch = show_ships ? '#' : '~'; break;
                case HIT:   ch = '*'; break;
                case KILL:  ch = 'x'; break;
                case MISS:  ch = '^'; break;
            }

            if (cursor_y == y && cursor_x == x && active) {
                attron(A_REVERSE);
                mvprintw(starty + y, startx + x * CELL_WIDTH, "%c ", ch);
                attroff(A_REVERSE);
            } else {
                mvprintw(starty + y, startx + x * CELL_WIDTH, "%c ", ch);
            }
        }
    }
}

void draw_buttons( 	int   starty, 
	    	  const char* mode) {
    mvprintw(starty, 2, "[Режим: %s]", mode);
    mvprintw(starty + 1, 2, "Стрелки — перемещение");
    mvprintw(starty + 2, 2, "Enter — действие / установка");
    mvprintw(starty + 3, 2, "Ctrl+C — выход");
}
