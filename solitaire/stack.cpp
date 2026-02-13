#include<iostream>

#include"Stack.h"

using namespace std;

// ------------------- Related Stack Functions --------------------------

Stack::Stack() {
	Node* top = nullptr;
	int deckSize = 52;
};

// check if stack is full -> maybe not needed for this but it is here anyway
bool Stack::isFull() {
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
bool Stack::isEmpty() {
	if (top == nullptr) {
		return true;
	}
	else {
		return false;
	};
};

// add to the top of the stack
void Stack::push(const Card& item) {
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

// delete the top of the stack
void Stack::pop() {
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

// look at the top of the stack
Card Stack::peek() {
	if (isEmpty()) {
		throw runtime_error("Stack is empty, cannot peek");
	}
	else {
		return top->data;
	};
};

// destructor
Stack::~Stack() {
	Node* current = top;
	while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
	};
	top = nullptr;
};