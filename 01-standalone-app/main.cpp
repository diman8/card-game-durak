#include <iostream>
#include <Deck.h>
#include <Table.h>
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
    players[1] = Player(L"Petya");

    //GAEM

    //Всем players раздается по 6 cards.
    for (int i=0; i<players.size(); i++)
    {
        players[i].Take(6,my);
    }

    //Выбирается trump.
    int trump = 0;
    wcout << L"Current trump: ♣" << endl;

    //Выбирается player с trump наим. значения. Это apl.
    int apl = 0;

    //MAIN LOOP
    while(1)
    {
        //Определяются apl и vpl.
        int vpl = (apl-1)%players.size();
        vector<Pair> heap;

//        APL LOOP
//            apl кладет карту(ы), проверяя есть-ли она в pair_collection (если он не пустой), формируется pair
//            vpl дополняет pair, либо берет все карты из нее.
//        APL LOOP END
        Card temp = players[apl].Thrown(true);
        heap.push_back(Pair(temp));
        if (players[vpl].Answer(heap[0], trump) == 1)
        {
            players[vpl].Take(heap);
        }

//        ALL LOOP
//            Все игроки открывают pair (если cards этого достоинства есть в pair_collection).
//            vpl отбивается, либо забирает все pair со стола.
//            Если отбивается - все pair уходят в trash.
//        ALL LOOP END

        //Идет добор cards до 6ти (если это возможно).
        for (int i=0; i<players.size(); i++)
        {
            if (players[i].hand.size() < 6)
                players[i].Take((6-players[i].hand.size()),my);
        }

    }

    return 0;
}
