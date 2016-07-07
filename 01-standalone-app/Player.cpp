#include "Player.h"
#include <iostream>
#include "Pair.h"
using namespace std;

int Player::count=0;

Player::Player()
{
    id = count++;
}

Player::Player(std::wstring a)
{
    id = count++;
    this->name = a;
}

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
    //temp.insert(hand.end(), std::make_move_iterator(temp.begin()), std::make_move_iterator(temp.end()));
}

Card Player::Thrown(bool first)
{
    while(1)
    {
        int choise=0;
        wcout << this->name << L": choose card to thrown" << endl;
        if (!first)
            wcout << L"-1. Nothing" << endl;
        for (int i=0; i<hand.size();i++)
        {
            wcout << i << ". " << hand[i].Print2() << endl;
        }
        cin >> choise;
        if (choise != -1)
        {
            Card temp = hand[choise];
            hand.erase(hand.begin() + choise);
            return temp;
        }
        else
        {
            if (first)
                return Card(); //TODO!!!
        }
    }
}

int Player::Answer(Pair &current, int trump)
{
    while(1)
    {
        int choise=0;
        wcout << this->name << L": choose card to answer for " << current.first.Print2() << endl;
        wcout << L"-1. Give up" << endl;
        for (int i=0; i<hand.size();i++)
        {
            wcout << i << ". " << hand[i].Print2() << endl;
        }
        cin >> choise;
        if (choise != -1)
        {
            if (current.Beat(hand[choise], trump))
            {
                return 0;
            }
        }
        else
        {
            return 1;
        }
    }
}
