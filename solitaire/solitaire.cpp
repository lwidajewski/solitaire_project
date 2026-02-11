#include<iostream>
#include<cstdlib> // for rand()

#include "Solitaire.h"

using namespace std;

// ------------------- Related Stack Functions --------------------------

Solitaire::Solitaire() {
	Node* top = nullptr;
	int deckSize = 52;
};

// check if stack is full -> maybe not needed for this but it is here anyway
bool Solitaire::isFull() {
	Node* temp;
	try {
		temp = new Node;
		delete temp;
		return false;
	}
	catch (bad_alloc) {
		return true;
	};
};

// check if stack is empty
bool Solitaire::isEmpty() {
	if (top == nullptr) {
		return true;
	}
	else {
		return false;
	};
};

void Solitaire::push(const Card& item) {
	if (isFull()) {
		throw bad_alloc();
	}
	else {
		Node* current = new Node;
		// insert card into the stack
		current->data = item;
		current->next = top;
		top = current;
	};
};

void Solitaire::pop() {
	if (isEmpty()) {
		throw runtime_error("Stack is empty, cannot pop");
		return;
	}
	else {
		Node* temp = top;
		top = top->next;
		delete temp;
	};
};

Card Solitaire::peek() {
	if (isEmpty()) {
		throw runtime_error("Stack is empty, cannot peek");
	}
	else {
		return top->data;
	};
};

Solitaire::~Solitaire() {

};

// ------------------- Card Related Functions ---------------------------

// create the 52 card deck
void Solitaire::createDeck() {

};

// prints the 52 card deck
void Solitaire::printCards() {

};

int Solitaire::randomInt(int low, int high) {
	return low + (rand() % (high - low + 1));
};

// swaps 2 cards in the 52 card deck - for shuffling purposes
void Solitaire::swapCards(Card& a, Card& b) {
	Card temp = a;
	a = b;
	b = temp;
};

// shuffles the 52 card deck
void Solitaire::shuffleDeck() {
	srand(static_cast<unsigned int>(time(nullptr)));

	for (int i = 0; i < 52; i++) {
		int j = randomInt(i, 51);
		swapCards(deck[i], deck[j]);
	};
};
