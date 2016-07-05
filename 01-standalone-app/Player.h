#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <Deck.h>

class Player
{
    static int count;
//    socket
public:
    int id;
    std::wstring name;
    std::vector<Card> hand;
    Player();
    Player(std::wstring a);
//    Player(std::string a, socket something);
    int Take(int count, Deck source);
    Card Thrown(); //надо-ли?

};

#endif // PLAYER_H
