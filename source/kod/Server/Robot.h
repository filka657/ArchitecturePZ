#pragma once
class Robot
{
private:
    int charge;
public:
    void on();
    void off();
    void move_on();
    void move_off();
    void move_forward();
    void turn_left();
    void spray();
};

