#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <memory>
#include "Deck.h"
#include "Pair.h"

class Player
{
public:
    static int count;
    int socket;
    int id;
    std::string name;
    std::vector<Card> hand;
    Player();
    Player(std::string a, int socket);
    int CloseSocket();
//    Player(std::string a, socket something);
    int Take(int count, Deck &source);
    int Take(std::vector<Pair> heap);
    std::shared_ptr<Card> Thrown();
    std::shared_ptr<Card> Thrown(std::vector<Pair> &heap);
    int Answer(Pair &current, int trump);
    int Sort();
};

#endif // PLAYER_H
