#include "Pair.h"
#include "Card.h"
#include <vector>
#include <memory>

Pair::Pair(std::shared_ptr<Card> first)
{
    this->first = first;
    this->second = nullptr;
}

int Pair::Beat(std::shared_ptr<Card> sec, int trump)
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
    temp.push_back(*first);
    if (second != nullptr)
    {
        temp.push_back(*second);
    }
    return temp;
}

Pair::~Pair()
{}
