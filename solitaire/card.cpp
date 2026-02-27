#include "Card.h"

Card::Card() {
	rank = 0;
	suit = ' ';
}

Card::Card(int j, char s) {
	rank = j;
	suit = s;
};

bool Card::isRed() const {
	if (suit == 'H' || suit == 'D') {
		return true;
	}
	else {
		return false;
	};
};