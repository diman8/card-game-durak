#ifndef HPLAYER_H
#define HPLAYER_H
#include "Player.h"

class HPlayer : public Player
{
public:
    int socket;
    HPlayer(std::string a, int socket);
    std::shared_ptr<Card> Thrown();
    std::shared_ptr<Card> Thrown(std::vector<Pair> &heap);
    int Send(std::string str);
    int CloseSocket();
    int Answer(Pair &current, int trump);
    //~HPlayer();
};

#endif // HPLAYER_H
