/* snake.cpp
 * contains function definitions for the snake
 * and segment classes
 */

#include"Snake.h"
#include<vector>

using namespace std;

int Segment::count = 0;

//default constructor:
Segment::Segment(){
   count++;
   displayChar = 'o';
}

//destructor:
Segment::~Segment(){
   parent = 0;
   count--;
}

Segment::Segment(int _row, int _col){
   row = _row;
   col = _col;
   displayChar = 'o';
   count++;
}

bool Segment::setRow(int _row){
   bool success = true;
   if (_row < 0 )
      success=false;
   else
      row = _row;
   
   return success;
}

bool Segment::setCol(int _col){
   bool success = true;
   if(_col < 0 )
      success = false;
   else
      col = _col;

   return success;
}

Segment* Segment::birth(){
   Segment* newSeg = new Segment(row,col);
   
   newSeg->parent = this;

   return newSeg;
}

Snake::Snake(){
   // default starting position
   startRow = 1;
   startCol = 1;

   // default headChar
   headChar = 'o';

   // make the head, whose parent is itself.
   segments.push_back(new Segment(startRow, startCol));
   segments[0]->parent = segments[0];
   segments[0]->displayChar = headChar;
   
   length = 1;
}

Snake::Snake(int _startRow, int _startCol){
   // parameterized starting position
   startRow = _startRow;
   startCol = _startCol;

   headChar = 'o';

   // make the head, whose parent is itself.
   segments.push_back(new Segment(startRow, startCol));
   segments[0]->parent = segments[0];
   segments[0]->displayChar = headChar;

   
   length = 1;
}

void Snake::grow(){
   segments.push_back(segments[(segments.size()-1)]->birth());
   length++;
}

void Snake::setHeadChar(char head){
   headChar = head;
   segments[0]->displayChar = headChar;
}


bool Snake::move(Direction dir){
   bool success = false;

   for(int i = segments.size()-1; i >= 1; i--){
      segments[i]->setCol(segments[i]->parent->getCol()); 
      segments[i]->setRow(segments[i]->parent->getRow());
   }

   switch(dir){
      case UP:
         
         if(segments[0]->setRow((segments[0]->getRow())-1))
            success = true;
         
         //if(mouthOpen){
            //setHeadChar('|');
            //mouthOpen = false;
         //}else{
            //setHeadChar('v');
            //mouthOpen = true;
         //}

         break;
      case DOWN:
         if(segments[0]->setRow((segments[0]->getRow())+1))
            success = true;
         
         //if(mouthOpen){
            //setHeadChar('|');
            //mouthOpen = false;
         //}else{
            //setHeadChar('^');
            //mouthOpen = true;
         //}
         
         break;
      case LEFT:
         
         if(segments[0]->setCol((segments[0]->getCol())-1))
            success = true;
         
         //if(mouthOpen){
            //setHeadChar('-');
            //mouthOpen = false;
         //}else{
            //setHeadChar('>');
            //mouthOpen = true;
         //}
         
         break;
      case RIGHT:
         if(segments[0]->setCol((segments[0]->getCol())+1))
            success = true;
         
         //if(mouthOpen){
            //setHeadChar('-');
            //mouthOpen = false;
         //}else{
            //setHeadChar('<');
            //mouthOpen = true;
         //}
         
         break;
   }

   return success;

}


