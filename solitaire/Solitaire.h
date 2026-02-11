#ifndef SOLITAIRESTACK_H
#define SOLITAIRESTACK_H

#include"Card.h"

class Solitaire {
	private:
		struct Node {
			Card data;
			Node* next;
		};
		Node* top;
	public:
		Card deck[52];

		// constructor
		Solitaire();

		// stack functions
		bool isFull();
		bool isEmpty();
		void push(const Card& item);
		void pop();
		Card peek();

		// deck/card functions
		void createDeck();
		void printCards();
		int randomInt(int low, int high);
		void swapCards(Card& a, Card& b);
		void shuffleDeck();

		// destructor
		~Solitaire();
};

#endif