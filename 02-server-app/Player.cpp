#include "Player.h"
#include <iostream>
#include "Pair.h"
#include <unistd.h>
#include <sys/socket.h>
#include "json.hpp"

using namespace std;

int Player::count=0;

Player::Player(){}

Player::Player(std::string a, int socket)
{
    id = count++;
    this->name = a;
    this->socket = socket;
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
}

std::shared_ptr<Card> Player::Thrown() //вызывается при 1ом ходе
{
    char ctmp[2000];
    int choise=0;
    nlohmann::json datas;
    datas["signal"]="thrown";
    datas["first"]=true;
    string tmp = datas.dump();
    send(this->socket,tmp.c_str(),tmp.size(),0);
    while(1)
    {
        int rsize = recv(this->socket, ctmp, 2000, 0);
        ctmp[rsize] = '\0';
        tmp = ctmp;
        nlohmann::json datar = nlohmann::json::parse(tmp);
        if (datar["signal"]=="thrown")
        {
            choise = datar["card"];
            if ((choise >= 0) && (choise < this->hand.size()))
            {
                nlohmann::json dataa;
                dataa["signal"]="status";
                dataa["status"]="ok";
                tmp = dataa.dump();
                send(this->socket,tmp.c_str(),tmp.size(),0);

                std::shared_ptr<Card> temp(new Card(hand[choise]));
                hand.erase(hand.begin() + choise);
                return temp;
            }
        }
        nlohmann::json dataa;
        dataa["signal"]="status";
        dataa["status"]="bad";
        send(this->socket,tmp.c_str(),tmp.size(),0);
    }
}

std::shared_ptr<Card> Player::Thrown(vector<Pair> &heap) //при 2ых и последующих
{
    if (this->hand.size()==0)
        return nullptr;

    vector<Card> stack;
    for (int i=0; i<heap.size();i++)
    {
        vector<Card> tmp = heap[i].Contains();
        stack.insert(stack.end(),tmp.begin(),tmp.end());
    }

    char ctmp[2000];
    int choise=0;
    nlohmann::json datas;
    datas["signal"]="thrown";
    datas["first"]=false;
    string tmp = datas.dump();
    send(this->socket,tmp.c_str(),tmp.size(),0);
    while(1)
    {
        int rsize = recv(this->socket, ctmp, 2000, 0);
        ctmp[rsize] = '\0';
        tmp = ctmp;
        nlohmann::json datar = nlohmann::json::parse(tmp);
        if (datar["signal"]=="thrown")
        {
            choise = datar["card"];
            if (choise == -1)
            {
                nlohmann::json dataa;
                dataa["signal"]="status";
                dataa["status"]="ok";
                tmp = dataa.dump();
                send(this->socket,tmp.c_str(),tmp.size(),0);

                return nullptr;
            }
            else if ((choise >= 0) && (choise < this->hand.size()))
            {
                for (int i=0; i<stack.size();i++)
                {
                    if (hand[choise].face == stack[i].face)
                    {
                        nlohmann::json dataa;
                        dataa["signal"]="status";
                        dataa["status"]="ok";
                        tmp = dataa.dump();
                        send(this->socket,tmp.c_str(),tmp.size(),0);

                        std::shared_ptr<Card> temp(new Card(hand[choise]));
                        hand.erase(hand.begin() + choise);
                        return temp;
                    }
                }
            }
        }
        nlohmann::json dataa;
        dataa["signal"]="status";
        dataa["status"]="bad";
        tmp = dataa.dump();
        send(this->socket,tmp.c_str(),tmp.size(),0);
    }
}

int Player::Answer(Pair &current, int trump)
{
    char ctmp[2000];
    int choise=0;
    nlohmann::json datas;
    datas["signal"]="answer";
    string tmp = datas.dump();
    send(this->socket,tmp.c_str(),tmp.size(),0);
    while(1)
    {
        int rsize = recv(this->socket, ctmp, 2000, 0);
        ctmp[rsize] = '\0';
        tmp = ctmp;
        nlohmann::json datar = nlohmann::json::parse(tmp);
        if (datar["signal"]=="answer")
        {
            choise = datar["card"];
            if (choise == -1)
            {
                nlohmann::json dataa;
                dataa["signal"]="status";
                dataa["status"]="ok";
                tmp = dataa.dump();
                send(this->socket,tmp.c_str(),tmp.size(),0);

                return 1;
            }
            else if ((choise >= 0) && (choise < this->hand.size()))
            {
                if (current.Beat(std::make_shared<Card>(hand[choise]), trump))
                {
                    nlohmann::json dataa;
                    dataa["signal"]="status";
                    dataa["status"]="ok";
                    tmp = dataa.dump();
                    send(this->socket,tmp.c_str(),tmp.size(),0);

                    hand.erase(hand.begin() + choise);
                    return 0;
                }
            }
        }
        nlohmann::json dataa;
        dataa["signal"]="status";
        dataa["status"]="bad";
        tmp = dataa.dump();
        send(this->socket,tmp.c_str(),tmp.size(),0);
    }
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

int Player::CloseSocket()
{
    close(this->socket);
}
