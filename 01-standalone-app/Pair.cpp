#include "Pair.h"
#include "Card.h"
#include <vector>

Pair::Pair(){}

Pair::Pair(Card first)
{
    this->first = first;
    //this->second = NULL;
}

int Pair::Beat(Card sec, int trump)
{
    if(sec.Fight(this->first, trump))
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
    //if (second != NULL) temp.push_back(second);
    return temp;
}
