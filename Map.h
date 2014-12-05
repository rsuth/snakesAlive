#ifndef MAP_H
#define MAP_H

#include"Snake.h"

using namespace std;

class Map{
   public:
      Map( Snake &_snake );
      Map( Snake &_snake, int _maxRows, int _maxCols);
      ~Map();
      int maxRows;
      int maxCols;
      int foodRow;
      int foodCol;
      char bgChar;
      char foodChar;
      char** grid;
      Snake* snake;
      void update();
      bool check();
      void printBasic();
      void makeFood(int _row, int _col);
};

#endif/*MAP_H*/
