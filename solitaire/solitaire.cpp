#include <iostream>
#include <cstdlib> // for rand()
#include <string>
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
	// display the board
	//displayBoard();
};

// converts card details into a string for printing purposes
string Solitaire::cardToString(const Card& c) {
	string r;

	if (c.rank == 1) r = "A";
	else if (c.rank == 11) r = "J";
	else if (c.rank == 12) r = "Q";
	else if (c.rank == 13) r = "K";
	else r = to_string(c.rank);

	return r + c.suit;
};

// print out free cells, foundations, and tableau's
void Solitaire::displayBoard() {
	const int WIDTH = 12;

	// FREE CELLS
	cout << left << setw(WIDTH) << "Free Cells";
	for (int i = 0; i < 4; i++) {
		string cardFreeCell;
		if (freeCell[i].isEmpty()) {
			cardFreeCell = "-"; // sets it to '-' if there was no card to display
		}
		else {
			cardFreeCell = cardToString(freeCell[i].peek()); // get card
		};
		cout << left << setw(WIDTH) << cardFreeCell; // display card
	};


	// FOUNDATIONS
	cout << left << setw(WIDTH) << "Foundations";
	for (int i = 0; i < 4; i++) {
		string cardFoundation;
		if (foundation[i].isEmpty()) {
			cardFoundation = "-"; // sets it to '-' if there was no card to display
		}
		else {
			cardFoundation = cardToString(foundation[i].peek()); // get card
		};
		cout << left << setw(WIDTH) << cardFoundation; // display card
	};

	cout << endl;
	cout << "----------------------------------------------------------------------------------------------------------------" << endl;

	// TABLEAU's
	// get max height of the stack(s)
	// needed in case someone adds onto a stack so we need to know how many rows to print
	// e.g. we intially had 7 rows, user added a card to a stack with 7, now we need 8 rows
	int maxHeight = 0;
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

				cout << left << setw(WIDTH) << cardToString(c);
			}
			else {
				// print an empty string if it was an empty row
				cout << left << setw(WIDTH) << " ";
			};
		};
		cout << endl;
	};
	cout << "----------------------------------------------------------------------------------------------------------------" << endl;
};

// checks moving a card to another tableau from a tableau
bool Solitaire::checkTableauToTableauMove(const Card& movedCard, const Card& destination) {
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
bool Solitaire::checkFreeCellToTableau(const Card& movedCard, const Stack& tableau) {
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
bool Solitaire::checkMoveToFoundation(const Card& movedCard, const Stack& foundation) {
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

// checks if a tableau or free cell is empty to move a card from a free cell or tableau
bool Solitaire::checkMoveToEmptyStack(const Stack& stack) {
	if (stack.isEmpty()) {
		return true;
	}
	else {
		return false;
	};
};

bool Solitaire::moveCard(char whereType, int whereIndex, char destinationType, int destinationIndex) {
	Card movedCard;

	// user told us earlier what to move from where -- use that here
	// T = Tableau | C = Free cell | None for foundation - moving from foundation is illegal in this solitiare version
	if (whereType == 'T') {
		if (tableau[whereIndex].isEmpty()) {
			return false; // no card to move
		}
		else {
			movedCard = tableau[whereIndex].peek(); // card to move
		};
	}
	else if (whereType == 'C') {
		if (freeCell[whereIndex].isEmpty()) {
			return false; // no card to move
		}
		else {
			movedCard = freeCell[whereIndex].peek(); // card to move
		};
	}
	else {
		return false; // could not find card -- user input was most likely wrong
	};

	bool legalMove = false;

	// check for tableau legal moves
	if (destinationType == 'T') {
		// check for empty tableau - always legal to move if moving 1 card
		if (tableau[destinationIndex].isEmpty()) {
			legalMove = checkMoveToEmptyStack(tableau[destinationIndex]);
		}
		else {
			legalMove = checkTableauToTableauMove(movedCard, tableau[destinationIndex].peek());
		};
	}
	// check for foundation legal moves
	else if (destinationType == 'F') {
		legalMove = checkMoveToFoundation(movedCard, foundation[destinationIndex]);
	}
	// check for free cell legal moves
	else if (destinationType == 'C') {
		legalMove = checkMoveToEmptyStack(freeCell[destinationIndex]);
	}
	// destination inputted wrong
	else {
		return false;
	};

	// check if move was legal
	if (!legalMove) {
		return false;
	}
	else {
		// move the card since move was legal
		// remove card from where we started
		if (whereType == 'T') {
			tableau[whereIndex].pop();
		}
		else if (whereType == 'C') {
			freeCell[whereIndex].pop();
		}

		// add card into destination stack
		if (destinationType == 'T') { // tableau
			tableau[destinationIndex].push(movedCard);
		}
		else if (destinationType == 'C') { // free cell
			freeCell[destinationIndex].push(movedCard);
		}
		else if (destinationType == 'F') { // foundation
			foundation[destinationIndex].push(movedCard);
		};

		return true; // card was moved
	};
};

bool Solitaire::checkWin() {
	for (int i = 0; i < 4; i++) {
		if (foundation[i].size() != 13) {
			return false;
		};
	};
	return true;
};

void Solitaire::gamePlay() {
	// C = Free cell | T = Tableau | F = Foundation
	char whereType;
	int whereIndex;
	char destinationType;
	int destinationIndex;

	while (true) {
		// displays the game board (will also display the updated version if a card was moved)
		displayBoard();

		//
		// get which pile or free cell they want to move a card from
		//
		cout << "Where do you want to move a card from (T - Tableau | C - Free Cell | Q - Quit)?" << endl;
		cin >> whereType;
		whereType = toupper(whereType);

		if (whereType == 'Q') {
			cout << "Thanks for playing!" << endl;
			break;
		}
		else {
			while (whereType != 'T' && whereType != 'C') { // input validation
				cout << "Invalid input. Enter T for Tableau or C for Free Cell: ";
				cin >> whereType;
				whereType = toupper(whereType);
			};

			if (whereType == 'T') { // tableau
				cout << "From which pile (1-8)?" << endl;
				cin >> whereIndex;
				while (cin.fail() || whereIndex > 8 || whereIndex < 1) { // input validation
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Enter an integer from 1-8: ";
					cin >> whereIndex;
				}
			}
			else { // free cell
				cout << "From which free cell (1-4 from left to right)?" << endl;
				cin >> whereIndex;
				while (cin.fail() || whereIndex > 4 || whereIndex < 1) { // input validation
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Enter an integer from 1-4: ";
					cin >> whereIndex;
				}
			};

			//
			// get where they want to move the card to
			//
			cout << "Move the card where (T - Tableau | F - Foundation | C - Free Cell" << endl;
			cin >> destinationType;
			destinationType = toupper(destinationType);

			while (destinationType != 'T' && destinationType != 'F' && destinationType != 'C') {
				cout << "Invalid input. Enter T for Tableau, F for Foundation, or C for Free Cell: ";
				cin >> destinationType;
				destinationType = toupper(destinationType);
			};

			if (destinationType == 'T') { // tableau
				cout << "Move the card to which pile (1-8)?" << endl;
				cin >> destinationIndex;
				while (cin.fail() || destinationIndex > 8 || destinationIndex < 1) { // input validation
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Enter an integer from 1-8: ";
					cin >> destinationIndex;
				}
			}
			else if (destinationType == 'F') { // foundation
				cout << "Move the card to which foundation (1-4 from left to right)" << endl;
				cin >> destinationIndex;
				while (cin.fail() || destinationIndex > 4 || destinationIndex < 1) { // input validation
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Enter an integer from 1-4: ";
					cin >> destinationIndex;
				}
			}
			else { // free cell
				cout << "Move the card to which free cell (1-4 from left to right)" << endl;
				cin >> destinationIndex;
				while (cin.fail() || destinationIndex > 4 || destinationIndex < 1) { // input validation
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Enter an integer from 1-4: ";
					cin >> destinationIndex;
				};
			};
		};

		//
		// check for legal move
		//
		if (moveCard(whereType, whereIndex - 1, destinationType, destinationIndex - 1)) {
			cout << "Move successful!" << endl;
			if (checkWin()) {
				displayBoard();
				cout << "Congrats! You have won!" << endl;
				break;
			};
		}
		else {
			cout << "Illegal move!" << endl;
		};
	};
};