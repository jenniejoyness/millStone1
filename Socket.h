//
// Created by renana on 12/19/18.
//

#ifndef MILLSTONE_SOCKET_H
#define MILLSTONE_SOCKET_H
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

class Socket {
protected:
    struct sockaddr_in socket;
    map<string,string> varPlaces;
    int id;
public:
    virtual void* openSocket(void* arg) = 0;
    virtual void* getSocket() = 0;

};

#endif //MILLSTONE_SOCKET_H
