#include<iostream> // for printing da map
#include"Map.h"
#include"Snake.h"
#include<time.h>

using namespace std;

//default constructor
Map::Map(Snake &_snake){
   snake = &_snake;
   maxRows = 10;
   maxCols = 20;
   bgChar = ' ';
   foodChar = 'f';
   foodRow = (maxRows/2)+3;
   foodCol = (maxCols/2)-3;

   
   // initialize the grid:
   grid = new char*[maxRows];
   for(int i = 0; i < maxRows; i++){
      grid[i] = new char[maxCols];
   }

   // add <the border:
   grid[0][0] = '+';
   grid[maxRows-1][maxCols-1] = '+';
   grid[0][maxCols-1] = '+';
   grid[maxRows-1][0] = '+';

   for (int i = 1; i < maxRows-1; i++){
      grid[i][0] = '|';
      grid[i][maxCols-1] = '|';
   }
   for (int i = 1; i < maxCols-1; i++){
      grid[0][i] = '-';
      grid[maxRows-1][i] = '-';
   }


   srand(time(NULL));
}

//overloaded constructor
Map::Map(Snake &_snake, int _maxRows, int _maxCols){
   if(!(_maxRows <= 0 || _maxCols <= 0)){
      snake = &_snake;
      maxRows = _maxRows;
      maxCols = _maxCols;
      bgChar = ' ';
      foodChar = 'f';
      foodRow = (maxRows/2)+3;
      foodCol = (maxCols/2)-3;
      
      // initialize the grid:
      grid = new char*[maxRows];
      for(int i = 0; i < maxRows; i++){
         grid[i] = new char[maxCols];
      }

      // add the border:
      grid[0][0] = '+';
      grid[maxRows-1][maxCols-1] = '+';
      grid[0][maxCols-1] = '+';
      grid[maxRows-1][0] = '+';

      for (int i = 1; i < maxRows-1; i++){
         grid[i][0] = '|';
         grid[i][maxCols-1] = '|';
      }
      for (int i = 1; i < maxCols-1; i++){
         grid[0][i] = '-';
         grid[maxRows-1][i] = '-';
      }

   }

   srand(time(NULL));

}

Map::~Map(){
   for(int i = 0; i < maxRows; i++){
      delete[] grid[i];
   }
   delete[] grid;
}

void Map::update(){
   
   // fill the grid with bgchar:
   for(int i = 1; i < maxRows-1; i++){
      for(int j = 1; j < maxCols-1; j++){
         grid[i][j] = bgChar;
      }
   }
   
   // put the snake on the grid:
   for(Segment* s : snake->segments){
      grid[s->getRow()][s->getCol()] = s->displayChar;
   }
   
   // place the food
   grid[foodRow][foodCol] = foodChar;

}

bool Map::check(){
   
   bool ok = true;

   //check for border collisions
   //(only the head, since segments cannot be anywhere the head has not been first)
   if(snake->segments[0]->getRow() == 0 || snake->segments[0]->getCol() == 0){
         ok = false;
         //cout << "hit top or left";
         //cout << "\nHead Row: " << snake->segments[0]->getRow();
         //cout << "\nHead Col: " << snake->segments[0]->getCol() << endl;

   }
   if(snake->segments[0]->getRow() == (maxRows-1) || snake->segments[0]->getCol() == (maxCols-1)){
         ok = false;
         //cout << "hit bottom or right";
         //cout << "\nHead Row: " << snake->segments[0]->getRow();
         //cout << "\nHead Col: " << snake->segments[0]->getCol() << endl;
   }
   
   //check for collisions with self
   //(only after length is long enough for collisions to be possible)
   if(snake->length > 4){
      for(int i = 1; i < snake->segments.size(); i++){
         if(*snake->segments[0] == *snake->segments[i]){ // use of overloaded == operator
            ok = false;
            //cout << "hit self";
            //cout << "\nHead Row: " << snake->segments[0]->getRow();
            //cout << "\nHead Col: " << snake->segments[0]->getCol() << endl;
         }
      }
   }

   //check for food
   if(snake->segments[0]->getRow() == foodRow && snake->segments[0]->getCol() == foodCol){
      snake->grow();
      if(snake->length > 5)
         snake->grow();
      makeFood((rand() % (maxRows-2) + 1),(rand() % (maxCols-2) + 1));
      //cout << "made food at " << foodRow << foodCol << endl;
   }

   return ok;

}

void Map::printBasic(){
   // print the grid:
   for(int i = 0; i < maxRows; i++){
      for(int j = 0; j < maxCols; j++){
         cout << grid[i][j];
      }
      cout << endl;
   }

}

void Map::makeFood(int _row, int _col){
   
   bool fail = false;
   
   do{
      
      for(Segment* s : snake->segments){
         if(s->getRow() == _row && s->getCol() == _col){
            fail = true;
         }
      }
      if(fail){
         _row = (rand() % (maxRows-2) + 1);
         _col = (rand() % (maxCols-2) + 1);
         fail = false;
         for(Segment* s : snake->segments){
            if(s->getRow() == _row && s->getCol() == _col){
               fail = true;
            }
         }

      }

   }while(fail);

   foodCol=_col;
   foodRow=_row;
}
