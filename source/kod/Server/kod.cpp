#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include "Inet.h"

#include "Pc.h"
#include "Camera.h"
#include "Robot.h"
#include "Hand.h"
#include "Spray.h"
#include "Estate.h"
#include "Event.h"
#include "CEvent.h"
#include "System.h"
#include "RobotStates.h"


using namespace std;

class Strategy
{
public:
    virtual CEvent get_event() = 0;
};

class cmdStrategy : public Strategy
{
public:
    CEvent get_event();
};

class inetStrategy : public Strategy
{
private:
    const short BUFF_SIZE = 1024;
    WSADATA wsData;
    SOCKET sock, listener;
    SOCKET* sock1 = &sock;
    SOCKET* listener1 = &listener;

    bool flag = true;
    bool* flag1 = &flag;
        
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsData);
    in_addr ip_to_num;
public:
    inetStrategy()
    {
        listener = socket(AF_INET, SOCK_STREAM, 0);
        iResult = inet_pton(AF_INET, "127.0.0.1", &ip_to_num);
    }
    CEvent get_event()
    {
        return Inet(flag1, sock1, listener1);
    }
};

CEvent cmdStrategy::get_event()
{
    int val;

    cin >> val;
    cout << endl << "-------------------" << endl;
    
    if (val == 0) return CEvent(Event::none);
    else if (val == 1) return CEvent(Event::press_start1);
    else if (val == 2) return CEvent(Event::press_stop1);
    else if (val == 3) return CEvent(Event::waiting_command);
    else if (val == 4) return CEvent(Event::receive_move);
    else if (val == 5) return CEvent(Event::receive_turn);
    else if (val == 6) return CEvent(Event::set_hand);
    else if (val == 7) return CEvent(Event::receive_spray);
    else if (val == 8) return CEvent(Event::on_error);
    else if (val == 9) return CEvent(Event::move_error);
    else if (val == 10) return CEvent(Event::turn_error);
    else if (val == 11) return CEvent(Event::hand_error);
    else return CEvent(Event::spray_error);
}

int main()
{
    setlocale(LC_ALL, "ru");
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
    cout << "Enter the command: " << endl;

    RobotStates Oleg;
    Strategy* cmd = new cmdStrategy();
    Strategy* inet = new inetStrategy();
    
    //
    while (1)
    {
        CEvent t = inet->get_event();

        Oleg.detectProcess(t);
    }
    return 0;
}