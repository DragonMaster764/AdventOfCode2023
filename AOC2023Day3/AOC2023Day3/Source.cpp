#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool isSymbol(char c);
bool isNotSymbol(char c);
bool checkForSymbol(vector<vector<char>> grid, vector<int> numberCoords, int curRowNum);

int main()
{

	//Make a new fstream to read the file
	fstream fileReader;

	//Open the input file
	fileReader.open("Input.txt");

	//Holds the current line
	string curLine;

	//Stores the total 
	int total = 0;

	//Makes the grid variable
	vector<vector<char>> grid;


	//Put the input into a vector grid
	while (getline(fileReader, curLine))
	{
		vector<char> rowToAdd;

		for (int i = 0; i < curLine.size(); i++)
		{
			rowToAdd.push_back(curLine[i]);
		}

		grid.push_back(rowToAdd);
	}


	//Prints grid (for test only)
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			cout << grid[i][j];
		}

		cout << endl;
	}

	//Checks for the part numbers in the grid
	for (int i = 0; i < grid.size(); i++)
	{
		int rowElementLocator = 0; 

		while (rowElementLocator < grid[i].size())
		{

			//Checks to see if element is a number using ASCII Table, if not, advance to next char
			if (isNotSymbol(grid[i][rowElementLocator]))
			{

				//Stores number and coordinates 
				vector<int> coordinates;
				string numberString = "";

				coordinates.push_back(rowElementLocator);
				numberString += grid[i][rowElementLocator];

				rowElementLocator++;

				//Checks for numbers grouped
				while (rowElementLocator < grid[i].size() && grid[i][rowElementLocator] != '.' 
					&& isNotSymbol(grid[i][rowElementLocator]))
				{
					if (isNotSymbol(grid[i][rowElementLocator]))
					{
						coordinates.push_back(rowElementLocator);
						numberString += grid[i][rowElementLocator];
					}

					rowElementLocator++;
				}

				//Checks if it is touching a symbol and is a part number, add to total
				if (checkForSymbol(grid, coordinates, i))
				{
					total += stoi(numberString);
				}

			}
			else {
				rowElementLocator++;
			}

			

		}
	}
	
	cout << "The total is: " << total << endl;

	return 0;
}


//Method that checks to see if symbol is adjacent, or next to a symbol 
bool checkForSymbol(vector<vector<char>> grid, vector<int> numberCoords, int curRowNum)
{
	//As long as it is not the first row, check for top left/right diagonals and above symbols
	if (curRowNum != 0) 
	{

		if (numberCoords[0] - 1 > 0)
		{
			char topLeftDiag = grid[curRowNum - 1][numberCoords[0] - 1];

			if (isSymbol(topLeftDiag))
			{
				return true;
			}
		}

		if (numberCoords[numberCoords.size() - 1] + 1 < grid.size() - 1) 
		{
			char topRightDiag = grid[curRowNum - 1][numberCoords[numberCoords.size() - 1] + 1];


			if (isSymbol(topRightDiag))
			{
				return true;
			}
		}


		for (int i = 0; i < numberCoords.size(); i++)
		{
			if (isSymbol(grid[curRowNum - 1][numberCoords[i]]))
			{
				return true;
			}
		}
	}

	//Checks the char to the left as long as the first coordinate isn't 0
	if (numberCoords[0] != 0)
	{
		if (isSymbol(grid[curRowNum][numberCoords[0] - 1]))
		{
			return true;
		}
	}

	//Checks char to the right as long as the last coordinate isn't the edge
	if (numberCoords[numberCoords.size() - 1] != grid[curRowNum].size() - 1)
	{
		if (isSymbol(grid[curRowNum][numberCoords[numberCoords.size() - 1] + 1]))
		{
			return true;
		}
	}

	//Checks bottom row and diagonals (if not the last row)
	if (curRowNum != grid.size() - 1) {

		if (numberCoords[0] - 1 > 0)
		{
			char botLeftDiag = grid[curRowNum + 1][numberCoords[0] - 1];


			if (isSymbol(botLeftDiag))
			{
				return true;
			}
		}
		

		if (numberCoords[numberCoords.size() - 1] + 1 < grid.size() - 1)
		{
			char botRightDiag = grid[curRowNum + 1][numberCoords[numberCoords.size() - 1] + 1];


			if (isSymbol(botRightDiag))
			{
				return true;
			}
		}


		for (int i = 0; i < numberCoords.size(); i++)
		{
			if (isSymbol(grid[curRowNum + 1][numberCoords[i]]))
			{
				return true;
			}
		}
	}

	//Else return false
	return false;
}

bool isSymbol(char c) 
{
	if (c != '.' && ((c >= 33 && c <= 45)
		|| c == 47 || (c >= 60 && c <= 64)))
	{
		return true;
	}
	else {
		return false;
	}
}

bool isNotSymbol(char c)
{
	if (c != '.' && !(c >= 33 && c <= 45)
		&& c != 47 && !(c >= 60 && c <= 64))
	{
		return true;
	}
	else {
		return false;
	}
}