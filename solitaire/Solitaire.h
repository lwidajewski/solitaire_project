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
};

#endif