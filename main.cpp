#include <iostream>
#include <map>
#include <string>
#include "game_of_life.h"

using namespace std;

int main(){
	game_of_life life; //creating a game of life object
	life.read(); //reading in the file
	life.run(); //running the program to update the map 

	cout << "Done!" << endl; //prints done when you are finished with the game

	return 0;
}