#ifndef CARD_H
#define CARD_H
#include <string>
#include "globals.h"

// enum {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
// enum {CLUBS, DIAMONDS, HEARTS, SPADES};

class Card
{
public:
    int id;
    static int count;
    unsigned short face;
    unsigned short suit;
    Card();
    Card(unsigned short face, unsigned short suit);
    short Fight(Card &a, unsigned short trump);
    std::string Print();
    std::string Print2();
};

#endif // CARD_H
