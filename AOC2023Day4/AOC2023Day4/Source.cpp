#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	// Open file reader to read the input
	fstream fileReader;
	fileReader.open("Input.txt"); 

	// Stores the total 
	int total = 0;

	// Stores the current line being read
	string curLine;

	//Number of scratch cards
	vector<int> copiesOfCards;

	//Checks each line 
	while (getline(fileReader, curLine))
	{
		copiesOfCards.push_back(1);
	}

	//Current card
	int curCard = 1;

	fileReader.close();
	fileReader.open("Input.txt");

	//Checks each line 
	while (getline(fileReader, curLine))
	{
		//Get rid of card #
		string sCard = curLine.substr(curLine.find(":") + 1, curLine.size() - 1);

		//Winning numbers
		vector<string> winNumbers;

		//Checks for numbers
		bool isNumber = false;
		string number = "";

		for (int i = 0; i < sCard.size(); i++)
		{
			char curChar = sCard[i];

			if (curChar >= 48 && curChar <= 57)
			{
				isNumber = true;
				number += curChar;
			}

			if (curChar == ' ' && isNumber == true)
			{
				isNumber = false;
				winNumbers.push_back(number);
				number = "";
			}

			if (curChar == '|') 
			{
				break;
			}
		}

		if (isNumber) {
			winNumbers.push_back(number);
		}

		//Do the same thing but with the other numbers

		number = "";

		vector<string> otherNums;

		isNumber = false;

		for (int i = sCard.find('|') + 1; i < sCard.size(); i++)
		{
			char curChar = sCard[i];

			if (curChar >= 48 && curChar <= 57)
			{
				isNumber = true;
				number += curChar;
			}

			if (curChar == ' ' && isNumber == true)
			{
				isNumber = false;
				otherNums.push_back(number);
				number = "";
			}

		}

		if (isNumber) {
			otherNums.push_back(number);
		}

		//Check for winning numbers
		int numOfMatches = 0;

		for (int i = 0; i < otherNums.size(); i++)
		{
			string numToCheck = otherNums[i];

			for (int j = 0; j < winNumbers.size(); j++)
			{
				if (numToCheck == winNumbers[j]) {
					numOfMatches++;
				}
			}
		}

		//Index of cards
		vector<int> indexesOfCards;
		
		if (numOfMatches >= 1)
		{
			for (int i = 1; i <= numOfMatches; i++) {
				indexesOfCards.push_back(i);
			}

			int indexOfCurCard = curCard - 1;
			int copiesOfCurCard = copiesOfCards[indexOfCurCard];

			//Add copies of cards
			for (int i = 0; i < indexesOfCards.size(); i++)
			{
				int curCopies = copiesOfCards[indexOfCurCard + indexesOfCards[i]];

				if (indexOfCurCard + indexesOfCards[i] < copiesOfCards.size())
					copiesOfCards[indexOfCurCard + indexesOfCards[i]] = curCopies + copiesOfCurCard;

			}
		}
		

		//Calculate what to add
		if (numOfMatches >= 1)
			total += pow(2, numOfMatches - 1);

		curCard++;

	}

	//Print out total
	cout << "Total: " << total << endl; 

	//Num cards
	int numOfCards = 0;

	for (int i = 0; i < copiesOfCards.size(); i++)
	{
		numOfCards += copiesOfCards[i];
	}

	cout << "Copies: " << numOfCards << endl;

	return 0;
}