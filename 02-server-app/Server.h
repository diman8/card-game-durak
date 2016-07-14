#ifndef SERVER_H
#define SERVER_H
#include <vector>
#include <string>
#include "Player.h"

class Server
{
public:
    std::vector<Player> pl;
    int sfd;
    Server(int port);
    int Wait(int count);
    int MakeNonBlocking(int fd);
};

#endif // SERVER_H
