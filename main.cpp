#include"Snake.h"
#include"Map.h"
#include<iostream>
#include"PlayCurses.h"
#include<unistd.h>

using namespace std;

void playGameBasic();

void printMainMenu();
void runMainMenu();
void clearScreen();

int main(){
   
   runMainMenu();


   return 0;
}

void playGameBasic(){
   
   int maxRows = 10;
   int maxCols = 20;
   
   Direction direction = LEFT;

   Snake snake(maxRows/2,maxCols/2);
   
   Map gameMap(snake, 10, 20);

   while(gameMap.check()){
      snake.move(direction);
      gameMap.update();
      gameMap.printBasic();
      usleep(200000);
   }

   cin.ignore();

}

void printMainMenu(){
   cout << "\n\t\tSnakes!";
   cout << "\n\t\t-------";
   cout << "\n\t\tPress a key to make a selection...";
   cout << "\n\t\tP. Play";
   cout << "\n\t\tS. View Scores";
   cout << "\n\t\tQ. Quit" << endl;
}

void runMainMenu(){
   
   bool quit = false;
   char c = 'x';
   while(!quit){
      //clearScreen();
      printMainMenu();
      cout << "\n";
      cin >> c;
      switch(c){
         case 'p':
         case 'P':
            playGameCurses();
            break;
         case 'q':
         case 'Q':
            quit = true;
            break;
      }
   }
}

void clearScreen(){
   for(int i = 0; i < 20; i++){
      cout << "\n";
   }
}

