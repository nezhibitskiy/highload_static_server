//
// Created by ilyas on 23.09.2022.
//

#include <iostream>
#include <server.h>
#include <zconf.h>

#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/event.h>
#include <http/request.h>
#include <staticHander.h>

static const unsigned short PORT = 8080;
StaticHandler* handler;

Server::Server(int cpuCount, std::string rootDir, std::string defaultFile) {
    _cpuCount = cpuCount;
    handler = new StaticHandler(rootDir, defaultFile);
}

Server::~Server() {
    delete handler;
}

void Server::readSock(struct bufferevent* bev , void *tmp) {
    std::string result;
    size_t read = 0;
    char* buffer = new char[150];
    while (read < 1000) {
        auto received = bufferevent_read(bev, buffer, 150);
        result.append(buffer, received);
        read += received;
        if (result.find("\r\n\r\n") != std::string::npos) {
            break;
        }
    }
    delete[] buffer;

    auto req = http::Request(result);

    auto response = handler->handle(req);

    auto resp = response.str();
    bufferevent_write(bev, resp.c_str(), resp.length());
}

void Server::AcceptConnect(struct evconnlistener *listener, evutil_socket_t fd,
                            struct sockaddr *sa, int socklen, void *user_data) {
    auto* base = static_cast<event_base *>(user_data);
    struct bufferevent *bev;

    printf("Received on (PID %d)\n", getpid());

    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if (!bev) {
        std::cerr << "Error constructing bufferevent!" << std::endl;
        event_base_loopbreak(base);
        return;
    }

    bufferevent_setcb(bev, readSock, WriteEndCallback, CloseConnCallback, base);
    bufferevent_enable(bev, EV_READ);
}

void Server::WriteEndCallback(struct bufferevent *bev, void *user_data) {
    struct evbuffer *output = bufferevent_get_output(bev);
    if (evbuffer_get_length(output) == 0) {
        bufferevent_free(bev);
    } else {
        std::cout << "Error" << std::endl;
    }
}


void Server::Run() {

    for (int i = 1; i < _cpuCount; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            break;
        } else if (pid < 0) {
            std::cerr << "Error during fork" << std::endl;
            return;
        }
    }
    struct event_base *listenBase;
    struct event *signal_event;
    struct evconnlistener *listener;

    struct sockaddr_in sin = {0};

    listenBase = event_base_new();
    if (!listenBase) {
        std::cerr <<  "Could not initialize libevent!" << std::endl;
        return;
    }

    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);


    signal_event = evsignal_new(listenBase, SIGINT, SignalCallback, (void *)listenBase);
    if (!signal_event || event_add(signal_event, NULL)<0) {
        std::cerr << "Could not create/add a signal event!" << std::endl;
        return;
    }

    listener = evconnlistener_new_bind(listenBase, this->AcceptConnect, (void *)listenBase,
                                       LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE_PORT, -1,
                                       (struct sockaddr*)&sin,
                                       sizeof(sin));
    if (!listener) {
        std::cerr << "Could not create a listener!" << std::endl;
        return;
    }
    std::cout << event_reinit(listenBase) << std::endl;


    std::cout << "Server inited" << std::endl;
    event_base_dispatch(listenBase);

    std::cout << "Server stopped" << std::endl;

    evconnlistener_free(listener);
    event_free(signal_event);
    event_base_free(listenBase);
}

void Server::CloseConnCallback(struct bufferevent *bev, short events, void *user_data) {
    if (events & BEV_EVENT_EOF) {
        std::cout << "Connection closed." << std::endl;
    } else if (events & BEV_EVENT_ERROR) {
        std::cout << "Got an error on the connection: " << strerror(errno) << std::endl;
    }
    bufferevent_free(bev);
}

void Server::SignalCallback(evutil_socket_t sig, short events, void *user_data) {
    auto *callbackBase = static_cast<event_base *>(user_data);
    struct timeval delay = { 2, 0 };

    std::cout << "Caught an interrupt signal; exiting cleanly in two seconds." << std::endl;

    event_base_loopexit(callbackBase, &delay);
}

