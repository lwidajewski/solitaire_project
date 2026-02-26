#ifndef SOLITAIRE_H
#define SOLITAIRE_H

#include"Card.h"
#include"Stack.h"

class Solitaire {
	private:
		// initialize 52 card deck
		Card deck[52];

		Stack tableau[8];
		Stack foundation[4];
		Stack freeCell[4];
	public:
		Solitaire();

		// deck/card functions
		void displayCards();
		int randomInt(int low, int high);
		void swapCards(Card& a, Card& b);
		void shuffleDeck();
		void dealCards();

		// gameplay functions
		void displayBoard();
		void gamePlay();


		// checking for legal card moves functions
		// tableau moves
		bool checkTableauToTableauMove(const Card& movedCard, const Card& destination);
		// free cell moves
		bool checkFreeCellToTableau(const Card& movedCard, const Stack& tableau);
		// move to foundation (from either free cell or tableau)
		bool checkMoveToFoundation(const Card& movedCard, const Stack& foundation);
		// move to empty tableau or free cell
		bool checkMoveToEmptyStack(const Stack& stack);

		// uses the legal move checks and process the move if it was legal
		bool moveCard(char whereType, int whereIndex, char destinationType, int destinationIndex);
};

#endif