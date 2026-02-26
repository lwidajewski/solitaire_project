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
		Stack openCell[4];
	public:
		Solitaire();

		// deck/card functions
		void displayCards();
		int randomInt(int low, int high);
		void swapCards(Card& a, Card& b);
		void shuffleDeck();
		void dealCards();
		void displayTableau();
		void gamePlay();


		// moving card functions
		 
		// tableau moves
		bool checkTableauToTableauMove(Card& movedCard, Card& destination);

		// free cell moves
		bool checkFreeCellToTableau(Card& movedCard, Stack& tableau);

		// move to foundation (from either free cell or tableau)
		bool checkMoveToFoundation(Card& movedCard, Stack& foundation);

		// move to empty tableau or free cell
		bool checkMoveToEmptyStack(Stack& stack);
};

#endif