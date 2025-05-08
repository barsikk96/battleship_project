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
		  Ship*   ship, // временное решение
		  Game*   settings) {
    char break_flag = 0;
    int  bindings_size = sizeof(bindings) / sizeof(bindings[0]); 
    for(int h_case = 0;
	    h_case < bindings_size && !break_flag;
            h_case++)
	if(bindings[h_case].key == key) {
	    bindings[h_case].handler(cursor);
	    break_flag = 1;
	} else {
	    if(key == KEY_ENTER)
		enter_handler(settings,
			      ship, /*ship надо передать в составе структуры*/
			      cursor);
	}
}

void enter_handler(Game*   settings,
		   Ship*   ship, /*ship в составе структуры надо сделать*/
		   Cursor* cursor) {
    Cell (*field)[FIELD_SIZE];
    if(settings->game_screen == PLAYER1_SCREEN)
	field = settings->p1_field;
    else
	field = settings->p2_field;

    switch(settings->game_mode) {
	case PLACEMENT_MODE:
	    place_ship(field,
		       ship/*ship*/,
		       &field[cursor->x][cursor->y],
		       cursor->direction);
	    break;
	case BATTLE_MODE:
	    /*attack_ship(создать функцию атаки корабля);*/
	    break;
	default:
	    break;
    }
}
