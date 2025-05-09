#ifndef IO_F
#define IO_F

#include "../../include/config.h"
#include "../game/game.h"

typedef struct {
    int x;
    int y;
    int on_field;
    int direction;
} Cursor;

void draw_border(int starty, 
		 int startx, 
		 int height, 
		 int width);

void draw_field(int  	starty, 
		int  	startx,  
		Cell 	field[FIELD_SIZE][FIELD_SIZE], 
		int  	is_own_field, 	
		int     current_field,
		Cursor* cursor,
		Ship*   active_ship);

void draw_buttons(int  starty, 
		  char mode);

void mv_up_cursor(Cursor* cursor);

void mv_down_cursor(Cursor* cursor);

void mv_left_cursor(Cursor* cursor);

void mv_right_cursor(Cursor* cursor);

void mv_field_cursor(Cursor* cursor);

void choose_ship_dir(Cursor* cursor);

#endif
