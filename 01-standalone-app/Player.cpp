#include "Player.h"

Player::Player()
{
    id = count++;
}

Player::Player(std::string a)
{
    id = count++;
    name = a;
}

int Player::Take(int count, Deck source)
{
    //нужна проверка на то, что столько карт можно взять из колоды
    std::vector<Card> temp = source.Take(count);
    //соединяем 2 вектора
    temp.insert(hand.end(), std::make_move_iterator(temp.begin()), std::make_move_iterator(temp.end()));
}

