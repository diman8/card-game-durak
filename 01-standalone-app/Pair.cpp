#include "Pair.h"
#include "Card.h"
#include <vector>

Pair::Pair(){}

Pair::Pair(Card first)
{
    this->first = first;
}

int Pair::Beat(Card sec, int trump)
{
    if (this->first.Fight(sec, trump))
    {
        this->second = sec;
        return 0;
    }
    else
    {
        return 1;
    }
}

std::vector<Card> Pair::Contains()
{
    std::vector<Card> temp;
    temp.push_back(first);
    temp.push_back(second);
    return temp;
}
