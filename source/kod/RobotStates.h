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
#include "System.h"
class RobotStates
{
private:
    int charge = 50;
    Estate state;
    System* system;
public:
    RobotStates();
    void detectProcess(CEvent e);
};

