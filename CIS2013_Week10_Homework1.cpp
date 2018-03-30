#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

int rng(int);
void printReal(int, int, char**);
char** genMap(int, int);
void deallocateMap(char**, int);
int main()
{
	//Use time as a seed for the rng
	srand(time(NULL));

	int rows;
	int columns;
	int numberOfMines;


	cout << "Enter the number of rows: ", cin >> rows, cout << endl;
	cout << "Enter the number of columns: ", cin >> columns, cout << endl;
	cout << "Enter the number of mines: ", cin >> numberOfMines, cout << endl;

	//cout << rng(numberOfMines);

	char** map = genMap(rows, columns);

	printReal(rows, columns, map);
	//Go through array and fill with mines
	//int currentNumberOfMines = 0;
	//int diceRoll;
	//diceRoll = rng(rows * columns);
	deallocateMap(map, rows);

	return 0;
}

//Random number generator used for arrays. Returns from 1 to max number provided as argument
int rng(int max)
{
	int randomN = 1 + rand() % max;
	return randomN;
}
//Print the real map
void printReal(int rows, int columns, char **map)
{
	//Print array
	cout << "  ";
	for (int i = 0; i < columns; i++) { cout << i + 1 << " "; }
	for (int i = 0; i < rows; ++i)
	{
		cout << endl << i + 1 << " ";
		for (int j = 0; j < columns; ++j)
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}
void deallocateMap(char **map, int rows)
{
	try
	{
		delete[] map;
	}
	catch(exception e)
	{
		//Just do nothing
	}
		
	
}

char** genMap(int rows, int columns)
{
	//Allocate a two dimensional row x column array
	char** map = new char*[rows];
	for (int i = 0; i < rows; ++i)
	{
		map[i] = new char[columns];
	}

	//Fill array with empty spaces
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			map[i][j] = '.';
		}
	}
	return map;
}
