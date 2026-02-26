#include<iostream>
#include<cstdlib> // for rand()
#include<string>
#include <iomanip>

#include "Solitaire.h"

using namespace std;

// ------------------- Solitaire Related Functions ---------------------------

// create the 52 card deck
Solitaire::Solitaire() {
	char suits[] = { 'S', 'H', 'C', 'D' };
	int index = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 13; j++) {
			deck[index++] = Card(j, suits[i]);
		};
	};
};


// display the 52 card deck
void Solitaire::displayCards() {
	cout << "Deck: " << endl;
	for (int i = 0; i < 52; i++) {
		cout << deck[i].rank << deck[i].suit << " ";

		if ((i + 1) % 13 == 0) {
			cout << endl;
		};
	};
};

// gets a random number using rand() | Additionally, rand() uses the seed from srand() declared in main.cpp
int Solitaire::randomInt(int low, int high) {
	return low + (rand() % (high - low + 1));
};

// swaps 2 cards in the 52 card deck - for shuffling purposes (see shuffleDeck() below this function)
void Solitaire::swapCards(Card& a, Card& b) {
	Card temp = a;
	a = b;
	b = temp;
};

// shuffles the 52 card deck - Fisher Yates shuffle, i is incrementing instead of decrementing though
void Solitaire::shuffleDeck() {
	for (int i = 0; i < 52; i++) {
		int j = randomInt(i, 51);
		swapCards(deck[i], deck[j]);
	};
};


// Deals the tableau's for Free Cell Solitaire game
void Solitaire::dealCards() {
	int index = 0;
	int cardsToDeal = 0;

	for (int i = 0; i < 8; i++) {
		// the first 4 tableau's get 7 cards
		if (i < 4) {
			cardsToDeal = 7;
		}
		// the last 4 tableau's get 6 cards
		else {
			cardsToDeal = 6;
		};

		// put cards into a tableau
		for (int j = 0; j < cardsToDeal; j++) {
			tableau[i].push(deck[index++]);
		};
	};
	// display the tableau's
	displayTableau();
};

void Solitaire::displayTableau() {
	int maxHeight = 0;
	const int WIDTH = 12;

	// get max height of the stack(s)
	// needed in case someone adds onto a stack so we need to know how many rows to print
	// e.g. we intially had 7 rows, user added a card to a stack with 7, now we need 8 rows
	for (int col = 0; col < 8; col++) {
		int height = tableau[col].size();
		if (height > maxHeight) {
			maxHeight = height;
		};
	};

	// add pile titles
	cout << setw(WIDTH);
	for (int i = 0; i < 8; i++) {
		cout << left << setw(WIDTH) << "Pile " + to_string(i + 1);
	};
	cout << endl;

	// print each tableau in rows
	for (int row = 1; row <= maxHeight; row++) {
		for (int col = 0; col < 8; col++) {

			// go to the specific row we are printing
			int colHeight = tableau[col].size();
			if (row <= colHeight) {
				Stack tempStack;

				// pop cards into a temporary stack to reach the correct row on the original stack
				for (int i = 0; i < colHeight - row + 1; i++) {
					tempStack.push(tableau[col].peek());
					tableau[col].pop();
				};

				// the card we were looking for
				Card c = tempStack.peek();

				// put everything back into original stack
				while (!tempStack.isEmpty()) {
					tableau[col].push(tempStack.peek());
					tempStack.pop();
				};

				// print card details
				string r;

				if (c.rank == 1) r = "A";
				else if (c.rank == 11) r = "J";
				else if (c.rank == 12) r = "Q";
				else if (c.rank == 13) r = "K";
				else r = to_string(c.rank);

				cout << left << setw(WIDTH) << (r + c.suit);
			}
			else {
				// print an empty string if it was an empty row
				cout << left << setw(WIDTH) << " ";
			};
		};
		cout << endl;
	};
};

// checks moving a card to another tableau from a tableau
bool Solitaire::checkTableauToTableauMove(Card& movedCard, Card& destination) {
	if (movedCard.isRed() == destination.isRed()) {
		return false;
	}
	else if (movedCard.rank != destination.rank - 1) {
		return false;
	}
	else {
		return true;
	}
};

// checks if a card can be moved to a tableau from a free cell
bool Solitaire::checkFreeCellToTableau(Card& movedCard, Stack& tableau) {
	if (tableau.isEmpty()) {
		return true;
	}
	else {
		Card top = tableau.peek();
		if (movedCard.isRed() != top.isRed() && movedCard.rank == top.rank - 1) {
			return true;
		}
		else {
			return false;
		};
	};
};

// checks if a card can be moved to the foundation
bool Solitaire::checkMoveToFoundation(Card& movedCard, Stack& foundation) {
	if (foundation.isEmpty()) {
		if (movedCard.rank == 1) {
			return true;
		}
		else {
			return false;
		};
	};

	Card top = foundation.peek();

	if (movedCard.suit == top.suit && movedCard.rank == top.rank + 1) {
		return true;
	}
	else {
		return false;
	};
};

// checks if a tableau is empty to move a card from a free cell or tableau
bool Solitaire::checkMoveToEmptyStack(Stack& stack) {
	if (stack.isEmpty()) {
		return true;
	}
	else {
		return false;
	};
};

void Solitaire::gamePlay() {

};