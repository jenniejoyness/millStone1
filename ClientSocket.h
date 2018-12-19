//
// Created by renana on 12/19/18.
//

#ifndef MILLSTONE_COSTUMERSOCKET_H
#define MILLSTONE_COSTUMERSOCKET_H

#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>
#include <map>
#include <netinet/in.h>
using namespace std;


class ClientSocket {
    struct sockaddr_in serverSocket;
    map<string,string> varPlaces;
    int id;

public:
    ClientSocket();

    static void* openSocket(void* arg);
    void* getSocket(void* arg);

};


#endif //MILLSTONE_COSTUMERSOCKET_H
