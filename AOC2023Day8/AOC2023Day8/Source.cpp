#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Network {
	string name, left, right;
};

Network findNode(const vector<Network>& map, string n);

int main()
{
	//Opens the file
	fstream fileReader("Input.txt");

	// Gets the pattern of steps needed
	string patternLine;
	getline(fileReader, patternLine);
	
	//Seperates each step into chars L and R
	vector<char> pattern;
	for (int i = 0; i < patternLine.length(); i++)
		pattern.push_back(patternLine[i]);

	//Make the full map with each network
	vector<Network> map;

	string curLine;


	while (getline(fileReader, curLine))
	{
		//Skips blank lines
		if (curLine.empty())
			continue;

		//Makes a new node
		Network node;
		node.name = curLine.substr(0, 3);
		node.left = curLine.substr(curLine.find('(') + 1, 3);
		node.right = curLine.substr(curLine.find(')') - 3, 3);

		//Adds it to map
		map.push_back(node);

	}

	//Close file reading
	fileReader.close();

	//Keeps track of steps needed
	int steps = 0;

	//Gets a starting node
	Network curNode = findNode(map, "AAA");

	//R and L pattern icrementor 
	int rlIndex = 0;

	//Keeps doing steps until ZZZ is reached
	while (curNode.name != "ZZZ")
	{
		char rl = pattern[rlIndex];

		//What node to search for next
		string nextNode;
		if (rl == 'R')
			nextNode = curNode.right;
		else
			nextNode = curNode.left;

		//Find the next node
		curNode = findNode(map, nextNode);

		//Count one step
		steps++;

		//Increment the rl index, but if it is too big, go back to start
		rlIndex++;

		if (rlIndex == pattern.size())
			rlIndex = 0;
	}

	//Print out number of steps
	cout << "It took " << steps << " steps." << endl;

	return 0;
}

//Finds the node in the map by name, returns the node
Network findNode(const vector<Network> & map, string n) 
{
	Network node;

	for (int i = 0; i < map.size(); i++)
	{
		if (map[i].name == n) 
		{
			node = map[i];
			return node;
		}
	}

	return node;
}