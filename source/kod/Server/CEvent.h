#pragma once
#include "Event.h"
struct CEvent
{
	Event event;
	CEvent(Event t) : event(t) {}
};

