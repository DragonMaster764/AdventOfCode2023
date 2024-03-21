#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<long long> getNumbers(string line);

int main()
{
	//Keep track of the total
	int total = 1;

	//File reader
	fstream fileReader("Input.txt");
	string curLine;
	getline(fileReader, curLine);

	//Get the times
	vector<long long> times = getNumbers(curLine);

	/*Testing print
	for (int i = 0; i < times.size(); i++)
		cout << times[i] << " "; */

		//Get the Distances
	getline(fileReader, curLine);
	vector<long long> distances = getNumbers(curLine);

	//For each race try finding winning solutions
	for (int i = 0; i < times.size(); i++)
	{
		//These are the race parameters
		long long raceTime = times[i];
		long long raceDistance = distances[i];

		//Keeps track of all winnable solutions
		long long wins = 0;

		//Starts at one because 0 wont make the boat move
		long long buttonHoldTime = 1;

		//Checks every single amount of time you could hold the button
		for (buttonHoldTime; buttonHoldTime < raceTime; buttonHoldTime++)
		{
			//First subtract the time left after holding the button
			long long timeLeft = raceTime - buttonHoldTime;

			//To know how far you go, multiply hold time by time left
			long long distanceTravelled = timeLeft * buttonHoldTime;

			//Check to see if boat made it past the record 
			if (distanceTravelled > raceDistance)
				wins++;

		}

		//Multiplies the amount of wins with the total (if not zero)
		if (wins != 0)
			total *= wins;


	}

	//Print the total
	cout << "Total: " << total << endl;


	return 0;
}


//Grabs all the numbers in the line, and puts them into a vector
vector<long long> getNumbers(string line)
{
	vector<long long> allNums;

	string nums = line.substr(line.find(':') + 1);

	bool isNum = false;
	string numToAdd = "";

	//cout << nums << endl;

	for (int i = 0; i < nums.length(); i++)
	{
		char c = nums[i];

		if (c >= 48 && c <= 57)
		{
			isNum = true;
			numToAdd += c;
		}

		/*if (c == ' ' && isNum) {
			isNum = false;
			allNums.push_back(stoi(numToAdd));
			numToAdd = "";
		} */
	}

	if (isNum) {
		isNum = false;
		allNums.push_back(stoll(numToAdd));
		numToAdd = "";
	}

	return allNums;
}