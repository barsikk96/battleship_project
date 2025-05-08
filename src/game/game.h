#ifndef GAME_H
#define GAME_H

#include "../include/config.h"

typedef struct {
    unsigned char length;
    unsigned char hp;
} Ship;

typedef struct {
    Ship* 	  ship;
    unsigned char row;
    unsigned char col;
    unsigned char checked;
    	     char status;
} Cell;

typedef struct {
    Cell (*p1_field)[FIELD_SIZE];
    Cell (*p2_field)[FIELD_SIZE];
    char  game_mode;
    char  game_screen;
} Game;

void init_field(Cell field[FIELD_SIZE][FIELD_SIZE]);

void place_ship(Cell  field[FIELD_SIZE][FIELD_SIZE],
	        Ship* ship, 
	        Cell* def_cell,
	        int   direction);

int is_free_space(Cell  field[FIELD_SIZE][FIELD_SIZE],
		  Ship* def_ship,
		  Cell* def_cell,
		  int   direction);

int filling_cells_vert(Cell  field[FIELD_SIZE][FIELD_SIZE],
		       Ship* def_ship,
		       Cell* def_cell);

int filling_cells_hor(Cell  field[FIELD_SIZE][FIELD_SIZE],
		      Ship* def_ship,
		      Cell* def_cell);

void log_err(int flag_error);

#endif
