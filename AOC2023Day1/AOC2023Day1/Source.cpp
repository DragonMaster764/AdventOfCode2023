#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctype.h>
using namespace std;

int main() 
{

	fstream fileReader;

	fileReader.open("Input.txt");

	int total = 0;

	if (fileReader.is_open()) 
	{

		string inputLine;

		while (getline(fileReader, inputLine))
		{
			vector<int> numbers;

			for (int i = 0; i < inputLine.size(); i++) {
				numbers.push_back(0);
			}

			for (int i = 0; i < inputLine.length(); i++) {
				char c = inputLine[i];

				if (isdigit(c)) {
					numbers[i] = int(c - '0');
				}

			}

			if (inputLine.find("one") != string::npos) {
				int strIndex = inputLine.find("one");
				numbers[strIndex] = 1;
			}
			if (inputLine.rfind("one") != string::npos) {
				int strIndex = inputLine.rfind("one");
				numbers[strIndex] = 1;
			}
			if (inputLine.find("two") != string::npos) {
				int strIndex = inputLine.find("two");
				numbers[strIndex] = 2;
			}
			if (inputLine.rfind("two") != string::npos) {
				int strIndex = inputLine.rfind("two");
				numbers[strIndex] = 2;
			}
			if (inputLine.find("three") != string::npos) {
				int strIndex = inputLine.find("three");
				numbers[strIndex] = 3;
			}
			if (inputLine.rfind("three") != string::npos) {
				int strIndex = inputLine.rfind("three");
				numbers[strIndex] = 3;
			}
			if (inputLine.find("four") != string::npos) {
				int strIndex = inputLine.find("four");
				numbers[strIndex] = 4;
			}
			if (inputLine.rfind("four") != string::npos) {
				int strIndex = inputLine.rfind("four");
				numbers[strIndex] = 4;
			}
			if (inputLine.find("five") != string::npos) {
				int strIndex = inputLine.find("five");
				numbers[strIndex] = 5;
			}
			if (inputLine.rfind("five") != string::npos) {
				int strIndex = inputLine.rfind("five");
				numbers[strIndex] = 5;
			}
			if (inputLine.find("six") != string::npos) {
				int strIndex = inputLine.find("six");
				numbers[strIndex] = 6;
			}
			if (inputLine.rfind("six") != string::npos) {
				int strIndex = inputLine.rfind("six");
				numbers[strIndex] = 6;
			}
			if (inputLine.find("seven") != string::npos) {
				int strIndex = inputLine.find("seven");
				numbers[strIndex] = 7;
			}
			if (inputLine.rfind("seven") != string::npos) {
				int strIndex = inputLine.rfind("seven");
				numbers[strIndex] = 7;
			}
			if (inputLine.find("eight") != string::npos) {
				int strIndex = inputLine.find("eight");
				numbers[strIndex] = 8;
			}
			if (inputLine.rfind("eight") != string::npos) {
				int strIndex = inputLine.rfind("eight");
				numbers[strIndex] = 8;
			}
			if (inputLine.find("nine") != string::npos) {
				int strIndex = inputLine.find("nine");
				numbers[strIndex] = 9;
			}
			if (inputLine.rfind("nine") != string::npos) {
				int strIndex = inputLine.rfind("nine");
				numbers[strIndex] = 9;
			}


			string finalNumToAdd = "";

			int firstNum;
			int lastNum;

			for (int i = 0; i < numbers.size(); i++) {
				if (numbers[i] != 0) {
					firstNum = numbers[i];
					break;
				}
			}

			for (int i = numbers.size() - 1; i >= 0; i--) {
				if (numbers[i] != 0) {
					lastNum = numbers[i];
					break;
				}
			}

			finalNumToAdd = to_string(firstNum) + to_string(lastNum);

			total = total + stoi(finalNumToAdd);
		}

	}
	else {
		cout << "There was an error" << endl;
	}

	fileReader.close();

	cout << "The total is: " << total << endl;

	return 0;
}