#ifndef HANDLER_H
#define HANDLER_H

#include "../../include/config.h"
#include "../io/io.h"
#include "../game/game.h"

typedef void (*KeyHandler)(Cursor*);

typedef struct {
    char       mode;
    int        key;
    KeyHandler handler;
} KeyBinding;

extern KeyBinding bindings[];

void handle_cases(int  	  key,
		  Cursor* cursor,
		  Ship*   ship, //временное решение
		  Game*   settings);

void enter_handler(Game*   settings,
		   Ship*   ship, /*ship в составе структуры надо сделать*/
		   Cursor* cursor);

#endif
