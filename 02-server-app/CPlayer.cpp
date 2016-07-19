#include "CPlayer.h"
#include <iostream>
#include "Pair.h"
#include <vector>
#include <memory>
#include <unistd.h>

using namespace std;

int CPlayer::count_comp = 0;

CPlayer::CPlayer()
{
    id = count++;
    comp_id = ++count_comp;
    name = "Comp" + std::to_string(comp_id);
}

//CPlayer::CPlayer(std::string a, int socket)
//{
//    id = count++;
//    this->name = a;
//    this->socket = socket;
//}

std::shared_ptr<Card> CPlayer::Thrown()
{
    usleep(100000);
    std::shared_ptr<Card> temp(new Card(hand[0]));
    hand.erase(hand.begin() + 0);
    std::cout << this->name << "thrown" << temp->Print2() << std::endl;
    return temp;
}

std::shared_ptr<Card> CPlayer::Thrown(vector<Pair> &heap)
{
    usleep(100000);
    vector<Card> stack;
    for (int i=0; i<heap.size();i++)
    {
        vector<Card> tmp = heap[i].Contains();
        stack.insert(stack.end(),tmp.begin(),tmp.end());
    }
    for (int i=0; i<hand.size(); i++)
    {
        if (hand[i].face == stack[i].face)
        {
            std::shared_ptr<Card> temp(new Card(hand[i]));
            hand.erase(hand.begin() + i);
            return temp;
        }
    }
    return nullptr;
}

int CPlayer::Answer(Pair &current, int trump)
{
    usleep(100000);
    for(int i=0; i<hand.size(); i++)
    {
        if (current.Beat(std::make_shared<Card>(hand[i]), trump))
        {
            hand.erase(hand.begin() + i);
            return 0;
        }
    }
    return 1;
}

//CPlayer::~CPlayer(){}
int CPlayer::CloseSocket(){}
int CPlayer::Send(std::string str){}
