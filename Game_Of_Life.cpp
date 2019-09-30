#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <map>

#include "Game_Of_Life.h"
using namespace std;

void Game_Of_Life::read(){ //read in the file and put it into a map
	cout << "Enter a filename to bring to life (file should include a square or rectangle consiting only of '.' and '*'): " << endl;
	string filename; //declares a string variable called string
	cin >> filename; //gets input from user about the name of the file they want to use (should be stored in debug folder of the program)

	ifstream file; //declares a ifstream object to extract info from file
	file.open(filename); //opens the file the user inputed

	if (!file) { //checks if file is valid and quits if not
		cerr << "Unable to open file datafile.txt \n Quitting";

		exit(1);   // call system to stop
	}

	//creating the map from the file inputed
	string line; //creates string object called line
	int counter = 0; //initializing counter for establishing what line of the map we are on
	while(file >> line){ //reads in the lines of the file into the line object
		_life_map[counter] = line; //the _life_map at each line = the line from the file
		++counter; //increment counter
	}

	_num_rows = _life_map.size(); //number of rows
	_num_cols = _life_map.at(0).size(); //number of columns

	//printing out the initial map
	cout << "Your map is:" << endl;
	for(int i=0; i<_life_map.size(); ++i){
		cout << _life_map.at(i) << endl;
	}

	char ans = ' '; //initializing a char for input
	bool b = true; //initializing a bool for the while loop while accepting input
	do{
		cout << "Do you want to automate the proccess? (y/n)";
		cin >> ans;
		if (ans == 'y' || ans == 'n') b = false; //checks if the user said y or n and sets b to false to get out of the loop
	}while (b); //if the user put in an invalid response, it asks again untill there is a valid response

	if (ans == 'y'){ //if yes, it will automate the program with the automate bool
		_automate = true;
		cout << "Ctrl-C to quit" << endl; //tells user how to quit
	}else if (ans == 'n'){ //if no, the program will not be automated
		_automate = false;
	}
}

void Game_Of_Life::run(){ //running the game

	map<int, string> temp_life_map; //temporary life map to store values without immediatly changing the real life map
	while (true){ //while loop to update the map as long as the player wants
		temp_life_map = _life_map; //setting the temporary life map equal to the real life map
		if (_automate) this_thread::sleep_for(chrono::seconds(1)); //if it is automated, this will run the code in this function every second

		//for loops to update the map, it takes info from the life map and updates the temp life map
		for(int i=0; i<_life_map.size(); ++i){
			for (int j=0; j<_life_map.at(i).size(); ++j){
				int alive_neighbors = check(i, j); //gets the number of alive neighbors a cell has
				char cell = _life_map.at(i).at(j); //gets the state of the current cell
				if (cell == '*'){
					if (alive_neighbors <= 1){ //solitude, cell dies
						temp_life_map.at(i).at(j) = '.';
					}else if(alive_neighbors >= 4){ //overpopulation, cell dies
					temp_life_map.at(i).at(j) = '.';
				}
				//otherwise cell survives
				}else if (alive_neighbors == 3){
					temp_life_map.at(i).at(j) = '*';
				}
			}
		}
		_life_map = temp_life_map; //updates the life map with the updated temporary life map
		cout << endl;
		for(int i=0; i<_life_map.size(); ++i){ //outputs the map
			cout << _life_map.at(i) << endl;
		}

		//if it isnt automated, then this if block will run
		if (!_automate){
			char answer = ' '; //char variable to store an answer
			bool t = true; //bool variable to make the do while loop work properly
			do{
				cout << endl;
				//do they want to continue the simulation
				cout << "continue? (y/n):";
				cin >> answer;
				if (answer == 'y' || answer == 'n') t = false;
			}while (t);

			if (answer == 'y'){
				//continue
			}else if (answer == 'n'){
				//quits program
				break;
			}
		}
	}
}

int Game_Of_Life::check(int row, int col){
  //count the number of alive cells around the cells
	int alive_neighbors = 0;
	for (int i=row-1; i<=row+1; ++i){
		for (int j=col-1; j<=col+1; ++j){
			if (!in_grid(i, j)) continue; //if its not in the grid, skip it
			if (i == row && j == col) continue; // if its the cell we are checking, skip it
			if (_life_map.at(i).at(j) == '*') ++alive_neighbors; //otherwise, if it is a star, add it to alive neighbors
		}
	}
	return alive_neighbors;
}

bool Game_Of_Life::in_grid(int row, int col){
	return (row >= 0) && (col >= 0) && (row < _num_rows) && (col < _num_cols);
}
