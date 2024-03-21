#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void numSearch(vector<long long int> & numHolder, string s);

int main()
{

	//Open the file Input.txt
	fstream fileReader;
	fileReader.open("Input.txt");

	//Get the seed values
	vector<long long int> seeds;

	//Get the string of seeds
	string seedLine;
	getline(fileReader, seedLine);

	//Grab the numbers from string
	numSearch(seeds, seedLine);

	//Prints the seeds

	cout << "Seeds: ";

	for (int i = 0; i < seeds.size(); i++)
	{
		cout << seeds[i] << " ";
	}

	cout << endl;


	//Stores current line of file
	string curLine = ""; 

	getline(fileReader, curLine);

	//Go to the first map
	while (curLine == "") {
		getline(fileReader, curLine);

		//Do Nothing
	}

	//For loops checking for maps and mapping the values of the seeds
	for (int i = 0; i < 7; i++) 
	{
		//Get the map ranges in format <destination start, destination end, source start, source end>
		vector<vector<long long int>> curMap;

		//Cur line should be map title rn

		//Should be first number range
		getline(fileReader, curLine);
		cout << curLine << endl;

		while (curLine != ""  && fileReader.peek() != EOF)
		{
			vector<long long int> currentRange;
			numSearch(currentRange, curLine);

			//Format should be destination start, source start, range
			long long int rangeToAdd = currentRange[2] - 1;

			vector<long long int> rangeToAddToMap = { currentRange[0], currentRange[0] + rangeToAdd, currentRange[1], currentRange[1] + rangeToAdd };

			//Add range to map
			curMap.push_back(rangeToAddToMap);

			//Do next line
			getline(fileReader, curLine);

			// cout << curLine << endl;
		}

		cout << endl << endl;

		//Change seed numbers (if needed)
		for (int j = 0; j < seeds.size(); j++)
		{
			//Check each range to see if the seed should change
			for (int k = 0; k < curMap.size(); k++)
			{
				long long int sourceMin = curMap[k][2];
				long long int sourceMax = curMap[k][3];

				if (seeds[j] >= sourceMin && seeds[j] <= sourceMax)
				{
					//Get the diff between number and minimum
					long long int difference = seeds[j] - sourceMin;
					long long int numberToChangeTo = curMap[k][0] + difference;

					//Change seed #
					seeds[j] = numberToChangeTo;

					break;
				}
			}

		}

		//Print the new seed numbers
		cout << "Seeds mapped: ";

		for (int i = 0; i < seeds.size(); i++)
		{
			cout << seeds[i] << " ";
		}

		cout << endl << endl;

		//Go to next map
		while (curLine == "") {
			getline(fileReader, curLine);

			//Do Nothing
		}
	}

	//Print the new seed numbers
	cout << "Seeds fully mapped: ";

	for (int i = 0; i < seeds.size(); i++)
	{
		cout << seeds[i] << " ";
	}

	cout << endl;

	//Get the least # seed
	long long int minSeed = 99999999999;

	for (int i = 0; i < seeds.size(); i++)
	{
		if (seeds[i] < minSeed)
		{
			minSeed = seeds[i];
		}
	}

	//Print out minimum seed
	cout << "Minimum: " << minSeed << endl;

	return 0;
}


//Searches for numbers in the line of the input
void numSearch(vector<long long int> & numHolder, string s)
{
	bool isNum = false;
	string curNum = "";

	for (int i = 0; i < s.size(); i++) {
		char c = s[i];

		if (c >= 48 && c <= 57)
		{
			curNum += c;
			isNum = true;
		}

		if (c == ' ' && isNum)
		{
			isNum = false;

			long long numToAdd = stoll(curNum);

			numHolder.push_back(numToAdd);
			curNum = ""; 
		}
	}

	if (isNum) {
		isNum = false;
		numHolder.push_back(stoll(curNum));
		curNum = "";

	}
}