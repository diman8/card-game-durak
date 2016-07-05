#ifndef PAIR_H
#define PAIR_H


class Pair
{
    Card first;
    Card second;
public:
    Pair();
    Pair(Card first);
    int Beat(Card sec);
    std::vector<Card> Contains();
};

#endif // PAIR_H
