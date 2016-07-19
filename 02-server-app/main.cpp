#include <iostream>
#include "Deck.h"
#include "Player.h"
#include <cstdlib>
#include <memory>
#include "Game.h"
#include "Server.h"
#include "getopt.h"
using namespace std;

int main(int argc, char *argv[])
{
    setlocale(LC_CTYPE, "");

    //передаваемые параметры
    int param=0;
    while ((param = getopt(argc,argv,"p:sbc:")) != -1)
    {
        switch(param)
        {
        case 'b':
            globals::sdeck=0;
            break;
        case 's':
            globals::sdeck=1;
            break;
        case 'p':
            globals::port=atoi(optarg);
        case 'c':
            globals::count=atoi(optarg);
        }
    }


    Server myserv(globals::port);
    //myserv.MakeNonBlocking(myserv.sfd);
    myserv.Wait(2);

    //Класс Server - там все взаимодействие
    //не буду использовать неблокирующие вызовы
    //хотя может и буду, но не epoll
    //открытие сокета, ожидающего на accept клиентов
    //нафиг не нужно лобби :)
    //как только залогинилось n-игроков - заканчивается прослушивание, игра начинается

    //игра:

    std::vector<Player> players = myserv.pl;
    Game g1(players);
    try
    {
        g1.Play();
    }
    catch(const invalid_argument& ia)
    {
        cout << "Invalid argument: " << ia.what() << endl;
        cout << "Server is shooting down." << endl;
    }

    for (Player &pl: players)
    {
        pl.CloseSocket();
    }
    myserv.CloseSocket();
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
