#include <string>
#include <map>

using namespace std;

#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H
class game_of_life{
public:
	void read();
	void run();
	bool in_grid(int row, int col);
	int check(int row, int col);

private:
	map<int, string> _life_map;
	int _num_rows = 0;
	int _num_cols = 0;
	bool _automate = false;
};
#endif