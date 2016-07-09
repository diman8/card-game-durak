#include "Pair.h"
#include "Card.h"
#include <vector>

Pair::Pair(Card* first)
{
    this->first = first;
    this->second = nullptr;
}

int Pair::Beat(Card* sec, int trump)
{
    if(sec->Fight(*(this->first), trump))
    {
        return 0;
    }
    else
    {
        this->second = sec;
        return 1;
    }
}

std::vector<Card> Pair::Contains()
{
    std::vector<Card> temp;
    Card tmp = *first;
    temp.push_back(tmp);
    if (second != nullptr)
    {
        Card tmp2 = *second;
        temp.push_back(tmp2);
    }
    return temp;
}

Pair::~Pair()
{
    delete first;
    if (second != nullptr) delete second;
}
