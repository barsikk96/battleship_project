#ifndef IO_F
#define IO_F

#include "../../include/config.h"
#include "../game/game.h"

void draw_border(int starty, 
		 int startx, 
		 int height, 
		 int width);

void draw_field(int  starty, 
		int  startx,  
		Cell field[FIELD_SIZE][FIELD_SIZE], 
		int  show_ships, 
		int  cursor_y, 
		int  cursor_x, 
		int  active);

void draw_buttons(	int   starty, 
		  const char* mode);

#endif
