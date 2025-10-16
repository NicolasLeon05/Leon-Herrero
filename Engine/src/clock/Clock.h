#pragma once

#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<Clock> TimePoint;
typedef std::chrono::duration<float, std::milli> Miliseconds;

class MyClock
{
private:
	static float deltaTime;
	static TimePoint previous;
	static TimePoint current;
	static Miliseconds delta;

public:
	MyClock();
	~MyClock();

	static void InitClock();

	static void UpdateDeltaTime();

	static float GetDeltaTime();
};