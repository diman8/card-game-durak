#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "Deck.h"
#include "Player.h"
#include "Pair.h"
#include <cstdlib>
#include <memory>

#define GAMESTART 0
#define CONSOLELOG 1
#define ORDER 2
#define GAMEINFO 3
#define TURNA 4
#define TURNV 5

using namespace std;

class Game
{
public:
    vector<Player> players;
    vector<Player> players_all;
    Deck my;
    int trump;
    Card tcard;
    int apl,vpl;
    Game(vector<Player> &pl);
    int Play();
    int SendToAll(string message);
    //int SendGameStart();
    int SendGameinfo(vector<Pair> heap);
    int SendOrder(int apl, int vpl);
    int SendTurnV(int plid, Card temp);
    int SendTurnA(int plid, Card temp);
    int SendPlayerDone(bool win=true);
};

#endif // GAME_H
