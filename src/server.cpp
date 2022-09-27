//
// Created by ilyas on 23.09.2022.
//

#include <iostream>
#include <utility>
#include <server.h>
#include <zconf.h>

#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <http/request.h>
#include <staticHander.h>

#include "Responses.h"

static const unsigned short PORT = 9995;
unsigned short forkNum = 0;
StaticHandler* handler;

Server::Server(int cpuCount, std::string rootDir, std::string defaultFile) {
    _cpuCount = cpuCount;
    handler = new StaticHandler(rootDir, defaultFile);
}

void Server::readSock(struct bufferevent* bev , void *tmp) {
    std::string result;
    size_t read = 0;
    char* buffer = new char[1000];
    while (read < 1000) {
        auto received = bufferevent_read(bev, buffer, 1000);
        result.append(buffer, received);
        read += received;
        if (result.find("\r\n\r\n") != std::string::npos) {
            break;
        }
    }
    delete[] buffer;

    auto req = http::Request(result);

    auto response = handler->handle(req);

    bufferevent_enable(bev, EV_WRITE);
    bufferevent_disable(bev, EV_READ);

    bufferevent_setcb(bev, NULL, WriteEndCallback, CloseConnCallback, NULL);

    auto resp = response.str();
    bufferevent_write(bev, resp.c_str(), resp.length());

}

void Server::AcceptConnect(struct evconnlistener *listener, evutil_socket_t fd,
                            struct sockaddr *sa, int socklen, void *user_data) {
    auto *base = static_cast<event_base *>(user_data);
    struct bufferevent *bev;

    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if (!bev) {
        std::cerr << "Error constructing bufferevent!" << std::endl;
        event_base_loopbreak(base);
        return;
    }
    bufferevent_setcb(bev, readSock, NULL, CloseConnCallback, NULL);


    bufferevent_enable(bev, EV_READ | EV_WRITE);
}

void Server::WriteEndCallback(struct bufferevent *bev, void *user_data) {
    struct evbuffer *output = bufferevent_get_output(bev);
    if (evbuffer_get_length(output) == 0) {
        std::cout << "Closed. Fork num: " << forkNum << std::endl;
        bufferevent_free(bev);
    }
}

void Server::Run() {
    struct event_base *base;
    struct evconnlistener *listener;
    struct event *signal_event;

    struct sockaddr_in sin = {0};

    base = event_base_new();
    if (!base) {
        std::cerr <<  "Could not initialize libevent!" << std::endl;
        return;
    }

    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);


    listener = evconnlistener_new_bind(base, this->AcceptConnect, (void *)base,
                                       LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
                                       (struct sockaddr*)&sin,
                                       sizeof(sin));
    if (!listener) {
        std::cerr << "Could not create a listener!" << std::endl;
        return;
    }

    for (int i = 1; i < _cpuCount; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            forkNum = i;
            break;
        } else if (pid < 0) {
            std::cerr << "Error during fork" << std::endl;
            return;
        }
    }

    signal_event = evsignal_new(base, SIGINT, SignalCallback, (void *)base);
    if (!signal_event || event_add(signal_event, NULL)<0) {
        std::cerr << "Could not create/add a signal event!" << std::endl;
        return;
    }

    std::cout << "Server inited" << std::endl;
    event_base_dispatch(base);

    std::cout << "Server stopped" << std::endl;

    evconnlistener_free(listener);
    event_free(signal_event);
    event_base_free(base);
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
    auto *base = static_cast<event_base *>(user_data);
    struct timeval delay = { 2, 0 };

    std::cout << "Caught an interrupt signal; exiting cleanly in two seconds." << std::endl;

    event_base_loopexit(base, &delay);
}

