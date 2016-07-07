#ifndef PAIR_H
#define PAIR_H
#include "Card.h"
#include <vector>

class Pair
{
public:
    Card first;
    Card second;
    Pair();
    Pair(Card first);
    int Beat(Card sec, int trump);
    std::vector<Card> Contains();
};

#endif // PAIR_H
