#ifndef STACK_H
#define STACK_H

#include "Card.h"

class Stack {
	private:
		struct Node {
			Card data; // contains a cards suit and a number 1-13 (11, 12, 13 --> J, Q, K)
			Node* next;
		};
		Node* top;
		int sizenum;
	public:

		// constructor
		Stack();

		// stack functions
		bool isFull();
		bool isEmpty() const;
		void push(const Card& item);
		void pop();
		Card peek() const;
		int size() const;

		// destructor
		~Stack();
};

#endif