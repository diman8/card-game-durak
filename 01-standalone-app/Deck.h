#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include <vector>

class Deck
{
    std::vector<Card> *stack;
public:
    int size;
    Deck();
    Deck(int faces, int suits, bool jokers);
    void Shuffle();
    Card Take();
    std::vector<Card> Take(int i);
    Card& operator[](int i);
};

#endif // DECK_H
