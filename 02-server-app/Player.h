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
    //int socket;
    int id;
    std::string name;
    std::vector<Card> hand;
    Player();
    //Player(std::string a, int socket);
    virtual int CloseSocket();
    int Take(int count, Deck &source);
    int Take(std::vector<Pair> heap);
    virtual std::shared_ptr<Card> Thrown();
    virtual std::shared_ptr<Card> Thrown(std::vector<Pair> &heap);
    virtual int Answer(Pair &current, int trump);
    int Sort();
    virtual int Send(std::string str);
    //virtual ~Player();
};

#endif // PLAYER_H
