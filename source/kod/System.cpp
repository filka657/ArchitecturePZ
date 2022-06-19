#include "System.h"
#include <iostream>
#include "Pc.h"
#include "Camera.h"
#include "Robot.h"
#include "Hand.h"
#include "Spray.h"
#include "Estate.h"
#include "Event.h"
#include "CEvent.h"
using namespace std;

void System::press_start()
{
	robo.on();
}

void System::move()
{
	robo.move_on();
	robo.move_forward();
	robo.move_off();
}

void System::waiting() {}

void System::setHand()
{
	hand.up();
	hand.down();
	hand.right();
	hand.left();
}

void System::do_spray()
{
	spr.on();
	spr.off();
}

void System::turning()
{
	robo.turn_left();
}

void System::press_stop()
{
	robo.off();
}
