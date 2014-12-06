#include"Snake.h"
#include"Map.h"
#include<iostream>
#include"PlayCurses.h"
#include<unistd.h>

using namespace std;

void printMainMenu();
void runMainMenu();

int main(){
    runMainMenu();
    return 0;
}

void printMainMenu(){
   cout << "\n\t\tSnakes!";
   cout << "\n\t\t-------";
   cout << "\n\t\tPress da key to make a selection...";
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

