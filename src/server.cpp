//
// Created by ilyas on 23.09.2022.
//

#include <iostream>
#include <server.h>
#include <zconf.h>

Server::Server(int cpuCount) {
    std::cout << "Server inited" << std::endl;

    for (int i = 0; i < cpuCount; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            std::cout << "I am new fork" << std::endl;
            break;
        } else if (pid < 0) {
            std::cout << "bad fork " << std::endl;
            return;
        }
        std::cout << "Created fork with pid: " << pid << std::endl;
    }
}

Server::~Server() {
    std::cout << "Server removed" << std::endl;
}