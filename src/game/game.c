#include "game.h"

void init_field(Cell field[FIELD_SIZE][FIELD_SIZE]) {
    for(unsigned char init_row = 0; init_row < 10; init_row++)
	for(unsigned char init_col = 0; 
			  init_col < 10; 
			  init_col++) {
	    field[init_row][init_col].row     = init_row;
	    field[init_row][init_col].col     = init_col;
	    field[init_row][init_col].checked = 0;
	    field[init_row][init_col].ship    = NULL;
	    field[init_row][init_col].status  = WATER;
	}
}

int place_ship(Cell  field[FIELD_SIZE][FIELD_SIZE],
	       Ship* ship, 
	       Cell* def_cell,
	       int   direction) {
    int flag_error = SUCCESS;
    
    switch(direction) {
	case VERT:
	    flag_error = filling_cells_vert(field, 
			    	 	    ship, 
					    def_cell);
	    log_err(flag_error);
	    break;
	case HOR:
	    flag_error = filling_cells_hor(field, 
			      		   ship, 
			      	 	   def_cell);
	    log_err(flag_error);
	    break;
	default:
	    break;
    }

    return flag_error;
}

int is_free_space(Cell  field[FIELD_SIZE][FIELD_SIZE],
		  Ship* def_ship,
		  Cell* def_cell,
		  int   direction) {
    int flag_error = SUCCESS;

    unsigned char count_len = def_ship->length;
    
    if(direction == VERT) {
    	if(count_len <= 
           def_cell->row + 1) {
	    for(int row = def_cell->row; 
		count_len > 0;
		row--) {
	        if(field[row][def_cell->col].ship)
	    	    flag_error = ERR_OCC_CELL;
	    	
		count_len--;
	    }
	} else
	    flag_error = ERR_NO_SPACE;
    }
    if(direction == HOR) {
	if(count_len <= 
       	   10 - def_cell->col) {
	    for(int col = def_cell->col; 
		count_len > 0;
		col++) {
	    	if(field[def_cell->row][col].ship)
	    	    flag_error = ERR_OCC_CELL;
		
		count_len--;
	    }
	} else
	    flag_error = ERR_NO_SPACE;
    }

    return flag_error;
}

int filling_cells_vert(Cell  field[FIELD_SIZE][FIELD_SIZE],
		       Ship* def_ship,
		       Cell* def_cell) {
    int flag_error = SUCCESS;

    
    unsigned char count_len = def_ship->length;
    
    flag_error = is_free_space(field,
		      	       def_ship,
		      	       def_cell,
		      	       VERT);
    for(int row = def_cell->row; 
	    count_len > 0 && !flag_error; 
            row--) {
	field[row][def_cell->col].ship   = def_ship;
	field[row][def_cell->col].status = SHIP; 
	count_len--;
    } 

    return flag_error;
}

int filling_cells_hor(Cell  field[FIELD_SIZE][FIELD_SIZE],
		      Ship* def_ship,
		      Cell* def_cell) {
    int flag_error = SUCCESS;

    unsigned char count_len = def_ship->length;
    
    flag_error = is_free_space(field,
		      	       def_ship,
		      	       def_cell,
		      	       HOR);
    for(int col = def_cell->col; 
	    count_len > 0 && !flag_error;
	    col++) {
	field[def_cell->row][col].ship   = def_ship;
	field[def_cell->row][col].status = SHIP;
	count_len--;
    } 

    return flag_error;
}

void log_err(int flag_error) {
    FILE* log_file = fopen("../log_file.txt", "a");
    
    
    time_t current_time = time(NULL);
    struct tm *time_info;
    char   time_str[100];
    time_info = localtime(&current_time);
    strftime(time_str, 
	     sizeof(time_str), 
	     "%Y-%m-%d %H:%M:%S", time_info);

    if(!log_file) {
	flag_error = ERR_ALLOCATION;
    	printf("Ошибка открытия файла! - %s\n", time_str);
    } else {
    	switch(flag_error) {
	    case ERR_ALLOCATION:
	    	fprintf(log_file, 
		        "Ошибка выделения памяти! - %s\n",  time_str);
	    	break;
	    case ERR_NO_SPACE:
	    	fprintf(log_file, 
		        "Выход за пределы массива! - %s\n", time_str);
	    	break;
	    case ERR_OCC_CELL:
	    	fprintf(log_file, 
		        "Клетка занята! - %s\n", 	    time_str);
	    	break;
	    default:
	    	break;
    	}
    }

    fclose(log_file);
}
