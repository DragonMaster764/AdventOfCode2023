#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void numSearch(vector<long long int> & numHolder, string s);
void fillMap(vector<vector<long long>>& map, string & mapLine, fstream & fileReader);

int main()
{

	//Open the file Input.txt
	fstream fileReader;
	fileReader.open("Input.txt");

	//Get the seed ranges
	vector<long long int> seedRanges;

	//Get the string of seeds
	string seedLine;
	getline(fileReader, seedLine);

	//Grab the numbers from string
	numSearch(seedRanges, seedLine);

	//Get the least # seed
	long long int minSeed = 9999999999999;

	////////////////////////////////////
	//       Makes each map          //
	///////////////////////////////////

	//Map 1
	vector<vector<long long>> map1;

	string mapLine;
	getline(fileReader, mapLine);
	getline(fileReader, mapLine);
	getline(fileReader, mapLine); //This is the first set of numbers

	fillMap(map1, mapLine, fileReader);


	//Map 2
	vector<vector<long long>> map2;
	getline(fileReader, mapLine);
	getline(fileReader, mapLine); //This is the first set of numbers
	
	fillMap(map2, mapLine, fileReader);
	
	
	//Map 3
	vector<vector<long long>> map3;
	getline(fileReader, mapLine);
	getline(fileReader, mapLine); //This is the first set of numbers

	fillMap(map3, mapLine, fileReader);


	//Map 4
	vector<vector<long long>> map4;
	getline(fileReader, mapLine);
	getline(fileReader, mapLine); //This is the first set of numbers

	fillMap(map4, mapLine, fileReader);


	//Map 5
	vector<vector<long long>> map5;
	getline(fileReader, mapLine);
	getline(fileReader, mapLine); //This is the first set of numbers

	fillMap(map5, mapLine, fileReader);


	//Map 6
	vector<vector<long long>> map6;
	getline(fileReader, mapLine);
	getline(fileReader, mapLine); //This is the first set of numbers

	fillMap(map6, mapLine, fileReader);


	//Map 7
	vector<vector<long long>> map7;
	getline(fileReader, mapLine);
	getline(fileReader, mapLine); //This is the first set of numbers

	fillMap(map7, mapLine, fileReader);

	//All maps
	vector<vector<vector<long long>>> allMaps = { map1, map2, map3, map4, map5, map6, map7 };

	//Say maps created!
	cout << "All maps created! :)" << endl;


	///////////////////////////////////


	//Edit so each seed and range gets done individually
	for (int i = 0; i < seedRanges.size(); i += 2)
	{
		//Makes an array of all the seeds
		vector<long long int> seeds;

		long long firstSeedNum = seedRanges[i];
		long long range = seedRanges[i + 1];

		for (int j = 0; j < range; j++)
		{
			seeds.push_back(firstSeedNum + j);
		}

		cout << "Seeds Populated" << endl;



		//For loops checking for maps and mapping the values of the seeds
		for (int i = 0; i < 7; i++)
		{

			vector<vector<long long>> curMap = allMaps[i];


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
			std::cout << "Seeds mapped" << endl;

		}

		//Print the new seed numbers
		std::cout << "All seeds mapped" << endl;


		//Gets the minimum seed #
		for (int i = 0; i < seeds.size(); i++)
		{
			if (seeds[i] < minSeed)
			{
				minSeed = seeds[i];
			}
		}


	}

	//Print out minimum seed
	std::cout << "Minimum: " << minSeed << endl;
	
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

//Make vectors with <destination start, destination end, source start, source end>
void fillMap(vector<vector<long long>>& map, string & mapLine, fstream & fileReader)
{
	while (mapLine != "" && fileReader.peek() != EOF)
	{
		vector<long long int> currentRange;
		numSearch(currentRange, mapLine);

		//Format should be destination start, source start, range
		long long int rangeToAdd = currentRange[2] - 1;

		vector<long long int> rangeToAddToMap = { currentRange[0], currentRange[0] + rangeToAdd, currentRange[1], currentRange[1] + rangeToAdd };

		//Add range to map
		map.push_back(rangeToAddToMap);

		//Do next line
		getline(fileReader, mapLine);

	}
}