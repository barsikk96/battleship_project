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

void draw_border(int   starty, 
		 int   startx, 
		 int   height, 
		 int   width,
	   const char* label);

void draw_field(int 	starty, 
                int 	startx, 
                int 	is_own_field,     
                int     current_field,
                Cell**  field,
                Cursor* cursor,
                Ship*   active_ship);

void draw_buttons(int  starty, 
		  char mode);

void draw_transition_screen(Game* settings);

void draw_winner_screen(const char* winner_name);

void mv_up_cursor(Cursor* cursor);

void mv_down_cursor(Cursor* cursor);

void mv_left_cursor(Cursor* cursor);

void mv_right_cursor(Cursor* cursor);

void choose_ship_dir(Cursor* cursor);

void render_ui(int     starty, 
	       int     startx, 
	       int     height, 
	       int     width,
	       Game*   settings,
	       Cursor* cursor);

#endif
