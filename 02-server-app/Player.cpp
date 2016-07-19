#include "Player.h"
#include <iostream>
#include "Pair.h"
#include <unistd.h>
#include <sys/socket.h>
#include "json.hpp"

using namespace std;

int Player::count=0;

Player::Player(){}

//Player::Player(std::string a, int socket)
//{
//    id = count++;
//    this->name = a;
//    this->socket = socket;
//}

int Player::Take(std::vector<Pair> heap)
{
    for (int i=0; i<heap.size(); i++)
    {
        vector<Card> temp = heap[i].Contains();
        hand.insert(hand.end(), std::make_move_iterator(temp.begin()), std::make_move_iterator(temp.end()));
    }
}

int Player::Take(int count, Deck &source)
{
    std::vector<Card> temp;
    //нужна проверка на то, что столько карт можно взять из колоды
    for (int i=0; i<count; i++)
    {
        if (source.size != 0)
            temp.push_back(source.Take());
    }
    //соединяем 2 вектора

    if((hand.size()!=0)&&(temp.size()!=0))
        hand.insert(hand.end(), temp.begin(), temp.end());
        //temp.insert(hand.end(), std::make_move_iterator(temp.begin()), std::make_move_iterator(temp.end()));
    else if (hand.size()==0)
    {
        hand=temp;
    }
    return 0;
}

int Player::Sort()
{
    for (int i=0; i<hand.size(); i++)
    {
        for (int j=i; j<hand.size(); j++)
        {
            if (hand[i].id > hand[j].id)
                std::swap<Card>(hand[i],hand[j]);
        }
    }
}

int Player::CloseSocket(){}
std::shared_ptr<Card> Player::Thrown(){}
std::shared_ptr<Card> Player::Thrown(std::vector<Pair> &heap){}
int Player::Answer(Pair &current, int trump){}
int Player::Send(std::string str){}

//int Player::CloseSocket(){}
//int Player::Send(std::string str){}
