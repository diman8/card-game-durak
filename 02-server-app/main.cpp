#include <iostream>
#include "Deck.h"
#include "Player.h"
#include <cstdlib>
#include <memory>
#include "Game.h"
#include "Server.h"
using namespace std;

int main(int argc, char *argv[])
{
    //setlocale(LC_CTYPE, "");

    Server myserv(8888);
    myserv.MakeNonBlocking(myserv.sfd);
    myserv.Wait(2);

    //Класс Server - там все взаимодействие
    //не буду использовать неблокирующие вызовы
    //хотя может и буду, но не epoll
    //открытие сокета, ожидающего на accept клиентов
    //нафиг не нужно лобби :)
    //как только залогинилось n-игроков - заканчивается прослушивание, игра начинается

    //игра:

    /*
    std::vector<Player> players;
    players.push_back(Player("Vasya", 10));
    players.push_back(Player("Petya", 20));
    players.push_back(Player("Sasha", 30));

    Game g1(players);
    g1.Play();
    */
    return 0;
}
