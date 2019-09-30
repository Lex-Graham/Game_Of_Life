#include <iostream>
#include <map>
#include <string>
#include "Game_Of_Life.h"

using namespace std;

int main(){
	Game_Of_Life life; //creating a game of life object
	life.read(); //reading in the file
	life.run(); //running the program to update the map

	cout << "Done!" << endl; //prints done when you are finished with the game

	return 0;
}
