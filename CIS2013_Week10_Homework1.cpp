#include <iostream>
#include <time.h>
#include <cstdlib>
#include <exception>
using namespace std;

//Function declarations
int rng(int);
void printReal(int, int, char**);
void printView(int, int, char**);
char** genMap(int, int);
char** genView(int, int);
bool** genChoices(int, int);
void deallocateMap(char**, int);
void deallocateChoices(bool**, int);
char** putMinesOnMap(char**, int, int, int);
void checkTileForMine(char** map, char** view, int x, int y);

//Global variables
int numberOfSweptSpaces=0;
int numberOfEmptySpaces=0;
int main()
{
	//Use time as a seed for the rng
	srand(time(NULL));

	int rows = -1;
	int columns = -1;
	int numberOfMines = -1;
	bool sweptAll = false;

	//Ask user for input until valid entry for rows, columns and the number of mines
	while(rows <= 0)
	{
		cout << "Enter the number of rows: ", cin >> rows, cout << endl;		
		if(rows == 0)
		{
			cout << "Invalid entry, please enter a number.\n\n\a";
		}
		if(rows > 22)
		{
			cout << "The maximum supported rows is currently 22." << endl;
			rows = -1;
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
		int numOfTiles = (rows * columns);
		if(numberOfMines > numOfTiles)
		{
			cout << "You cannot have more mines then there are tiles in the game." << endl;
			numberOfMines = -1;
		}
		cin.clear();
		cin.ignore(100, '\n');
	}
	numberOfEmptySpaces = ((rows*columns) - numberOfMines);
	//Generate the map
	char** map = genMap(rows, columns);
	map = putMinesOnMap(map, rows, columns, numberOfMines);

	//Generate the view array
	char** view = genView(rows, columns);

	//Generate choices array
	bool** choices = genChoices(rows, columns);
	

	while(!sweptAll)
	{

		//Print the real map
		printReal(rows, columns, map);
		cout << "\n";
		//Print the view
		printView(rows, columns, view);

		//Create coordinates
		int x, y;
		//Get coordinates from user
		cout << "Enter a row and column to sweep.\nRow:", cin >> x; cout << "\nColumn:", cin >> y;

		if(choices[x-1][y-1] == true)
		{
			cout << "You already swept this tile." << endl;
		}
		else
		{
			checkTileForMine(map, view, x-1, y-1);	
			choices[x-1][y-1] = true;
		}

		if(numberOfSweptSpaces == numberOfEmptySpaces)
		{
			sweptAll = !sweptAll;
		}
	}

	cout << "\nCONGRATS YOU WIN!\n";
	//Print Real Map
	
	//Deallocate the arrays
	deallocateMap(map, rows);
	deallocateChoices(choices, rows);
	return 0;
}

void checkTileForMine(char** map, char** view, int x, int y)
{
	if(map[x][y] == 'M')
	{
		cout << "You hit a mine." << endl;
		//printReal
		//end the game
	}
	else
	{
		cout << "You swept the tile, and found no mines." << endl;
		view[x][y] = ' ';
		numberOfSweptSpaces++;


	}
}

char** putMinesOnMap(char **map, int rows, int columns, int numberOfMines)
{
	
	int mineCounter = 0;

	while(mineCounter != numberOfMines)
	{
		int numberOfTiles = rows * columns;
		int i = rng(rows) - 1;
		
		int diceRoll = rng(numberOfTiles) - 1;
		int j = rng(columns) - 1;
		if(diceRoll == 0 && map[i][j] != 'M')
		{
			map[i][j] = 'M';
			mineCounter++;
		}
	}
	return map;
}

//Random number generator used for arrays. Returns from 1 to max number provided as argument
int rng(int max)
{
	int randomN = 1 + rand() % max;
	return randomN;
}
//Prints the view for the user
//TODO update view
void printView(int rows, int columns, char**view)
{
	//Spacing
	cout << "     ";
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
	cout << endl;
	cout << "    ";
	//Print a line for the top of the view
	for (int i = 0; i < (columns*3)+1; i++) 
	{ 
		cout << "-";
	}
	cout << endl;
	//Print each view row
	for (int i = 0; i < rows; ++i)
	{
		//Print the row number
		cout << endl << i + 1;
		if(i<9){cout << " ";}
		cout << "|  ";
		for (int j = 0; j < columns; ++j)
		{
			//Print the tile and some spaces
			cout << view[i][j] << "  ";
		}
		//Print the row number again
		cout << "\b | " << i + 1 << endl;
	}
	//Print a new line and some spaces
	cout << endl;
	cout << "    ";
	//Print a line for the bottom of the view
	for (int i = 0; i < (columns*3)+1; i++) { cout << "-";}
	cout << endl;
	cout << "     ";
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

//Prints the real map for development
void printReal(int rows, int columns, char **map)
{
	//Spacing
	cout << "     ";
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
	cout << endl;
	cout << "    ";
	//Print a line for the top of the map
	for (int i = 0; i < (columns*3)+1; i++) 
	{ 
		cout << "-";
	}
	cout << endl;
	//Print each map row
	for (int i = 0; i < rows; ++i)
	{
		//Print the row number
		cout << endl << i + 1;
		if(i<9){cout << " ";}
		cout << "|  ";
		for (int j = 0; j < columns; ++j)
		{
			//Print the tile and some spaces
			cout << map[i][j] << "  ";
		}
		//Print the row number again
		cout << "\b | " << i + 1 << endl;
	}
	//Print a new line and some spaces
	cout << endl;
	cout << "    ";
	//Print a line for the bottom of the map
	for (int i = 0; i < (columns*3)+1; i++) { cout << "-";}
	cout << endl;
	cout << "     ";
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
//Deallocates the map array
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
//Deallocates the choices array
void deallocateChoices(bool **choices, int rows)
{
	try
	{
		delete[] choices;
	}
	catch(exception e)
	{
		//Just do nothing
	}	
}
//Generates the map array
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
			//Blank or Clear Tile
			map[i][j] = ' ';
		}
	}
	return map;
}

//Generates the view array
char** genView(int rows, int columns)
{
	//Allocate a two dimensional row x column array
	char** view = new char*[rows];
	for (int i = 0; i < rows; ++i)
	{
		view[i] = new char[columns];
	}

	//Fill array with Unchosen Tiles
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			//Unchosen Tile
			view[i][j] = '+';
		}
	}
	return view;
}

//Generates the choices array
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
