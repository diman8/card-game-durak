#ifndef PAIR_H
#define PAIR_H
#include "Card.h"
#include <vector>

class Pair
{
    Card first;
    Card second;
public:
    Pair();
    Pair(Card first);
    int Beat(Card sec, int trump);
    std::vector<Card> Contains();
};

#endif // PAIR_H
