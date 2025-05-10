#include "io.h"

void draw_border(int   starty, 
		 int   startx, 
		 int   height, 
		 int   width,
	   const char* label) {
    mvaddch(starty, startx,             ACS_ULCORNER);
    mvhline(starty, startx + 1,         ACS_HLINE, width - 2);
    mvaddch(starty, startx + width - 1, ACS_URCORNER);

    mvvline(starty + 1, startx,             ACS_VLINE, height - 2);
    mvvline(starty + 1, startx + width - 1, ACS_VLINE, height - 2);

    mvaddch(starty + height - 1, startx,             ACS_LLCORNER);
    mvhline(starty + height - 1, startx + 1,         ACS_HLINE, width - 2);
    mvaddch(starty + height - 1, startx + width - 1, ACS_LRCORNER);

    if (label != NULL) {
        int label_length = strlen(label);
        int label_x = startx + (width - label_length) / 2;
        mvprintw(starty - 1, label_x, "%s", label);
    }
}

void draw_field(int 	starty, 
                int 	startx, 
                int 	is_own_field,     
                int 	current_field,
                Cell** 	field,
                Cursor* cursor,
                Ship* 	active_ship) {     
    for (int y = 0; y < FIELD_SIZE; y++) {
        for (int x = 0; x < FIELD_SIZE; x++) {
            int screen_y = starty + y;
            int screen_x = startx + x * 2;
            char ch = '~';
            switch (field[y][x].status) {
                case WATER: ch = '~'; break;
                case SHIP:  ch = is_own_field ? '#' : '~'; break;
                case HIT:   ch = '*'; break;
                case KILL:  ch = 'x'; break;
                case MISS:  ch = '^'; break;
            }

            int is_cursor_here = (cursor->x == x && 
                                  cursor->y == y && 
                                  cursor->on_field == current_field);

            int draw_preview = 0;
            if (is_own_field && 
                cursor->on_field == current_field && 
                active_ship != NULL && 
		!active_ship->is_placed) {
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

void draw_transition_screen(Game* settings) {
    int width = 40;
    int height = 5;
    int screen_width, screen_height;
    getmaxyx(stdscr, screen_height, screen_width); 

    int center_y = screen_height / 2 - height / 2;
    int center_x = screen_width / 2 - width / 2;

    for (int y = center_y; y < center_y + height; y++) {
        move(y, center_x);
        clrtoeol(); 
    }

    draw_border(center_y, center_x, height, width, "Смена хода");

    char* player_name = (settings->game_screen == PLAYER1_SCREEN) 
                      ? "Игрок 1" 
                      : "Игрок 2";

    mvprintw(center_y + height / 2, 
             center_x + (width - strlen(player_name) - 8) / 2,
             "%s, ваш ход!", player_name);

    mvprintw(center_y + height - 1, 
             center_x + (width - 27) / 2,
             "Нажмите Enter для продолжения");

    refresh(); 
}

void draw_winner_screen(const char* winner_name) {
    int width = 40;  
    int height = 5;  
    int screen_width, screen_height;
    
    getmaxyx(stdscr, screen_height, screen_width);
    
    int center_y = screen_height / 2 - height / 2;
    int center_x = screen_width / 2 - width / 2;
    
    for (int y = center_y; y < center_y + height; y++) {
        move(y, center_x);
        clrtoeol();
    }
    
    draw_border(center_y, center_x, height, width, "Игра окончена");
    
    mvprintw(center_y + height / 2, 
             center_x + (width - strlen(winner_name) - 12) / 2,
             "Победитель: %s!", winner_name);
    
    mvprintw(center_y + height - 1, 
             center_x + (width - 27) / 2,
             "Нажмите Enter для выхода");
    
    refresh();
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

void choose_ship_dir(Cursor* cursor) {
    cursor->direction = (cursor->direction == VERT) 
	      				    ?
	    				HOR : VERT;
}

void render_ui(int     starty, 
	       int     startx, 
	       int     height, 
	       int     width,
	       Game*   settings,
	       Cursor* cursor) {
        

	// Поля для первого игрока
        if(settings->game_screen == PLAYER1_SCREEN) {
            // Нарисовать рамку
            draw_border(starty, 
		    	startx, 
		    	height, 
		    	width,
			"Игрок 1");

	    draw_field(starty + 1, 
            	       startx + 2,  
		       SHOW_SHIPS,  
		       PLAYER_FIELD,
		       settings->p1_field,
		       cursor,
		       settings->p1_ships[settings->active_ship]);
                
            draw_field(starty + 1, 
            	       startx + FIELD_SIZE * CELL_WIDTH + 4, 
		       HIDE_SHIPS, 
		       ENEMY_FIELD,
		       settings->p2_field,	
		       cursor,
		       settings->p2_ships[settings->active_ship]);
	}

	// Поля для второго игрока
        if(settings->game_screen == PLAYER2_SCREEN) {
            // Нарисовать рамку
            draw_border(starty, 
		    	startx, 
		    	height, 
		    	width,
			"Игрок 2");

	    draw_field(starty + 1, 
            	       startx + 2, 
		       SHOW_SHIPS, 
            	       PLAYER_FIELD, 
            	       settings->p2_field,
		       cursor,
		       settings->p2_ships[settings->active_ship]); 
                
            draw_field(starty + 1, 
            	       startx + FIELD_SIZE * CELL_WIDTH + 4, 
		       HIDE_SHIPS, 
		       ENEMY_FIELD,
            	       settings->p1_field, 
		       cursor,
		       settings->p1_ships[settings->active_ship]);
	}
	

        // Кнопки
        draw_buttons(starty + height + 1, 
		     settings->game_mode);
}
