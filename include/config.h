#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncursesw/curses.h>
#include <locale.h>

#define FIELD_SIZE 10
#define CELL_WIDTH 2
#define COUNT_SHIPS 10

#define PLAYER_FIELD 1
#define ENEMY_FIELD 0

#define SHOW_SHIPS 1
#define HIDE_SHIPS 0

#define PLACEMENT_MODE 1
#define BATTLE_MODE 2

#define PLAYER1_SCREEN 1
#define PLAYER2_SCREEN 2

#define VERT 1
#define HOR 2

enum CellState { WATER, SHIP, HIT, KILL, MISS };

// Типы кораблей
enum { BATTLESHIP, CRUISER, DESTROYER, BOAT };

// Коды ошибок
enum {
    SUCCESS 	   = 0,
    ERR_ALLOCATION = 1,
    ERR_NO_SPACE   = 2,
    ERR_OCC_CELL   = 3,
    ERR_RE_ATTACK  = 4
};

#endif
