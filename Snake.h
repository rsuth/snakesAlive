#ifndef SNAKE_H
#define SNAKE_H

#include<vector>

using namespace std;

enum Direction {UP, DOWN, LEFT, RIGHT};

class Segment{
   private:
      int row;
      int col;
   public:
      Segment();
      Segment(int _row, int _col);
      ~Segment();
      static int count;
      int getRow(){return row;};
      int getCol(){return col;};
      bool setRow(int _row);
      bool setCol(int _col);
      Segment* parent;
      Segment* birth();
      char displayChar;
      bool operator==(Segment &rhs){ 
         return ((col == rhs.getCol()) && (row == rhs.getRow()));
      };
};


class Snake{
   public:
      Snake();
      Snake(int _startRow, int _startCol);
      int startRow;
      int startCol;
      int length;
      char headChar;
      vector<Segment*> segments;
      void grow();
      bool move(Direction dir);
      void setHeadChar(char head);
};

#endif/*SNAKE_H*/

