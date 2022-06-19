#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")
using namespace std;

int main()
{
    cout << "Commands:" << endl;
    cout << "1 - press_start1" << endl;
    cout << "2 - press_stop1" << endl;
    cout << "3 - waiting_command" << endl;
    cout << "4 - receive_move" << endl;
    cout << "5 - receive_turn" << endl;
    cout << "6 - set_hand" << endl;
    cout << "7 - receive_spray" << endl;
    cout << "8 - on_error" << endl;
    cout << "9 - move_error" << endl;
    cout << "10 - turn_error" << endl;
    cout << "11 - hand_error" << endl;
    cout << "12 - spray_error" << endl;
    cout << endl;

    WSADATA wsaData;
    SOCKET Socket;
    sockaddr_in mem;
    in_addr ip_to_num;
    ///
    int iResult = inet_pton(AF_INET, "127.0.0.1", &ip_to_num);
    if (iResult <= 0)
    {
        cout << "Covertation the character string to address - ERROR";
        return 1;
    }
    ZeroMemory(&mem, sizeof(mem));
    mem.sin_family = AF_INET;
    mem.sin_port = htons(1234);
    mem.sin_addr = ip_to_num;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        cout << "WSAStartup failed with error: %d\n", iResult;
        return 0;
    }
    Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (Socket == INVALID_SOCKET)
    {
            cout << "socket failed with error: %ld\n", WSAGetLastError();
            WSACleanup();
            return 1;
    }
       
    iResult = connect(Socket, (sockaddr*)&mem, sizeof(mem));
    if (iResult == SOCKET_ERROR)
    {
        closesocket(Socket);
        Socket = INVALID_SOCKET;
        return 1;
    }

    int state = 0;
    while (1)
    {
        cout << "ENTER the massege to server:";
        cin >> state;
        iResult = send(Socket, (char*)&state, sizeof(state), 0);
        if (iResult == SOCKET_ERROR)
        {
            cout << "send failed with error: %d\n" << WSAGetLastError();
            closesocket(Socket);
            WSACleanup();
            return 1;
        }
    }
    closesocket(Socket);
    WSACleanup();

    return 0;
}