#ifndef GAME_H
#define GAME_H

#include "../include/config.h"

typedef struct {
    unsigned char length;
    unsigned char hp;
    bool 	  is_placed;
} Ship;

typedef struct {
    Ship* 	  ship;
    unsigned char row;
    unsigned char col;
    	     char status;
} Cell;

typedef struct {
    Cell**        p1_field;
    Cell**	  p2_field;
    Ship** 		p1_ships;
    unsigned char count_p1_ships;
    Ship** 		p2_ships;
    unsigned char count_p2_ships;
    char   	  game_mode;
    char  	  game_screen;
} Game;

void init_field(Cell** field);

Ship* create_ship(int type_ship);

void init_game(Game* settings);

void game_over(Game* settings);

int place_ship(Cell** field,
	        Ship*  ship, 
	        Cell*  def_cell,
	        int    direction);

int is_free_space(Cell** field,
		  Ship*  def_ship,
		  Cell*  def_cell,
		  int    direction);

int filling_cells_vert(Cell** field,
		       Ship*  def_ship,
		       Cell*  def_cell);

int filling_cells_hor(Cell** field,
		      Ship*  def_ship,
		      Cell*  def_cell);

void log_err(int flag_error);

#endif
