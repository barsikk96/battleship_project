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

void init_field(Cell field[10][10]);

int place_ship(Cell  field[10][10],
	       Ship* ship, 
	       Cell* def_cell,
	       int   direction);

int is_free_space(Cell  field[10][10],
		  Ship* def_ship,
		  Cell* def_cell,
		  int   direction);

int filling_cells_vert(Cell  field[10][10],
		       Ship* def_ship,
		       Cell* def_cell);

int filling_cells_hor(Cell  field[10][10],
		      Ship* def_ship,
		      Cell* def_cell);

void log_err(int flag_error);

#endif
