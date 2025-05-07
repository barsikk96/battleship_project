#include "handler.h"

void handle_cases(int  ch,
		  int* cursor_x,
		  int* cursor_y,
		  int* on_field) {
    switch (ch) {
            case KEY_UP:
                if(*cursor_y > 0) 
		    (*cursor_y)--;
                break;
            case KEY_DOWN:
                if(*cursor_y < FIELD_SIZE - 1) 
		    (*cursor_y)++;
                break;
            case KEY_LEFT:
                if(*cursor_x > 0) 
		    (*cursor_x)--;
                break;
            case KEY_RIGHT:
                if(*cursor_x < FIELD_SIZE - 1) 
		    (*cursor_x)++;
                break;
            case '\t':
                if(*on_field)
		    (*on_field) = ENEMY_FIELD;
		else
		    (*on_field) = PLAYER_FIELD;
                break;
            case '\n':
            case KEY_ENTER:
                // Здесь может быть вызов действия, установки корабля, выстрела
                break;
        }
}
