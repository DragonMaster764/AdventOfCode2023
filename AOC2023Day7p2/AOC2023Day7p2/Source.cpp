#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int getHandStrength(string cards);

struct Hand {
	string cards;
	int bid;
	int strength;

	//Returs the address to insert the hand
	bool checkTies(const vector<Hand>& hands, int curIndex)
	{
		//The hierarchy of letters
		vector<char> cardScores = { 'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};

		Hand otherHand = hands[curIndex];

		//Check each letter
		for (int i = 0; i < 5; i++)
		{
			char curCard = cards[i];
			char otherHandCard = otherHand.cards[i];

			int curCardIndex = -1;
			int otherHandCardIndex = -1;

			//Goes through each letter in card scores
			for (int j = 0; j < cardScores.size(); j++)
			{
				if (curCard == cardScores[j])
					curCardIndex = j;

				if (otherHandCard == cardScores[j])
					otherHandCardIndex = j;
			}

			//Checks to see which one is greater (the one that has the smallest index 
			//since the vector has strengths from largest -> smallest
			if (curCardIndex < otherHandCardIndex) {
				return true;
			}
			else if (curCardIndex > otherHandCardIndex) {
				return false;
			}

			//If it is equal, go to next letter
		}


	}
};

int main()
{
	//Total holder
	int total = 0;

	//File Reader
	fstream fileReader("Input.txt");

	//Holder of all the hands in order
	vector<Hand> hands;

	//Get the first hand
	string curLine;
	getline(fileReader, curLine);

	//Fill in the info for the hand
	Hand hand1;
	int bid = stoi(curLine.substr(curLine.find(" ") + 1));
	hand1.bid = bid;
	hand1.cards = curLine.substr(0, curLine.find(" "));

	//Get the strength of card (1 - 7)
	hand1.strength = getHandStrength(hand1.cards);

	//Put hand in vector
	hands.push_back(hand1);


	//Goes through the rest of the cards
	while (getline(fileReader, curLine))
	{
		Hand nextHand;
		bid = stoi(curLine.substr(curLine.find(" ") + 1));
		nextHand.bid = bid;
		nextHand.cards = curLine.substr(0, curLine.find(" "));

		//Get the strength of card (1 - 7)
		nextHand.strength = getHandStrength(nextHand.cards);

		/* cout << nextHand.strength << endl;
		if (nextHand.strength == 6)
			cout << "Four of a kind: " << nextHand.cards << " " << nextHand.strength << endl;

		if (nextHand.strength == 5)
			cout << "Full House: " << nextHand.cards << " " << nextHand.strength << endl; */

		int initalHandSize = hands.size();
		bool addedToHands = false;

		//Checks every other hand to see if it's strength is higher
		for (int i = 0; i < initalHandSize; i++)
		{

			//Checks if they are eqaul, returns if one is greater than the other
			//Then checks if the hand is greater, and too insert at the address
			//If it is at the end, add the hand at the end
			if (nextHand.strength == hands[i].strength) {
				bool isHandGreater = false;
				isHandGreater = nextHand.checkTies(hands, i);

				if (isHandGreater) {
					hands.insert(hands.begin() + i, nextHand);
					addedToHands = true;
					break;
				}


			}
			else if (nextHand.strength > hands[i].strength) {
				hands.insert(hands.begin() + i, nextHand);
				addedToHands = true;
				break;

			}

		}

		if (!addedToHands)
			hands.push_back(nextHand);


	}



	//Count the totals
	int curRank = 1;

	for (int i = hands.size() - 1; i >= 0; i--)
	{
		cout << hands[i].cards << " " << hands[i].bid << " " << curRank << " " << i << endl;
		total += hands[i].bid * curRank;
		curRank++;
	}

	//Prints out the total
	cout << "Total = " << total << endl;


	return 0;
}

int getHandStrength(string cards)
{

	vector<char> uniqueCards = { cards[0] };

	//Checks the hand for each unique card
	for (int i = 0; i < cards.length(); i++)
	{
		char card = cards[i];
		if (!(find(uniqueCards.begin(), uniqueCards.end(), card) != uniqueCards.end()))
		{
			uniqueCards.push_back(card);
		}
	}

	//Find the jokers
	int numberOfJokers = 0;
	//Checks the hand for each joker card
	for (int i = 0; i < cards.length(); i++)
	{
		char card = cards[i];
		if (card == 'J')
			numberOfJokers++;
	}


	//Count how many of each card (and what they would be + jokers)
	vector<int> cardCounts;
	vector<int> cardCountsJokers;

	for (int i = 0; i < uniqueCards.size(); i++)
	{
		int count = 0;

		for (int j = 0; j < cards.length(); j++)
		{
			if (cards[j] == uniqueCards[i]) {
				count++;
			}
		}

		cardCounts.push_back(count);
		cardCountsJokers.push_back(count + numberOfJokers);
	}

	/* cout << "Unique Cards: " << uniqueCards.size() << endl;

	for (int i = 0; i < cardCounts.size(); i++)
		cout << cardCounts[i] << " ";

	cout << endl; */

	//Checks each hand type
	if (uniqueCards.size() == 1 || (uniqueCards.size() == 2 && numberOfJokers >= 1)) {  //Start back here
		return 7;
	}
	else if (uniqueCards.size() == 2 || (uniqueCards.size() == 3 && numberOfJokers >= 1)) {

		//Check for full house or four of a kind
		if (find(cardCounts.begin(), cardCounts.end(), 4) != cardCounts.end() 
			|| find(cardCountsJokers.begin(), cardCountsJokers.end(), 4) != cardCountsJokers.end())
			return 6;
		else
			return 5;

	}
	else if (uniqueCards.size() == 3 || (uniqueCards.size() == 4 && numberOfJokers >= 1)) {

		//check for 3 of a kind or two pair
		if (find(cardCounts.begin(), cardCounts.end(), 3) != cardCounts.end()
			|| find(cardCountsJokers.begin(), cardCountsJokers.end(), 3) != cardCountsJokers.end())
			return 4;
		else
			return 3;
	}
	else if (uniqueCards.size() == 4 || (uniqueCards.size() == 5 && numberOfJokers >= 1)) {
		return 2;
	}
	else {
		return 1;
	}

}

