#include "RobotStates.h"
#include <iostream>
#include "Pc.h"
#include "Camera.h"
#include "Robot.h"
#include "Hand.h"
#include "Spray.h"
#include "Estate.h"
#include "Event.h"
#include "CEvent.h"
#include "System.h"
using namespace std;

RobotStates::RobotStates()
{
	state = Estate::Off;
}

void RobotStates::detectProcess(CEvent e)
{
    if (charge > 0 && charge <= 100)
    {
        switch (state)
        {
        case Estate::Off:
            if (e.event == press_start1)
            {
                state = Estate::On;
                system->press_start();
                cout << "Состояние: " << state << " -- ON" << endl;
            }
            break;
        case Estate::On:
            if (e.event == waiting_command)
            {
                state = Estate::waiting;
                system->waiting();
                cout << "Состояние: " << state << " -- Waiting" << endl;
            }
            else if (e.event == on_error)
            {
                state = Estate::Error;
                cout << "Состояние: " << state << " -- Error" << endl;
            }
            break;
        case Estate::waiting:
            if (e.event == press_stop1)
            {
                state = Estate::Off;
                system->press_stop();
                cout << "Состояние: " << state << " -- Off" << endl;
            }
            else if (e.event == receive_move)
            {
                state = Estate::move_forward;
                system->move();
                cout << "Состояние: " << state << " -- Moving forward" << endl;
            }
            break;
        case Estate::move_forward:
            if (e.event == receive_turn)
            {
                state = Estate::turn_left;
                system->turning();
                cout << "Состояние: " << state << " -- Turn left" << endl;
            }
            else if (e.event == move_error)
            {
                state = Estate::Error;
                cout << "Состояние: " << state << " -- Error" << endl;
            }
            break;
        case Estate::turn_left:
            if (e.event == set_hand)
            {
                state = Estate::settingHand;
                system->setHand();
                cout << "Состояние: " << state << " -- Setting hand" << endl;
            }
            else if (e.event == turn_error)
            {
                state = Estate::Error;
                cout << "Состояние: " << state << " -- Error" << endl;
            }
            break;
        case Estate::settingHand:
            if (e.event == receive_spray)
            {
                state = Estate::spraying;
                system->do_spray();
                cout << "Состояние: " << state << " -- Spraying" << endl;
            }
            else if (e.event == hand_error)
            {
                state = Estate::Error;
                cout << "Состояние: " << state << " -- Error" << endl;
            }
            break;
        case Estate::spraying:
            if (e.event == spray_error)
            {
                state = Estate::Error;
                cout << "Состояние: " << state << " -- Error" << endl;
            }
            break;
        }
    }
    else if (charge <= 0) {
        state = Estate::Off;
        system->press_stop();
    }
}
