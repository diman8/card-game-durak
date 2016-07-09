#ifndef PAIR_H
#define PAIR_H
#include "Card.h"
#include <vector>

class Pair
{
public:
    bool seccard;
    Card* first;
    Card* second;
    Pair(Card* first);
    ~Pair();
    int Beat(Card* sec, int trump);
    std::vector<Card> Contains();
};

#endif // PAIR_H
