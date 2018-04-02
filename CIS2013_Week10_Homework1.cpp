#include <iostream>
#include <time.h>
#include <cstdlib>
#include <exception>
using namespace std;

int rng(int);
void printReal(int, int, char**);
void printView(int, int, char**);
char** genMap(int, int);
bool** genChoices(int, int);
void deallocateMap(char**, int);
int main()
{
	//Use time as a seed for the rng
	srand(time(NULL));

	int rows = -1;
	int columns = -1;
	int numberOfMines = -1;
	bool validate;


	while(rows <= 0)
	{
		cout << "Enter the number of rows: ", cin >> rows, cout << endl;		
		if(rows == 0)
		{
			cout << "Invalid entry, please enter a number.\n\n\a";
		}
		cin.clear();
		cin.ignore(100, '\n');
	}


	while(columns <= 0)
	{
		cout << "Enter the number of columns: ", cin >> columns, cout << endl;	
		if(columns == 0)
		{
			cout << "Invalid entry, please enter a number.\n\n\a";
		}
		cin.clear();
		cin.ignore(100, '\n');
	}

	while(numberOfMines <= 0)
	{
		cout << "Enter the number of mines: ", cin >> numberOfMines, cout << endl;		
		if(numberOfMines == 0)
		{
			cout << "Invalid entry, please enter a number.\n\n\a";
		}
		cin.clear();
		cin.ignore(100, '\n');
	}
	
	//Generate the map
	char** map = genMap(rows, columns);
	//Generate choices array
	bool** choices = genChoices(rows, columns);

	//Print the real map
	cout << "\t\t\n\n---------" << endl;
	printReal(rows, columns, map);
	cout << "\t\t\n\n---------\n\n" << endl;
	printView(rows, columns, map);
	cout << "\t\t\n\n---------\n\n" << endl;

	deallocateMap(map, rows);
	return 0;
}

//Random number generator used for arrays. Returns from 1 to max number provided as argument
int rng(int max)
{
	int randomN = 1 + rand() % max;
	return randomN;
}

void printView(int rows, int columns, char**map)
{
	//Spacing
	cout << "   ";
	for (int i = 0; i < columns; i++) 
	{
		//Print the column number
		if(i<9)
		{
			cout << i + 1 << "  ";
		}else
		{
			cout << i + 1 << " "; 
		}
	}
	//Spacing
	cout << endl << "   ";
	//Print a line for the top of the map
	for (int i = 0; i < (columns*3)-1; i++) 
	{ 
		cout << "_";
	}
	//Print each map row
	for (int i = 0; i < rows; ++i)
	{
		//Print the row number
		cout << endl << i + 1;
		if(i<9){cout << " ";}
		cout << "|";
		for (int j = 0; j < columns; ++j)
		{
			//Print the tile and some spaces
			cout << (char)219 << "  ";
		}
		//Print the row number again
		cout << "\b|" << i + 1 << endl;
	}
	//Print a new line and some spaces
	cout << endl << "   ";
	//Print a line for the bottom of the map
	for (int i = 0; i < (columns*3)-1; i++) { cout << "_";}
	cout << endl;
	cout << "   ";
	//Print the column numbers again
	for (int i = 0; i < columns; i++) 
	{ 
		if(i<9){cout << i + 1 << "  ";
	}
	else
		{
			cout << i + 1 << " "; 
		}
	}
	cout << endl;
}

//Print the real map
void printReal(int rows, int columns, char **map)
{
	//Spacing
	cout << "   ";
	for (int i = 0; i < columns; i++) 
	{
		//Print the column number
		if(i<9)
		{
			cout << i + 1 << "  ";
		}else
		{
			cout << i + 1 << " "; 
		}
	}
	//Spacing
	cout << endl << "   ";
	//Print a line for the top of the map
	for (int i = 0; i < (columns*3)-1; i++) 
	{ 
		cout << "_";
	}
	//Print each map row
	for (int i = 0; i < rows; ++i)
	{
		//Print the row number
		cout << endl << i + 1;
		if(i<9){cout << " ";}
		cout << "|";
		for (int j = 0; j < columns; ++j)
		{
			//Print the tile and some spaces
			cout << map[i][j] << "  ";
		}
		//Print the row number again
		cout << "\b|" << i + 1 << endl;
	}
	//Print a new line and some spaces
	cout << endl << "   ";
	//Print a line for the bottom of the map
	for (int i = 0; i < (columns*3)-1; i++) { cout << "_";}
	cout << endl;
	cout << "   ";
	//Print the column numbers again
	for (int i = 0; i < columns; i++) 
	{ 
		if(i<9){cout << i + 1 << "  ";
	}
	else
		{
			cout << i + 1 << " "; 
		}
	}
	cout << endl;
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

	//Fill array with Blank Tiles
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			//Blank Tile
			map[i][j] = (char)176;
		}
	}
	return map;
}

bool** genChoices(int rows, int columns)
{
	//Allocate a two dimensional row x column array
	bool** choices = new bool*[rows];
	for (int i = 0; i < rows; ++i)
	{
		choices[i] = new bool[columns];
	}

	//Fill array with unchosen tile
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			//Unchosen tile
			choices[i][j] = false;
		}
	}
	return choices;
}
