#include "game.h"

void init_field(Cell** field) {
    for(unsigned char init_row = 0; init_row < 10; init_row++)
	for(unsigned char init_col = 0; 
			  init_col < 10; 
			  init_col++) {
	    field[init_row][init_col].row     = init_row;
	    field[init_row][init_col].col     = init_col;
	    field[init_row][init_col].ship    = NULL;
	    field[init_row][init_col].status  = WATER;
	}
}

Ship* create_ship(int type_ship) {
    int flag_error = SUCCESS;

    Ship* ship = malloc(sizeof(Ship));
    if(!ship) {
	flag_error = ERR_ALLOCATION;
	log_err(flag_error);
    }

    if(!flag_error) {
	switch(type_ship) {
	    case BATTLESHIP:
		ship->length = 4;
		ship->hp     = 4;
		break;
	    case CRUISER:
		ship->length = 3;
		ship->hp     = 3;
		break;
	    case DESTROYER:
		ship->length = 2;
		ship->hp     = 2;
		break;
	    case BOAT:
		ship->length = 1;
		ship->hp     = 1;
		break;
	}
    }

    return ship;
}

void init_game(Game* settings) {
    settings->p1_field = malloc(FIELD_SIZE * sizeof(Cell*));
    for (int i = 0; i < FIELD_SIZE; i++)
    	settings->p1_field[i] = malloc(FIELD_SIZE * sizeof(Cell));
    init_field(settings->p1_field);

    settings->p2_field = malloc(FIELD_SIZE * sizeof(Cell*));
    for (int i = 0; i < FIELD_SIZE; i++)
    	settings->p2_field[i] = malloc(FIELD_SIZE * sizeof(Cell));
    init_field(settings->p2_field);

    settings->count_p1_ships  = 0;  
    settings->p1_ships = malloc(COUNT_SHIPS * sizeof(Ship*));
    
    settings->count_p2_ships  = 0;
    settings->p2_ships = malloc(COUNT_SHIPS * sizeof(Ship*));

    int ship_types[] = { BATTLESHIP, 
	    		 CRUISER, CRUISER, 
			 DESTROYER, DESTROYER, DESTROYER, 
			 BOAT, BOAT, BOAT, BOAT };
    for (int ship = 0; ship < COUNT_SHIPS; ship++) {
    	settings->p1_ships[ship] = create_ship(ship_types[ship]);
    	settings->p2_ships[ship] = create_ship(ship_types[ship]);
    	settings->p1_ships[ship]->is_placed = false;
    	settings->p2_ships[ship]->is_placed = false;
    }

    settings->active_ship = 0;
    settings->game_mode   = PLACEMENT_MODE;
    settings->game_screen = PLAYER1_SCREEN;
}

void game_over(Game* settings) {
    if(settings->p1_field) {
	free(settings->p1_field);
	settings->p1_field = NULL;
    }
    if(settings->p2_field) {
        free(settings->p2_field);
        settings->p2_field = NULL;
    }

    // Освобождаем корабли игрока 1
    if (settings->p1_ships) {
        for (unsigned char i = 0; i < settings->count_p1_ships; i++) {
            if (settings->p1_ships[i]) {
                free(settings->p1_ships[i]);
		settings->p1_ships[i] = NULL;
            }
        }
        free(settings->p1_ships); 
        settings->p1_ships = NULL;
    }

    // Освобождаем корабли игрока 2 
    if (settings->p2_ships) {
        for (unsigned char i = 0; i < settings->count_p2_ships; i++) {
            if (settings->p2_ships[i]) {
                free(settings->p2_ships[i]);  
                settings->p2_ships[i] = NULL;
            }
        }
        free(settings->p2_ships);  
        settings->p2_ships = NULL;
    }

    settings->count_p1_ships = 0;
    settings->count_p2_ships = 0;
}

void attack_ship(Game* settings,
		 Cell* def_cell) {
    if(def_cell->status == WATER)
	def_cell->status = MISS;
    
    if(def_cell->status == SHIP) {
	def_cell->ship->hp--;
	if(def_cell->ship->hp == 0)
	    kill_ship(settings,
		      def_cell->ship);
	else
	    def_cell->status = HIT;
    }
}

void kill_ship(Game* settings,
	       Ship* ship) {
    for(size_t cell = 0; 
	       cell < ship->length;
	       cell++) {
	ship->address[cell]->status = KILL;
    }

    if(settings->game_screen == PLAYER1_SCREEN)
	settings->count_p1_ships--;
    else
	settings->count_p2_ships--;
}

int place_ship(Cell** field,
	       Ship*  ship, 
	       Cell*  def_cell,
	       int    direction) {
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

int is_free_space(Cell** field,
		  Ship*  def_ship,
		  Cell*  def_cell,
		  int    direction) {
    int flag_error = SUCCESS;

    unsigned char count_len = def_ship->length;
    
    if(direction == VERT) {
    	if(count_len <= 
           def_cell->row + 1) {
	    for(int row = def_cell->row; 
		count_len > 0 && !flag_error;
		row--) {
	        if(field[row][def_cell->col].ship)
	    	    flag_error = ERR_OCC_CELL;
		else
		    count_len--;
	    }
	} else
	    flag_error = ERR_NO_SPACE;
    }
    if(direction == HOR) {
	if(count_len <= 
       	   10 - def_cell->col) {
	    for(int col = def_cell->col; 
		count_len > 0 && !flag_error;
		col++) {
	    	if(field[def_cell->row][col].ship)
	    	    flag_error = ERR_OCC_CELL;
	        else	
		    count_len--;
	    }
	} else
	    flag_error = ERR_NO_SPACE;
    }

    return flag_error;
}

int filling_cells_vert(Cell** field,
		       Ship*  def_ship,
		       Cell*  def_cell) {
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
	def_ship->address[count_len - 1] = &field[row][def_cell->col];
	count_len--;
    } 

    return flag_error;
}

int filling_cells_hor(Cell** field,
		      Ship*  def_ship,
		      Cell*  def_cell) {
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
	def_ship->address[count_len - 1] = &field[def_cell->row][col];
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
