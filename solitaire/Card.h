#ifndef CARD_H
#define CARD_H

class Card {
public:
	Card();
	Card(int j, char s);
	int rank; // rank from 1 to 13 (11, 12, 13 --> J, Q, K)
	char suit; // 4 suits (Spade, Heart, Club, Diamond)
};

#endif