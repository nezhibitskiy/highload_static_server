//
// Created by ilyas on 24.09.2022.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
using namespace std;
//Client side
int main(int argc, char *argv[])
{
    char *serverIp = "0.0.0.0"; int port = 9994;
    //create a message buffer
    char msg[1500];
    //setup a socket and connection tools
    struct hostent* host = gethostbyname(serverIp);
    sockaddr_in sendSockAddr;
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr =
            inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);


    for (int i = 0; i < 10000; i++) {
        int clientSd = socket(AF_INET, SOCK_STREAM, 0);
        //try to connect...
        int status = connect(clientSd,
                             (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
        if(status < 0)
        {
            cout<<"Error connecting to socket!"<<endl;
            return -1;
        }
        cout << "Connected to the server!" << endl;
        int bytesRead, bytesWritten = 0;
        struct timeval start1, end1;
        gettimeofday(&start1, NULL);

        memset(&msg, 0, sizeof(msg));//clear the buffer

        bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
        cout << "Awaiting server response..." << endl;
        memset(&msg, 0, sizeof(msg));//clear the buffer
        bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
        if(!strcmp(msg, "exit"))
        {
            cout << "Server has quit the session" << endl;
        }
        gettimeofday(&end1, NULL);
        close(clientSd);

        cout << "Elapsed time: " << (end1.tv_usec- start1.tv_usec)
             << " usecs" << endl;
    }


    return 0;
}
