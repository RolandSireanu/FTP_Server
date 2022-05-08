#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <thread>
#include <ThreadSafeDeque.h>
#ifdef EnableTests
    #include<gtest/gtest.h>
#endif

constexpr unsigned int SERVER_PORT = 10000;
constexpr unsigned int  MAXLINE = 4096;
using SA = struct sockaddr;
TSDeque<int> tsDeque;

void HandleConnection()
{
    char recvline[MAXLINE+1];
    size_t bytes_read = 0;
    socklen_t addr_len;
    char buff[MAXLINE+1];
    int n = 0;

    
    std::cout << "Connection accepted" << std::endl;

    do
    {
        std::shared_ptr<int> connFd = tsDeque.pop();
        if(connFd != nullptr)
        {
            memset(recvline, 0 , MAXLINE);
            memset(buff, 0, MAXLINE);
            n = 0;

            do
            {                
                std::cout << "reading from fd "<< *connFd << "..." << std::endl;
                bytes_read = read(*connFd, recvline, MAXLINE-1);
                
                // out << recvline;
                std::cout << "read result = " << n << std::endl;
                if(recvline[bytes_read-1] == '\n')
                    break;
                memset(recvline, 0 , MAXLINE);

            } while (bytes_read > 0);
        

        if (bytes_read < 0)
            throw std::runtime_error("Read error !");
        snprintf((char*)buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\nHello");   
        write(*connFd, (char*)buff, strlen((char*)buff));
        close(*connFd);
        }

    } while(1);    
}


int main(int ac, char** av)
{

    #ifdef EnableTests
        testing::InitGoogleTest(&ac, av);
        return RUN_ALL_TESTS();
    #else
        
        int listenfd, connfd, n;
        struct sockaddr_in serverAddr;
        std::thread threads[10];
        int thCounter = 0;
        
        threads[0] = std::thread(HandleConnection);
        threads[1] = std::thread(HandleConnection);
        //threads[0] = std::thread(HandleConnection);

        if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)    
            throw std::runtime_error("Socket creation failed ");

        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serverAddr.sin_port = htons(SERVER_PORT);

        if((bind(listenfd, (SA*) &serverAddr, sizeof(serverAddr))) < 0)
            throw std::runtime_error("Bind failed ");

        if((listen(listenfd,10)) < 0)
            throw std::runtime_error("Listen error ");

        

        while(1)
        {
            struct sockaddr_in addr;
            socklen_t addr_len;

            std::cout << "Waiting for a connection on port " << SERVER_PORT << std::endl;
            fflush(stdout);

            connfd = accept(listenfd, (SA*)&addr, &addr_len);
            tsDeque.push(connfd);
            // threads[thCounter++] = std::thread{HandleConnection, connfd};
        
        }
    #endif
}