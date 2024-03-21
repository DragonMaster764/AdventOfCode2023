#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

//Make a structure where each "pipe" points to two locations
struct Pipe {

	int row, column;

	//Where does one end of the pipe point to 
	int enterRow, enterColumn;

	//Where the other end points to
	int exitRow, exitColumn;

	bool isS;

};

void addPipes(vector<vector<Pipe>>& g, string line, int curRow);
Pipe findNextPipe(vector<vector<Pipe>> g, Pipe pipe, int& lRow, int& lCol);

int main()
{

	//Get the file
	ifstream fileReader("Input.txt");

	//Grid variable
	vector<vector<Pipe>> grid;

	//For each pipe, check the type, put the two coordinates it looks to
	string curLine;
	int rowNum = 0; // Count rows by starting at zero

	while (getline(fileReader, curLine)) {
		addPipes(grid, curLine, rowNum);
		rowNum++;
	}

	//Find S
	bool foundS = false;
	Pipe sPipe = { -1 };
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++) 
		{
			if (grid[i][j].isS == true) {
				foundS = true;
				sPipe = grid[i][j];
				cout << "Found S at location (" << sPipe.enterRow << ", " << sPipe.enterColumn << ") " << endl;
				break;
			}
		}

		if (foundS)
			break;
	}

	//See what pipes S could point to
	// Check a 3x3 grid, with the sPipe being the center
	vector<Pipe> posPipes;

	int rowStart = sPipe.enterRow - 1;
	if (rowStart < 0)
		rowStart = 0;

	int columnStart = sPipe.enterColumn - 1;
	if (columnStart < 0)
		columnStart = 0;

	for (int i = rowStart; i <= sPipe.enterRow + 1; i++) {

		for (int j = columnStart; j <= sPipe.enterColumn + 1; j++) {

			Pipe curPipe = grid[i][j];
			if (!curPipe.isS) 
			{

				if ((curPipe.enterColumn == sPipe.enterColumn && curPipe.enterRow == sPipe.enterRow) ||
					(curPipe.exitColumn == sPipe.exitColumn && curPipe.exitRow == sPipe.exitRow))
				{
					posPipes.push_back(curPipe);
					cout << "Found a possible pipe!" << endl;
				}
			}
		}

	}

	//Follow one pipe, count steps
	vector<Pipe> path = { sPipe };

	int lastRow = sPipe.row;
	int lastColumn = sPipe.column;

	Pipe curPathPipe = posPipes[0];
	path.push_back(curPathPipe);

	while (!curPathPipe.isS) {
		Pipe nextPipe = findNextPipe(grid, curPathPipe, lastRow, lastColumn);
		path.push_back(nextPipe);
		curPathPipe = nextPipe;
		//cout << path.size() << endl;
	}

	//Find max distance by steps/2
	int maxDist = path.size() / 2;
	cout << "Max Distance: " << maxDist << endl;

	fileReader.close();
	return 0;
}


//Function adds the row of pipes to the grid
void addPipes(vector<vector<Pipe>> & g, string line, int curRow) {

	vector<Pipe> row;

	for (int i = 0; i < line.length(); i++)
	{
		Pipe newPipe;
		newPipe.isS = false;
		newPipe.row = curRow;
		newPipe.column = i;

		char c = line[i];

		if (c == '|') { 
			newPipe.enterColumn = i;
			newPipe.enterRow = curRow - 1;
			newPipe.exitColumn = i;
			newPipe.exitRow = curRow + 1;
		}
		else if (c == '-') {
			newPipe.enterColumn = i + 1;
			newPipe.enterRow = curRow;
			newPipe.exitColumn = i - 1;
			newPipe.exitRow = curRow;
		}
		else if (c == 'L') {
			newPipe.enterColumn = i;
			newPipe.enterRow = curRow - 1;
			newPipe.exitColumn = i + 1;
			newPipe.exitRow = curRow;
		}
		else if (c == 'J') {
			newPipe.enterColumn = i;
			newPipe.enterRow = curRow - 1;
			newPipe.exitColumn = i - 1;
			newPipe.exitRow = curRow;
		}
		else if (c == '7') {
			newPipe.enterColumn = i;
			newPipe.enterRow = curRow + 1;
			newPipe.exitColumn = i - 1;
			newPipe.exitRow = curRow;
		}
		else if (c == 'F') {
			newPipe.enterColumn = i;
			newPipe.enterRow = curRow + 1;
			newPipe.exitColumn = i + 1;
			newPipe.exitRow = curRow;
		}
		else if (c == 'S') {
			//Holds location of S
			newPipe.enterColumn = i;
			newPipe.enterRow = curRow;
			newPipe.exitColumn = i;
			newPipe.exitRow = curRow;
			newPipe.isS = true;
		}
		else {
			newPipe.enterColumn = -1;
			newPipe.enterRow = -1;
			newPipe.exitColumn = -1;
			newPipe.exitRow = -1;
		}

		row.push_back(newPipe);
	}


	g.push_back(row);
}

//Gets the grid, returns the pipe not travelled on
Pipe findNextPipe(vector<vector<Pipe>> g, Pipe pipe, int & lRow, int & lCol) {

	Pipe nextPipe = {-1};

	if (lRow == pipe.enterRow && lCol == pipe.enterColumn) {
		nextPipe = g[pipe.exitRow][pipe.exitColumn];
		lRow = pipe.row;
		lCol = pipe.column;
	}
	else if (lRow == pipe.exitRow && lCol == pipe.exitColumn) {
		nextPipe = g[pipe.enterRow][pipe.enterColumn];
		lRow = pipe.row;
		lCol = pipe.column;
	}
	else {
		cout << "ERROR" << endl;
	}

	return nextPipe;
}