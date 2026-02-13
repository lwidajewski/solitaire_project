#ifndef SOLITAIRE_H
#define SOLITAIRE_H

#include"Card.h"

class Solitaire {
	private:
		// initialize 52 card deck
		Card deck[52];
	public:
		Solitaire();

		// deck/card functions
		void displayCards();
		int randomInt(int low, int high);
		void swapCards(Card& a, Card& b);
		void shuffleDeck();
};

#endif