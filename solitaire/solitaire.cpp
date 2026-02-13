#include<iostream>
#include<cstdlib> // for rand()

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

// shuffles the 52 card deck
void Solitaire::shuffleDeck() {
	for (int i = 0; i < 52; i++) {
		int j = randomInt(i, 51);
		swapCards(deck[i], deck[j]);
	};
};
