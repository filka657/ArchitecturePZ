#include <iostream>
using namespace std;


class PC {
    public:
        void ask() {}
        void answer() {}
        void detect_graffiti() {}
};
class Camera {
    public:
        void take_picture() {}
};
class Robot {
    private:
        int charge;
    public:
        void on() {}
        void off() {}
        void moveOn() {}
        void moveOff() {}
        void move_forward() {}
        void turn_left() {}
        void spray() {}    
};
class Hand {
    public:
        void up() {}
        void down() {}
        void left() {}
        void right() {}
};
class Spray {
    public:
        void on() {}
        void off() {}
};



class System : public Robot {
    private:        
        PC pc;
        Camera cam;
        Robot robo;
        Hand hand;
        Spray spr;

    public:
        void press_start() {}
        void move() {}
        void waiting() {}
        void setHand() {}
        void do_spray() {}
        void turning() {}
        void press_stop() {}
};




enum Estate
{
    Off = 0,
    On = 1,
    Error = 2,
    waiting = 3,
    move_forward = 4,
    turn_left = 5,
    settingHand = 6,
    spraying = 7,
    
};
enum Event
{
    none = 0,
    press_start1 = 1,
    press_stop1 = 2,
    waiting_command = 3,
    receive_move = 4,
    receive_turn = 5,
    set_hand = 6,
    receive_spray = 7,
    on_error = 8,
    move_error = 9,
    turn_error = 10,
    hand_error = 11,
    spray_error = 12,  
};
struct CEvent
{
    Event event;
    CEvent(Event t) : event(t) {}
};

class RobotStates : System
{
    private:
        int charge = 50;
        Estate state;

    public:
        RobotStates()
        {
            state = Estate::Off;
        }
        void detectProcess(CEvent e)
        {
            if (charge > 0 && charge <= 100) {
                switch (state)
                {
                case Estate::Off:
                    if (e.event == press_start1)
                    {
                        state = Estate::On;
                        press_start();
                        cout << "Состояние: " << state << " -- ON" << endl;
                    }
                    break;
                case Estate::On:
                    if (e.event == waiting_command)
                    {
                        state = Estate::waiting;
                        waiting();
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
                        press_stop();
                        cout << "Состояние: " << state << " -- Off" << endl;
                    }
                    else if (e.event == receive_move)
                    {
                        state = Estate::move_forward;
                        move();
                        cout << "Состояние: " << state << " -- Moving forward" << endl;
                    }
                    break;
                case Estate::move_forward:
                    if (e.event == receive_turn)
                    {
                        state = Estate::turn_left;
                        rotating();
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
                        setHand();
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
                        do_spray();
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
                press_stop();
            }
        }
};

CEvent get_event()
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
    else if (val == 12) return CEvent(Event::spray_error);
}

int main()
{
    setlocale(LC_ALL, "ru");
    RobotStates Oleg;
    while (1)
    {
        CEvent t = get_event();
        Oleg.detectProcess(t);
    }
    cout << "Hello World" << endl;

    System rob1{};
    rob1.press_start();
    rob1.press_stop();
    cout << "Hello, leather bag!" << endl;
    return 0;
}