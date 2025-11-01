#include "Clock.h"

#include <iostream>

float MyClock::deltaTime = 0.0f;
TimePoint MyClock::previous;
TimePoint MyClock::current;
Miliseconds MyClock::delta;

MyClock::MyClock()
{

}

MyClock::~MyClock()
{

}

void MyClock::InitClock()
{
	previous = Clock::now();
}

void MyClock::UpdateDeltaTime()
{
	current = Clock::now();
	delta = current - previous;
	previous = current;

	deltaTime = delta.count();
}

float MyClock::GetDeltaTime()
{
	return deltaTime;
}
