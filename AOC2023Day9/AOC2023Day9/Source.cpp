#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> getValues(string line);
bool isZeroRow(vector<int> v);

int main()
{

	//Variable for total
	int total = 0;

	//Open the input file
	fstream fileReader("Input.txt");

	//For each line, get the next number in the pattern and add to total
	string curLine = "";

	while (getline(fileReader, curLine))
	{
		vector<vector<int>> patternMap;

		//Get the pattern values in a vector
		vector<int> initialRow = getValues(curLine);
		patternMap.push_back(initialRow);
		
		vector<int> curVector = initialRow;

		//While the curVector isn't all zeros, make a new vector that is the difference of two values
		while (!isZeroRow(curVector))
		{
			vector<int> diffVector;

			//curVector.size() - 1, because code grabs the next value to subtract (would go out of scope)
			for (int i = 0; i < curVector.size() - 1; i++)
			{
				int difference = curVector[i + 1] - curVector[i];
				diffVector.push_back(difference);

			}

			//Push current difference vector to the pattern map
			//Also, make the curVector this difference vector
			patternMap.push_back(diffVector);
			curVector = diffVector;


		}

		
		//Since the last row is all zeros, add a zero to the last vector to start the extrapolation
		patternMap[patternMap.size() - 1].push_back(0);

		//Keep adding the last number in the previous row + the last number in the currentRow, then add it
		//to the end of the current row. Starts from the bottom (last element) to the top
		for (int i = patternMap.size() - 2; i >= 0; i--)
		{
			int previousRow = patternMap[i + 1][patternMap[i + 1].size() - 1];
			int curRow = patternMap[i][patternMap[i].size() - 1];
			int sumRow = previousRow + curRow;

			patternMap[i].push_back(sumRow);
		}

		//Add the last value in the first row to total
		total += patternMap[0][patternMap[0].size() - 1];

		/* Test print all rows
		for (int i = 0; i < patternMap.size(); i++)
		{
			for (int j = 0; j < patternMap[i].size(); j++)
			{
				cout << patternMap[i][j] << " ";
			}
			cout << endl;
		}

		cout << endl;  */

	}

	//Print total"
	cout << "Total = " << total << endl;

	return 0;
}

//Takes a string line, makes the numbers into a vector
vector<int> getValues(string line)
{
	//Vector to return
	vector<int> nums;

	//Keeps track if the character is a number
	bool isNum = false;
	string numToAdd = "";

	for (int i = 0; i < line.length(); i++) 
	{
		char c = line[i];
		if (c >= 48 && c <= 57 || c == 45) {
			isNum = true;
			numToAdd += c;
		}
		
		if (c == ' ' && isNum) {
			isNum = false;
			nums.push_back(stoi(numToAdd));
			numToAdd = "";
		}
	}

	//Checks if last char is a number
	if (isNum) {
		isNum = false;
		nums.push_back(stoi(numToAdd));
		numToAdd = "";
	}

	//Return the vector
	return nums;
}

//Checks if vector is all zeros
bool isZeroRow(vector<int> v) 
{

	bool zeroRow = true;

	for (int i = 0; i < v.size(); i++) {
		
		if (v[i] != 0)
			zeroRow = false;
	}

	return zeroRow;

}