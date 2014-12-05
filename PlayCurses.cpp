#include"PlayCurses.h"
#include<curses.h>
#include<unistd.h>
#include"Snake.h"
#include"Map.h"

using namespace std;

void playGameCurses(){
   int mapRows, mapCols;
   char buffer[100]; // needed for the curses equivalent of getline, holds garbage input
   Direction direction = DOWN; // the direction variable set to default starting direction
   
   WINDOW* gameWindow = initCurses();
   getmaxyx(gameWindow, mapRows, mapCols);

   // Make a snake in the center of the board
   Snake snake(mapRows/2, mapCols/2);

   // make the map
   Map gameMap(snake,mapRows,mapCols);

   // print once
   printMapCurses(gameMap, gameWindow);
   
   // the game Loop:
   // checks the game Map for issues every time it loops.
   // check handles all collisions as well as food.
   while(gameMap.check()){
      
      // First, get the direction from the keyboard, 
      // and assign it to direction variable. If no input,
      // the direction stays the same.
      getDirectionCurses(gameWindow, direction);

      // Move once in the direction.
      snake.move(direction);

      // Update the Map, so we can use the grid
      gameMap.update();

      // print the map:
      printMapCurses(gameMap, gameWindow);

      // sleep.(this value controls the speed of the game)
      usleep(100000);
   }

   mvwprintw(gameWindow, mapRows/2, (mapCols/2)-5, "GAME OVER");
   wrefresh(gameWindow);
   nodelay(gameWindow, false);
   wgetstr(gameWindow, buffer);
   
   //delete gameWindow;
   delwin(gameWindow);
   endwin();

}

void printMapCurses(Map &gameMap, WINDOW* win){
   for(int i = 0; i < gameMap.maxRows; i++){
      for(int j = 0; j < gameMap.maxCols; j++){
         
         if(gameMap.grid[i][j] == 'o')
            wattron(win, COLOR_PAIR(1));
         if(gameMap.grid[i][j] == 'f')
            wattron(win, COLOR_PAIR(2));
         if(gameMap.grid[i][j] == '|' || gameMap.grid[i][j] == '-' || gameMap.grid[i][j] == '+')
            wattron(win, COLOR_PAIR(3));
         if(gameMap.grid[i][j] == '*')
            wattron(win, COLOR_PAIR(4));

         mvwaddch(win, i, j, gameMap.grid[i][j]);
         wattroff(win, COLOR_PAIR(1));
         wattroff(win, COLOR_PAIR(2));
         wattroff(win, COLOR_PAIR(3));
         wattroff(win, COLOR_PAIR(4));
      }
   }
   wrefresh(win);
}

void getDirectionCurses(WINDOW* win, Direction &dir){
   switch(wgetch(win)){
      case KEY_UP:
      case 'w':
         if(dir != DOWN)
            dir = UP;
         break;
      case KEY_DOWN:
      case 's':
         if(dir != UP)
            dir = DOWN;
         break;
      case KEY_LEFT:
      case 'a':
         if (dir != RIGHT)
            dir = LEFT;
         break;
      case KEY_RIGHT:
      case 'd':
         if (dir != LEFT)
            dir = RIGHT;
         break;
      default:
         break;
   }
}

WINDOW* initCurses(){
   int windowRows, windowCols, mapRows, mapCols, leftPad, topPad;
   
   // set up curses stuff
   initscr();        // intialize curses
   cbreak();         // needed for non-blocking getch
   curs_set(0);      // Do not display cursor
   noecho();         // do not echo keyboard input
   
   // initialize color pairs:
   start_color();    // use colors
   init_pair(1, COLOR_GREEN, COLOR_GREEN);
   init_pair(2, COLOR_RED, COLOR_RED);
   init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
   init_pair(4, COLOR_RED, COLOR_GREEN);
   init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
   
   // configure window geometry:
   getmaxyx(stdscr, windowRows, windowCols);
   leftPad = windowRows/4;
   topPad = windowCols/4;
   mapRows = windowRows/2;
   mapCols = windowCols/2;
   
   // Make the window:
   WINDOW* gameWindow;
   gameWindow = newwin( mapRows, mapCols, leftPad, topPad );
   keypad(gameWindow, true);        // allow use of arrow keys
   nodelay(gameWindow, true);       // no blocking on getch

   return gameWindow;

}
