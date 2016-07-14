#include "Card.h"
#include "globals.h"

int Card::count=0;

Card::Card(){}
Card::Card(unsigned short face, unsigned short suit)
{
    id = count++;
    this->face=face;
    this->suit=suit;
}

// 0 если бьем, 1 иначе
short Card::Fight(Card &a, unsigned short trump)
{
    if (this->suit == a.suit)
        return ((this->face > a.face) ? 0 : 1);
    else if ((this->suit == trump) && (a.suit != trump))
        return 0;
    else
        return 1;
}

std::string Card::Print()
{
    char temp[10];
    sprintf(temp, "%d of %d", this->face, this->suit);
    return std::string(temp);
}

std::string Card::Print2()
{
    return std::string(globals::cfaces[face] + globals::csuits[suit]);
}
