#include "Deck.h"
#include <time.h>

Deck::Deck(){}

Deck::Deck(int faces, int suits, bool jokers)
{
    int count = faces*suits;
    stack = new std::vector<Card>(count+(jokers*2));
    for (int i=0; i < count; i++)
    {
        stack->at(i) = Card(i%faces,i/faces);
    }
    size = count+(jokers*2);
    /*
    if (jokers)
    {
        for (int i=count; i < count+2; i++)
        {
            stack[i] = SCard(i%2);
        }
    }
    */
}

void Deck::Shuffle()
{
    //узкое место, надо что-то придумать с rand и time
    //придумал!
    srand(time(0));
    int size = stack->size();
    for (int i=0; i < size-1; i++)
    {
        //stack[i].swap(stack[((std::rand()%(size-i))+i)]);
        std::swap(stack->at(i), stack->at(((rand()%(size-i))+i)));

    }
}

Card Deck::Take()
{
    if (size!=0)
    {
        Card temp = stack->back();
        stack->pop_back();
        --size;
        return temp;
    }
    else
    {
        return Card();
    }

}

std::vector<Card> Deck::Take(int i)
{
    std::vector<Card> temp(i);
    for(int j=0; j<i;j++)
    {
        temp[j]=this->Take();
    }
    return temp;
}

Card& Deck::operator [](int i)
{
    return stack->at(i);
}

int Deck::Add(Card a)
{
    //stack->push_back(a);
    stack->insert(stack->begin(),a);
    ++this->size;
    return 0;
}
