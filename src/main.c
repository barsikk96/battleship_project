#include <stdio.h>
#include <stdlib.h>

#define UP 1
#define SUCCESS 0
#define ERR_USED 1

typedef struct {
    unsigned char length;
    unsigned char hp;
} Ship;

typedef struct {
    Ship* 	  ship;
    unsigned char row;
    unsigned char col;
    unsigned char checked;
} Cell;

int init_field(Cell  field[10][10]);
int place_ship(Cell  field[10][10],
	       Ship* ship, 
	       Cell* def_cell,
	       int   direction);
int filling_cells_up(Cell  field[10][10],
		     Ship* def_ship,
		     Cell* def_cell);

int main() {
    Cell field[10][10];
    init_field(field);

    Ship* cruiser   = malloc(sizeof(Ship));
    cruiser->length = 4;
    cruiser->hp     = 4;
    place_ship(field,
	       cruiser,
	       &field[9][0],
	       UP);
    for(int i = 0; i < 10; i++) {
	for(int j = 0; j < 10; j++) {
	    if(field[i][j].ship != NULL)
		printf("X:%u \nY:%u - ship\n", field[i][j].row,
		    	  	               field[i][j].col);
	}
    }
    free(cruiser);

    return 0;
}

int init_field(Cell field[10][10]) {
    int flag_error = SUCCESS;

    for(unsigned char init_row = 0; init_row < 10; init_row++) {
	for(unsigned char init_col = 0; init_col < 10; init_col++) {
	    field[init_row][init_col].row     = init_row;
	    field[init_row][init_col].col     = init_col;
	    field[init_row][init_col].checked = 0;
	    field[init_row][init_col].ship    = NULL;
	}
    }

    return flag_error;
}

int place_ship(Cell  field[10][10],
	       Ship* ship, 
	       Cell* def_cell,
	       int   direction) {
    int flag_error = SUCCESS;
    
    if(def_cell->ship)
	flag_error = ERR_USED;
    else {
	switch(direction) {
	    case UP:
		filling_cells_up(field, ship, def_cell);
		break;
	    default:
		break;
	}
    }
}

int filling_cells_up(Cell  field[10][10],
		     Ship* def_ship,
		     Cell* def_cell) {
    int flag_error = SUCCESS;

    unsigned char count_len = def_ship->length;
    for(int row  = def_cell->row;
	    row >= 0 && count_len > 0;
	    row--) {
	field[row][def_cell->col].ship = def_ship;
    	count_len--;
    }

    return flag_error;
}
