#include "Player.h"

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

int Player::Take(int count, Deck source)
{
    //нужна проверка на то, что столько карт можно взять из колоды
    std::vector<Card> temp = source.Take(count);
    //соединяем 2 вектора
    if(hand.size()!=0)
        temp.insert(hand.end(), std::make_move_iterator(temp.begin()), std::make_move_iterator(temp.end()));
    else
    {
        hand=temp;
    }
    return 0;
    //temp.insert(hand.end(), std::make_move_iterator(temp.begin()), std::make_move_iterator(temp.end()));
}


