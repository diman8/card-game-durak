#ifndef PAIR_H
#define PAIR_H
#include "Card.h"
#include <vector>
#include <memory>

class Pair
{
public:
    std::shared_ptr<Card> first;
    std::shared_ptr<Card> second;
    Pair(std::shared_ptr<Card> first);
    ~Pair();
    int Beat(std::shared_ptr<Card> sec, int trump);
    std::vector<Card> Contains();
};

#endif // PAIR_H
