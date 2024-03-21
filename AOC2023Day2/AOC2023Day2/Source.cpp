#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void checkMarbleColors(string round, bool& isGamePos, int& minPRed, int& minPGreen, int& minPBlue);

int main() 
{
	// Make a stream to read file
	fstream readFile;
	readFile.open("Input.txt");

	//Game number storage
	int gameNum = 1;

	// Total storage
	int total = 0;
	int totalPowers = 0;

	// Keep checking file till empty

	string curLine;

	while (getline(readFile, curLine)) 
	{

		//Sets Game Possible to True
		bool isGamePos = true;

		//Get rid of game#: part of string
		string noGame = curLine.substr(curLine.find(':') + 1, curLine.size() - 1);

		string roundsLeft =  noGame;
		string curRound = "";

		//Sets up the minimum cubes needed for game to be possible
		int minPosRed = 0;
		int minPosGreen = 0;
		int minPosBlue = 0;

		while (roundsLeft.find(";") != string::npos) {

			// Gets the curent round round
			curRound = roundsLeft.substr(0, roundsLeft.find(';'));

			//Checks the round
			checkMarbleColors(curRound, isGamePos, minPosRed, minPosGreen, minPosBlue);

			//Moves rounds left up a round
			roundsLeft = roundsLeft.substr(roundsLeft.find(";") + 1);


		}

		//Completes the final round
		string finalRound = roundsLeft;

		//Checks finalRound
		checkMarbleColors(finalRound, isGamePos, minPosRed, minPosGreen, minPosBlue);

		//if game is possible, add to total the game number
		if (isGamePos) {
			total += gameNum;
		}

		//Gets the game power number and adds it to total
		int gamePow = minPosRed * minPosGreen * minPosBlue;
		totalPowers += gamePow;


		//Up the game number
		gameNum++;


	}


	//Print out the totals
	cout << "Total is: " << total << endl;
	cout << "Power total: " << totalPowers << endl;

	return 0;
}
 
void checkMarbleColors(string round, bool & isGamePos, int & minPRed, int & minPGreen, int & minPBlue)
{

	// Max cube storage
	int maxRed = 12;
	int maxGreen = 13;
	int maxBlue = 14;

	//String storing the number of cubes
	string numRed = "";
	string numGreen = "";
	string numBlue = "";

	//Check for marble colors
	if (round.find("red") != string::npos) {

		//Checks if the for loops finds a number
		bool foundANum = false;

		//check entire string for the number
		for (int i = round.find("red"); i >= 0; i--) {

			//Gets current char
			char curChar = round.at(i);

			//Checks if it is a number
			if (isdigit(curChar)) {

				//Changes the string of the number of red cubes to inlcude the character
				numRed = curChar + numRed;
				foundANum = true;
			}

			//If a number has been found, and there is a space, stop gathering chars
			if (foundANum && curChar == ' ') {
				break;
			}

		}
	}

	if (round.find("green") != string::npos) {

		//Get the number of red
		bool foundANum = false;


		//check entire string for the number
		for (int i = round.find("green"); i >= 0; i--) {

			//Gets current char
			char curChar = round.at(i);

			//Checks if it is a number
			if (isdigit(curChar)) {

				//Changes the string of the number of red cubes to inlcude the character
				numGreen = curChar + numGreen;
				foundANum = true;
			}

			//If a number has been found, and there is a space, stop gathering chars
			if (foundANum && curChar == ' ') {
				break;
			}

		}
	}

	if (round.find("blue") != string::npos) {

		//Get the number of red
		bool foundANum = false;


		//check entire string for the number
		for (int i = round.find("blue"); i >= 0; i--) {

			//Gets current char
			char curChar = round.at(i);

			//Checks if it is a number
			if (isdigit(curChar)) {

				//Changes the string of the number of red cubes to inlcude the character
				numBlue = curChar + numBlue;
				foundANum = true;
			}

			//If a number has been found, and there is a space, stop gathering chars
			if (foundANum && curChar == ' ') {
				break;
			}

		}
	}

	//If the number of cubes grabbed is > the max cubes in the bag, the game is impossible
	if (numRed != "") {
		if (stoi(numRed) > maxRed) {
			isGamePos = false;
		}

		if (stoi(numRed) > minPRed) {
			minPRed = stoi(numRed);
		}
	}
	if (numGreen != "") {
		if (stoi(numGreen) > maxGreen) {
			isGamePos = false;
		}

		if (stoi(numGreen) > minPGreen) {
			minPGreen = stoi(numGreen);
		}
	}
	if (numBlue != "") {
		if (stoi(numBlue) > maxBlue) {
			isGamePos = false;
		}

		if (stoi(numBlue) > minPBlue) {
			minPBlue = stoi(numBlue);
		}
	}
}