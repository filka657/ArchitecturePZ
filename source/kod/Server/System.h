#pragma once
#include <iostream>
#include "Pc.h"
#include "Camera.h"
#include "Robot.h"
#include "Hand.h"
#include "Spray.h"
#include "Estate.h"
#include "Event.h"
#include "CEvent.h"

class System
{
private:
    Pc pc;
    Camera cam;
    Robot robo;
    Hand hand;
    Spray spr;

public:
    void press_start();
    void move();
    void waiting();
    void setHand();
    void do_spray();
    void turning();
    void press_stop();
};

