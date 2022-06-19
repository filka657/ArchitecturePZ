#include "Inet.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

CEvent Inet(bool* flag1, SOCKET* sock, SOCKET* listener)
{
    if (*flag1)
    {
        *flag1 = false;
        WSADATA wsaData;

        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            printf("WSAStartup failed with error: %d\n", iResult);
        }

        sockaddr_in mem;
        in_addr ip_to_num;

        iResult = inet_pton(AF_INET, "127.0.0.1", &ip_to_num);
        ZeroMemory(&mem, sizeof(mem));
        mem.sin_family = AF_INET;
        mem.sin_port = htons(1234);
        mem.sin_addr = ip_to_num;        

        *listener = socket(AF_INET, SOCK_STREAM, 0);
        if (bind(*listener, (sockaddr*)&mem, sizeof(mem)) < 0)
        {
            perror("bind");            
        }
        iResult = listen(*listener, SOMAXCONN);



        int mem_size = sizeof(mem);
        *sock = accept(*listener, (sockaddr*)&mem, &mem_size);
    }
    int state = 0;
    short bytes_read = 0;
    while (1)
    {
        bytes_read = recv(*sock, (char*)&state, sizeof(state), 0);
        cout << "Received message: " << state << endl;
        if (state == 0) return CEvent(Event::none);
        else if (state == 1) return CEvent(Event::press_start1);
        else if (state == 2) return CEvent(Event::press_stop1);
        else if (state == 3) return CEvent(Event::waiting_command);
        else if (state == 4) return CEvent(Event::receive_move);
        else if (state == 5) return CEvent(Event::receive_turn);
        else if (state == 6) return CEvent(Event::set_hand);
        else if (state == 7) return CEvent(Event::receive_spray);
        else if (state == 8) return CEvent(Event::on_error);
        else if (state == 9) return CEvent(Event::move_error);
        else if (state == 10) return CEvent(Event::turn_error);
        else if (state == 11) return CEvent(Event::hand_error);
        else return CEvent(Event::spray_error);
    }
    closesocket(*sock);
    closesocket(*listener);
    WSACleanup();
}
