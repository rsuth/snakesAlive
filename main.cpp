#include"Snake.h"
#include"Map.h"
#include<iostream>
#include<vector>
#include<unistd.h>
#include<curses.h>
#include<string>

using namespace std;

void playGame();

void printMapCurses(Map &gameMap, WINDOW* win);

void getDirectionFromKeyboard(WINDOW* win, Direction &dir);

int main(){         
   
   playGame();
   return 0;
}

void playGame(){
   int windowRows;
   int windowCols;
   int mapRows = 10;
   int mapCols = 10;
   int leftPad = 10;
   int topPad = 10;
   int i = 0;
   char buffer[100];

   Direction direction = DOWN;
    
   initscr();
   cbreak();
   curs_set(0);
   noecho();
   start_color();
   init_pair(1, COLOR_GREEN, COLOR_GREEN);
   init_pair(2, COLOR_RED, COLOR_RED);
   init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
   init_pair(4, COLOR_RED, COLOR_GREEN);
   getmaxyx(stdscr, windowRows, windowCols);
   leftPad = windowRows/4;
   topPad = windowCols/4;
   mapRows = windowRows/2;
   mapCols = windowCols/2;

   WINDOW* gameWindow;
   gameWindow = newwin( mapRows, mapCols, leftPad, topPad );
   keypad(gameWindow, true);
   nodelay(gameWindow, true);
   
   Snake snake(mapRows/2, mapCols/2);
   snake.setHeadChar('\'');

   Map gameMap(snake,mapRows,mapCols);
   gameMap.bgChar = ' ';


   printMapCurses(gameMap, gameWindow);

   while(gameMap.check()){
      getDirectionFromKeyboard(gameWindow, direction);
      snake.move(direction);
      gameMap.update();
      printMapCurses(gameMap, gameWindow);
      usleep(100000);
   }

   mvwprintw(gameWindow, mapRows/2, (mapCols/2)-5, "GAME OVER");
   wrefresh(gameWindow);
   nodelay(gameWindow, false);
   wgetstr(gameWindow, buffer);
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
         if(gameMap.grid[i][j] == '\'')
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

void getDirectionFromKeyboard(WINDOW* win, Direction &dir){
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
