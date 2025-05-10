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

void key_handler(int  	 key,
		 Cursor* cursor, 
		 Game*   settings);

void enter_handler(Game*   settings, 
		   Cursor* cursor);

void mode_handler(Game*   settings,
		  Cursor* cursor);

#endif
