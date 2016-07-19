#ifndef CPLAYER_H
#define CPLAYER_H
#include "Player.h"

class CPlayer : public Player
{
public:
    static int count_comp;
    int comp_id;
    CPlayer();
    int CloseSocket();
    std::shared_ptr<Card> Thrown();
    std::shared_ptr<Card> Thrown(std::vector<Pair> &heap);
    int Send(std::string str);
    int Answer(Pair &current, int trump);
    //~CPlayer();
};

#endif // CPLAYER_H
