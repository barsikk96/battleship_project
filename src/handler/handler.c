#include "handler.h"

KeyBinding bindings[] = {
    {PLACEMENT_MODE, KEY_UP,    mv_up_cursor},
    {PLACEMENT_MODE, KEY_DOWN,  mv_down_cursor},
    {PLACEMENT_MODE, KEY_LEFT,  mv_left_cursor},
    {PLACEMENT_MODE, KEY_RIGHT, mv_right_cursor},
    {PLACEMENT_MODE, '\t',      choose_ship_dir},
    {BATTLE_MODE,    KEY_UP,    mv_up_cursor},
    {BATTLE_MODE,    KEY_DOWN,  mv_down_cursor},
    {BATTLE_MODE,    KEY_LEFT,  mv_left_cursor},
    {BATTLE_MODE,    KEY_RIGHT, mv_right_cursor},
    {BATTLE_MODE,    '\t',      mv_field_cursor}
};

void handle_cases(int     key,
		  Cursor* cursor,
		  size_t  ship, 
		  Game*   settings) {
    char break_flag = 0;
    int  bindings_size = sizeof(bindings) / sizeof(bindings[0]); 
    
    if(key == KEY_ENTER || key == '\n') {
	enter_handler(settings,
		      ship,
		      cursor);
	break_flag = 1;
    }
    for(int h_case = 0;
	    h_case < bindings_size && !break_flag;
            h_case++)
	if(bindings[h_case].mode == settings->game_mode && 
	   bindings[h_case].key  == key) {
	    bindings[h_case].handler(cursor);
	    break_flag = 1;
	}
}

void enter_handler(Game*    settings,
		   size_t   num_ship, 
		   Cursor*  cursor) {
    Cell** field;
    Ship*  ship;
    if(settings->game_screen == PLAYER1_SCREEN) {
	field = settings->p1_field;
	ship  = settings->p1_ships[num_ship];
    } else {
	field = settings->p2_field;
	ship  = settings->p2_ships[num_ship];
    }

    switch(settings->game_mode) {
	case PLACEMENT_MODE:
	    if ((settings->game_screen == PLAYER1_SCREEN && 
         	num_ship >= settings->count_p1_ships) ||
        	(settings->game_screen == PLAYER2_SCREEN && 
         	num_ship >= settings->count_p2_ships)) {
	        int result = place_ship(field,
		       	   		ship,
		           		&field[cursor->y][cursor->x],
		           		cursor->direction);
		if (result == SUCCESS) {
    		    ship->is_placed = true;
    		    if (settings->game_screen == PLAYER1_SCREEN) {
        		settings->count_p1_ships++;
    		    } else {
        		settings->count_p2_ships++;
    		    }
		}
	    }
	    break;
	case BATTLE_MODE:
	    /*attack_ship(создать функцию атаки корабля);*/
	    break;
	default:
	    break;
    }
}
