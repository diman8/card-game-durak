#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "Deck.h"
#include "Player.h"
#include <cstdlib>
#include <memory>

using namespace std;

class Game
{
    vector<Player> players;
public:
    Game(vector<Player> &pl);
    int Play();
    ~Game();
};

#endif // GAME_H
