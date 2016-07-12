#include <iostream>
#include "Deck.h"
#include "Table.h"
#include "Player.h"
#include <cstdlib>
#include <memory>
using namespace std;

int main(int argc, char *argv[])
{
    setlocale(LC_CTYPE, "");
    Deck my(13,4,0);
    my.Shuffle();

    std::vector<Player> players(3);
    players[0] = Player(L"Vasya");
    players[1] = Player(L"Petya");
    players[2] = Player(L"Sasha");

    //GAEM

    //Всем players раздается по 6 cards.
    for (Player &pl:players)
    {
        pl.Take(6,my);
        pl.Sort();
    }

    //Выбирается trump.
    Card tcard = my.Take();
    int trump = tcard.suit;
    wcout << L"Current trump:" << tcard.Print2() << endl;
    my.Add(tcard);

    //Выбирается player с trump наим. значения. Это apl.
    int tmin=100;
    int apl=0;
    for (int i=0; i<players.size(); i++)
    {
        for (int j=0; j<players[i].hand.size();j++)
        {
            if ((players[i].hand[j].suit == trump)&&(players[i].hand[j].face < tmin))
            {
                tmin = players[i].hand[j].face;
                apl = i;
            }
        }
    };
    int vpl = (apl+1)%players.size();
    wcout << L"Player " << players[apl].name << L" has lowest trump-card" << endl;

    //MAIN LOOP
    while(1)
    {
        bool vpl_take=false;
        //Определяются apl и vpl.
        vector<Pair> heap;

//        APL LOOP
//            apl кладет карту(ы), проверяя есть-ли она в pair_collection (если он не пустой), формируется pair
//            vpl дополняет pair, либо берет все карты из нее.
//        APL LOOP END
        shared_ptr<Card> temp = players[apl].Thrown();
        heap.push_back(Pair(temp));
        while(1)
        {
            if (players[vpl].Answer(heap[heap.size()-1], trump) == 1)
            {
                players[vpl].Take(heap);
                vpl_take = true;
                break;
            }
            else if (players[vpl].hand.size() == 0)
                break;
            shared_ptr<Card> temp = players[apl].Thrown(heap);
            if (temp == nullptr)
            {
                break;
            }
            heap.push_back(Pair(temp));
        }


//        ALL LOOP
//            Все игроки открывают pair (если cards этого достоинства есть в pair_collection).
//            vpl отбивается, либо забирает все pair со стола.
//            Если отбивается - все pair уходят в trash.
//        ALL LOOP END
        if ((!vpl_take)&&(players[vpl].hand.size()!=0))
        {
            while(1)
            {
                for (int i=(apl+2)%players.size(); i!=(apl+1)%players.size(); i=(i+1)%players.size())
                {
                    if (i == vpl) continue;

                    shared_ptr<Card> temp = players[i].Thrown(heap);
                    if (temp == nullptr)
                    {
                        continue;
                    }
                    else
                    {
                        heap.push_back(Pair(temp));
                        break;
                    }
                }
                if (heap[heap.size()-1].second == nullptr)
                {
                    if (players[vpl].Answer(heap[heap.size()-1], trump) == 1)
                    {
                        players[vpl].Take(heap);
                        vpl_take = true;
                        break;
                    }
                    else if (players[vpl].hand.size() == 0)
                        break;
                }
                else
                {
                    break;
                }
            }
        }


        //Идет добор cards до 6ти (если это возможно).
        //Если у player нет cards - он выходит из players.
        wcout << L"End of a turn" << endl;
        //apl берет первым
        if (players[apl].hand.size() < 6)
            players[apl].Take((6-players[apl].hand.size()),my);

        for (int i=(apl+2)%players.size(); i!=apl; i=(i+1)%players.size())
        {
            if (i == vpl) continue;

            if (players[i].hand.size() < 6)
                players[i].Take((6-players[i].hand.size()),my);
        }
        //vpl берет последним
        if (players[vpl].hand.size() < 6)
            players[vpl].Take((6-players[vpl].hand.size()),my);

        //удаление игрока из вектора
        for (int i=0;i<players.size();i++)
        {
            if (players[i].hand.size() == 0)
            {
                players.erase(players.begin() + i);
                if (i <= apl)
                {
                    apl = (apl-1)%players.size();
                    if((vpl < apl)&&(apl==i))
                        vpl = (vpl)%players.size();
                    else
                        vpl = (vpl-1)%players.size();
                }
                i=(i-1)%players.size();
            }
        }
//        Когда в players остался 1 player - он считается проигравшим.
        if (players.size() == 1)
        {
            wcout << L"Player " << players[0].name << L" is a durak!" << endl;
            break;
        }
        else if (players.size() == 0)
        {
            wcout << L"Draw!";
            break;
        }

        if (!vpl_take)
        {
            apl = vpl;
            vpl = (apl+1)%players.size();
//            vpl = (apl-1)%players.size();
        }
    }

    return 0;
}
