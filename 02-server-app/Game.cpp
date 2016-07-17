#include "Game.h"
#include <json.hpp>
#include <sys/socket.h>

Game::Game(vector<Player> &pl)
{
    this->players = pl;
    this->players_all = pl;
    my = Deck(13,4,0);
}

int Game::Play()
{
    my.Shuffle();

//    std::vector<Player> players(3);
//    players[0] = Player("Vasya");
//    players[1] = Player("Petya");
//    players[2] = Player("Sasha");

    //GAEM

    //Всем players раздается по 6 cards.
    for (Player &pl:players)
    {
        pl.Take(6,my);
        pl.Sort();
    }

    //Выбирается trump.
    tcard = my.Take();
    trump = tcard.suit;
    cout << "Current trump:" << tcard.Print2() << endl;
    my.Add(tcard);

    //SendGameStart();

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
    cout << "Player " << players[apl].name << " has lowest trump-card" << endl;

    //MAIN LOOP
    while(1)
    {
        bool vpl_take=false;
        //Определяются apl и vpl.
        vector<Pair> heap;

        SendGameinfo();
        SendOrder(apl,vpl);

//        APL LOOP
//            apl кладет карту(ы), проверяя есть-ли она в pair_collection (если он не пустой), формируется pair
//            vpl дополняет pair, либо берет все карты из нее.
//        APL LOOP END
        shared_ptr<Card> temp = players[apl].Thrown();
        SendTurnA(apl,temp);
        heap.push_back(Pair(temp));

        if (players[vpl].Answer(heap[heap.size()-1], trump) == 1)
        {
            players[vpl].Take(heap);
            vpl_take = true;
            SendTurnV(vpl, nullptr);
        }
        else
        {
            SendTurnV(vpl,std::make_shared<Card>(*heap[heap.size()-1].second));
        }


//        ALL LOOP
//            Все игроки открывают pair (если cards этого достоинства есть в pair_collection).
//            vpl отбивается, либо забирает все pair со стола.
//            Если отбивается - все pair уходят в trash.
//        ALL LOOP END
        if ((!vpl_take)&&(players[vpl].hand.size()!=0))
        {
            int lapl=apl;
            while(1)
            {
                //for (int i=(apl+2)%players.size(); i!=(apl+1)%players.size(); i=(i+1)%players.size())
                for (int i=0; i<players.size();i++)
                {
                    int j=(i+lapl)%players.size();

                    if (j == vpl) continue;

                    shared_ptr<Card> temp = players[j].Thrown(heap);
                    SendTurnA(j,temp);
                    if (temp == nullptr)
                    {
                        SendOrder(j,vpl);
                        continue;
                    }
                    else
                    {
                        heap.push_back(Pair(temp));
                        lapl=j;
                        break;
                    }
                }
                if (heap[heap.size()-1].second == nullptr)
                {
                    if (players[vpl].Answer(heap[heap.size()-1], trump) == 1)
                    {
                        players[vpl].Take(heap);
                        vpl_take = true;
                        SendTurnV(vpl, nullptr);
                        break;
                    }
                    else
                    {
                        SendTurnV(vpl, std::make_shared<Card>(*heap[heap.size()-1].second));
                        if (players[vpl].hand.size() == 0)
                            break;
                    }
                }
                else
                {
                    break;
                }
            }
        }


        //Идет добор cards до 6ти (если это возможно).
        //Если у player нет cards - он выходит из players.
        cout << "End of a turn" << endl;
        SendTurnEnd();
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
                SendPlayerDone(i, true);
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
            SendPlayerDone(0, false);
            cout << "Player " << players[0].name << " is a durak!" << endl;
            break;
        }
        else if (players.size() == 0)
        {
            cout << "Draw!";
            break;
        }

        if (!vpl_take)
        {
            apl = vpl;
            vpl = (apl+1)%players.size();
        }
    }
}

int Game::SendToAll(string message)
{
    nlohmann::json data;
    data["signal"]="consolelog";
    data["message"]=message;
    string snd = data.dump();
    for (Player &pl : players)
    {
        send(pl.socket,snd.c_str(),snd.size(),0);
    }
}
/*
int Game::SendGameStart()
{
    nlohmann::json data;
    data["signal"]="gamestart";
    data["trumpcard"]={this->tcard.face, this->tcard.suit};
    for (int i=0; i<this->players.size(); i++)
    {
        data["players"][i]={{"name",players[i].name},{"id",players[i].id},{"cards",players[i].hand.size()}};
    }
    for (Player &pl : this->players)
    {
        nlohmann::json data2 = data;
        for (int i=0; i<pl.hand.size(); i++)
            data2["hand"][i]={pl.hand[i].face, pl.hand[i].suit};
        cout << data2.dump() << endl;
    }
}
*/
int Game::SendOrder(int lapl, int vpl)
{
    nlohmann::json data;
    string tmp;
    data["signal"]="order";
    data["lapl"] = lapl;
    data["vpl"] = vpl;

    cout << data.dump() << endl;
    for (Player &pl : this->players)
    {
        tmp = data.dump();
        send(pl.socket,tmp.c_str(),tmp.size(),0);
    }
}

int Game::SendGameinfo()
{
    nlohmann::json data;
    string tmp;
    data["signal"]="gameinfo";
    data["deck"]=this->my.size;
    data["trumpcard"]={this->tcard.face, this->tcard.suit};
    for (int i=0; i<this->players.size(); i++)
    {
        data["players"][i]={{"name",players[i].name},{"id",players[i].id},{"cards",players[i].hand.size()}};
    }
//    for (int i=0; i<heap.size(); i++)
//    {
//        data["pairs"][i]["f"] = {heap[i].first->face, heap[i].first->suit};
//        data["pairs"][i]["s"] = {heap[i].second->face, heap[i].second->suit};
//    }
    for (Player &pl : this->players)
    {
        nlohmann::json data2 = data;
        for (int i=0; i<pl.hand.size(); i++)
            data2["hand"][i]={pl.hand[i].face, pl.hand[i].suit};
        cout << data2.dump() << endl;

        tmp = data2.dump();
        send(pl.socket,tmp.c_str(),tmp.size(),0);
    }
}

int Game::SendTurnA(int plid, std::shared_ptr<Card> temp)
{
    nlohmann::json data;
    string tmp;
    data["signal"]="turna";
    data["plid"]=plid;
    if (temp == nullptr)
        data["none"]=true;
    else
        data["card"]={temp->face, temp->suit};

    cout << data.dump() << endl;
    for (Player &pl : this->players)
    {
        tmp = data.dump();
        send(pl.socket,tmp.c_str(),tmp.size(),0);
    }
}

int Game::SendTurnV(int plid, std::shared_ptr<Card> temp)
{
    nlohmann::json data;
    string tmp;
    data["signal"]="turnv";
    data["plid"]=plid;

    if(temp==nullptr)
        data["giveup"]=true;
    else
        data["card"]={temp->face, temp->suit};

    cout << data.dump() << endl;
    for (Player &pl : this->players)
    {
        tmp = data.dump();
        send(pl.socket,tmp.c_str(),tmp.size(),0);
    }
}

int Game::SendPlayerDone(int plid, bool win)
{
    nlohmann::json data;
    string tmp;
    data["signal"]="done";
    data["plid"]=plid;
    if (win)
        data["win"]=true;
    else
        data["win"]=false;

    cout << data.dump() << endl;

    for (Player &pl : this->players)
    {
        tmp = data.dump();
        send(pl.socket,tmp.c_str(),tmp.size(),0);
    }
}

int Game::SendTurnEnd()
{
    nlohmann::json data;
    string tmp;
    data["signal"]="turnend";

    cout << data.dump() << endl;

    for (Player &pl : this->players)
    {
        tmp = data.dump();
        send(pl.socket,tmp.c_str(),tmp.size(),0);
    }
}

int Game::SendPairs(vector<Pair> heap)
{
    nlohmann::json data;
    string tmp;
    data["signal"]="pairs";
    for (int i=0; i<heap.size(); i++)
    {
        data["pairs"][i]["f"] = {heap[i].first->face, heap[i].first->suit};
        if (heap[i].second != nullptr)
        {
            data["pairs"][i]["s"] = {heap[i].second->face, heap[i].second->suit};
        }
        else
        {
            data["pairs"][i]["s"] = 0;
        }
    }
    for (Player &pl : this->players)
    {
        nlohmann::json data2 = data;
        for (int i=0; i<pl.hand.size(); i++)
            data2["hand"][i]={pl.hand[i].face, pl.hand[i].suit};
        cout << data2.dump() << endl;

        tmp = data2.dump();
        send(pl.socket,tmp.c_str(),tmp.size(),0);
    }
}
