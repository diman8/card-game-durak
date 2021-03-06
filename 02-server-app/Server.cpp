#include "Server.h"
#include "Player.h"
#include "HPlayer.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <iostream>

Server::Server(int port)
{
    int socket_desc, yes=1;
    struct sockaddr_in server;
    if ((socket_desc = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("Could not create socket");
    }

    if (setsockopt(socket_desc,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind failed. Error");
    }

    this->sfd = socket_desc;
}

int Server::Wait(int count)
{
    struct sockaddr_in client;
    int client_sock, read_size, c=sizeof(struct sockaddr_in);
    char client_message[2000];

    listen(sfd, 3);

    while(count != 0)
    {
        //ждем accept на подключение. т.к. сокет не блокирующий - вернет -1 если ничего нет. но лучше проверить errno
        if ((client_sock = accept(sfd,(struct sockaddr *)&client, (socklen_t*)&c)) >= 0)
        {
            read_size = recv(client_sock, client_message, 2000, 0);
            if (read_size > 0)
            {
                client_message[read_size] = '\0';
                std::string name(client_message);
                pl.push_back(std::make_shared<HPlayer>(HPlayer(name, client_sock)));
                std::cout << "Player " << name << " has arrived!" << std::endl;
                count--;
            }
            else if(read_size == 0)
            {
                puts("Client disconnected");
            }
            else if(read_size == -1)
            {
                perror("recv failed");
            }
        }
        else if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
        {
            /* We have processed all incoming
             connections. */
            continue;
        }
        else
        {
            perror ("accept");
        }
    }
    /*
    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) >= 0)
    {
        while((read_size = recv(client_sock, client_message, 2000, 0)) > 0)
        {
            client_message[read_size]='\0';
            printf("%s\n",client_message);
            send(client_sock, client_message, read_size, 0);
        }

        if(read_size == 0)
        {
            puts("Client disconnected");
        }
        else if(read_size == -1)
        {
            perror("recv failed");
            return 1;
        }
    }
    */
}

int Server::MakeNonBlocking(int fd)
{
    int flags, s;

    flags = fcntl (fd, F_GETFL, 0);
    if (flags == -1)
    {
        perror ("fcnt");
        return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl (fd, F_SETFL, flags);
    if (s == -1)
    {
        perror ("fcnt");
        return -1;
    }

    return 0;
}

int Server::CloseSocket()
{
    close(this->sfd);
}
