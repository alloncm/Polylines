#pragma once
#include <chrono>
class Timer
{
public:
	Timer()
	{
		last = std::chrono::high_resolution_clock::now();
	}
	float Tick()
	{
		auto old = last;
		last = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> time = last - old;
		return time.count();
	}
private:
	std::chrono::high_resolution_clock::time_point last;
};