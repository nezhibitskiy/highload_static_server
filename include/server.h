//
// Created by ilyas on 23.09.2022.
//

#ifndef HIGHLOAD2DZ_SERVER_H
#define HIGHLOAD2DZ_SERVER_H

#include <evutil.h>
#include "staticHander.h"
#include <event2/listener.h>

class Server {
public:
    explicit Server(int cpuCount, std::string rootDir, std::string defaultFile);
    ~Server();
    void Run();
private:
    static void AcceptConnect(struct evconnlistener *listener, evutil_socket_t fd,
                              struct sockaddr *sa, int socklen, void *user_data);
    static void WriteEndCallback(struct bufferevent *bev, void *user_data);
    static void CloseConnCallback(struct bufferevent *bev, short events, void *user_data);
    static void SignalCallback(evutil_socket_t sig, short events, void *user_data);
    static void readSock(struct bufferevent* bev , void *tmp);
    unsigned short _cpuCount;
};

#endif //HIGHLOAD2DZ_SERVER_H
