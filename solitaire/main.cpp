//#include <iomanip>
#include <iostream>
#include <ctime>

#include "Solitaire.h"

using namespace std;

int main() {
	// random uses this seed based on your time (in seconds) to shuffle the deck
	srand(static_cast<unsigned int>(time(nullptr)));

	Solitaire game;
	game.displayCards();

	game.shuffleDeck();
	cout << "\nShuffled ";
	game.displayCards();

	cout << "\nFinn and Leo's Solitaire Game - Free Cell" << endl;
	cout << "-----------------------------------------------------------------------" << endl;

	game.dealCards();

	return 0;
};