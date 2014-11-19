#include"Snake.h"
#include"Map.h"
#include<iostream>
#include<vector>
#include<unistd.h>

using namespace std;

void playGame();

int main(){         
   
   playGame();
   cin.ignore();
   return 0;
}

void playGame(){
   int mapRows = 40;
   int mapCols = 60;
   int i = 0;
   Direction direction = DOWN;
   
   Snake snake(mapRows/2, mapCols/2);

   Map gameMap(snake,mapRows,mapCols);
   
   gameMap.bgChar = '-';
   
   while(gameMap.check()){ 
      cout << endl;
      cout << "\niteration #: " << i << endl;      
      
      snake.move(direction);
      
      gameMap.update();      
      gameMap.printBasic();
      
      i++;

      if(i > 2)
         direction = LEFT;
      
      cin.ignore();   
   }

   cout << "GAME OVER";

}



