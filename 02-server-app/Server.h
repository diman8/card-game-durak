#ifndef SERVER_H
#define SERVER_H
#include <vector>
#include <string>
#include <memory>
#include "Player.h"

class Server
{
public:
    std::vector<std::shared_ptr<Player>> pl;
    int sfd;
    Server(int port);
    int Wait(int count);
    int MakeNonBlocking(int fd);
    int CloseSocket();
};

#endif // SERVER_H
