#include <iostream>
#include <Deck.h>
#include <Turn.h>
#include <Player.h>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
    setlocale(LC_CTYPE, "");
    Deck my(13,4,0);
    my.Shuffle();
//    for(int i=0; i < 52; i++)
//    {
//        Card temp = my.Take();
//        std::wcout << temp.Print2() << std::endl;
//        for (int j=0; j < my.size; j++)
//        {
//            if (temp.Fight(my[j], 0) == 1)
//            {
//                std::wcout << L"    kill " << my[j].Print2() << std::endl;
//            }
//        }
//    }

    std::vector<Player> players(2);
    players[0] = Player(L"Vasya");
    players[0].Take(6,my);
    players[1] = Player(L"Petya");
    players[1].Take(6,my);

    //GAEM
    for (int i=0; i < players.size(); i++)
    {
        wcout << L"Player" << players[i].name << " has: ";
        for (int j=0; j<players[i].hand.size(); j++)
        {
            wcout << players[i].hand[j].Print2() << ", ";
        }
        wcout << endl;
    }
    //p1 turn






    return 0;
}
