#ifndef CARD_H
#define CARD_H
#include <string>

// enum {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
// enum {CLUBS, DIAMONDS, HEARTS, SPADES};

class Card
{
public:
    std::wstring cfaces[13] = {L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"T", L"J", L"Q", L"K", L"A"};
    std::wstring csuits[4] = {L"♣",L"♦",L"♥",L"♠"};
    unsigned short face;
    unsigned short suit;
    Card();
    Card(unsigned short face, unsigned short suit);
    short Fight(Card &a, unsigned short trump);
    std::string Print();
    std::wstring Print2();
};

#endif // CARD_H
