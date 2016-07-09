#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Deck.h"
#include "Pair.h"

class Player
{
    static int count;
//    socket
public:
    int id;
    std::wstring name;
    std::vector<Card> hand;
    Player();
    Player(Player& a);
    Player(std::wstring a);
//    Player(std::string a, socket something);
    int Take(int count, Deck &source);
    int Take(std::vector<Pair> heap);
    Card* Thrown();
    Card* Thrown(std::vector<Pair> &heap);
    int Answer(Pair &current, int trump);

};

#endif // PLAYER_H
