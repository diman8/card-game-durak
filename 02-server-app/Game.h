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
    vector<std::shared_ptr<Player>> players;
    //vector<std::shared_ptr<Player>> players_all;
    Deck my;
    int trump;
    Card tcard;
    int apl,vpl;
    Game(vector<std::shared_ptr<Player>> &pl);
    int Play();
    int SendToAll(string message);
    //int SendGameStart();
    int SendGameinfo();
    int SendOrder(int apl, int vpl);
    int SendTurnV(int plid, std::shared_ptr<Card> temp);
    int SendTurnA(int plid, std::shared_ptr<Card> temp);
    int SendTurnEnd();
    int SendPairs(vector<Pair> heap);
    int SendPlayerDone(int plid, bool win);
};

#endif // GAME_H
