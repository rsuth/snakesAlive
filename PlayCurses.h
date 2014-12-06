#ifndef PLAYCURSES_H
#define PLAYCURSES_H

#include<curses.h>
#include"Map.h"
#include"Snake.h"

// the main game loop.
void playGameCurses();

void printMapCurses(Map &gameMap, WINDOW* win);

// initialize a curses window
WINDOW* initCurses();

void getDirectionCurses(WINDOW* win, Direction &dir);

#endif

