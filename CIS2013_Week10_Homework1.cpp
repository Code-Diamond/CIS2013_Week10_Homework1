#include <iostream>
#include <time.h>
#include <cstdlib>
#include <exception>
using namespace std;

//Function declarations
int rng(int);
void printReal(int, int, char**);
void printReal(int, int, char**, int, int);
void printView(int, int, char**);
char** genMap(int, int);
char** genView(int, int);
bool** genChoices(int, int);
void deallocateMap(char**, int);
void deallocateChoices(bool**, int);
void deallocateView(char**, int);
char** putMinesOnMap(char**, int, int, int);
void checkTileForMine(char** map, char** view, int, int, int, int);


//Global variables
int x = -1;
int y = -1;
int numberOfSweptSpaces=0;
int numberOfEmptySpaces=0;
int rows = -1;
int columns = -1;
int numberOfMines = -1;
bool sweptAll = false;

int main()
{
	for(int i = 0; i < 50; i++){cout << "\n";}
	cout << "Welcome to Console Minesweeper.\nTo Begin please tell me how many rows and columns you'd like the map.\n   \n";

	//Use time as a seed for the rng
	srand(time(NULL));

	//Ask user for input until valid entry for rows, columns and the number of mines
	while(rows <= 0)
	{
		cout << "Enter the number of rows: ", cin >> rows;		
		if(rows == 0)
		{
			cout << "Invalid entry, please enter a whole number greater than 0.\n\n\a";
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
		cout << "Enter the number of columns: ", cin >> columns;	
		if(columns == 0)
		{
			cout << "Invalid entry, please enter a whole number greater than 0.\n\n\a";
		}
		cin.clear();
		cin.ignore(100, '\n');
	}
	while(numberOfMines <= 0)
	{
		cout << "Enter the number of mines: ", cin >> numberOfMines, cout << endl;		
		if(numberOfMines == 0)
		{
			cout << "Invalid entry, please enter a whole number greater than 0.\n\n\a";
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

		//Enable for testing
			//printReal(rows, columns, map);
			//cout << "\n";

		//Reset x and y
		x = -1;
		y = -1;
		
		//Print the view
		printView(rows, columns, view);
		
		//Get coordinates from user
		while(x <= 0)
		{
			cout << "\nEnter a row and column to sweep.\nRow: ", cin >> x; 	
			if(x == 0)
			{
				cout << "Invalid entry, please enter a whole number greater than 0.\n\n";
			}
			cin.clear();
			cin.ignore(100, '\n');
		}
		while(y <= 0)
		{
			cout << "Column: ", cin >> y; 	
			if(y == 0)
			{
				cout << "Invalid entry, please enter a whole number greater than 0.\n\n";
			}
			cin.clear();
			cin.ignore(100, '\n');
		}

		if(choices[x-1][y-1] == true)
		{
			cout << "You already swept this tile." << endl;
		}
		else
		{
			checkTileForMine(map, view, x-1, y-1, rows, columns);	
			choices[x-1][y-1] = true;
		}

		if(numberOfSweptSpaces == numberOfEmptySpaces)
		{
			sweptAll = !sweptAll;
		}
	}


	cout << "\nCONGRATS YOU WIN!\n";
	
	//Deallocate the arrays
	deallocateMap(map, rows);
	deallocateChoices(choices, rows);
	deallocateView(view, rows);
	return 0;
}

void checkTileForMine(char** map, char** view, int x, int y, int rows, int columns)
{
	if(map[x][y] == 'X')
	{
		cout << "\a\nYou hit a mine!" << endl;
		printReal(rows, columns, map, x, y);
		cout << "\nYOU ARE DEAD!\n";		
		exit(1);
	}
	else
	{
		cout << "\nYou swept the tile, and found no mines.\n" << endl;
		view[x][y] = ' ';
		numberOfSweptSpaces++;
		//Display map if winner
		if(numberOfSweptSpaces == numberOfEmptySpaces)
		{
			printReal(rows,columns,map,x,y);
		}

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
		if(diceRoll == 0 && map[i][j] != 'X')
		{
			map[i][j] = 'X';
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

//Overloaded Function that prints map
void printReal(int rows, int columns, char **map, int x, int y)
{
	map[x][y] = '@';
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
//Deallocates the choices array
void deallocateView(char **view, int rows)
{
	try
	{
		delete[] view;
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
