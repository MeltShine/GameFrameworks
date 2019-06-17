#include "Timer.h"

namespace meltshine
{
	Timer::Timer()
		: _previous(std::chrono::system_clock::now())
		, _delta_time()
	{
	}


	Timer::~Timer()
	{
	}

	void Timer::CalculateDeltaTime()
	{
		auto current = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsed_time = (current - _previous);
		_delta_time = elapsed_time.count();
		_previous = current;
	}

}