#ifndef __MELTSHINE_TIMER_H__
#define __MELTSHINE_TIMER_H__
#include <chrono>
namespace meltshine
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		void  CalculateDeltaTime();
		float GetDeltaTime() const { return _delta_time; };

	private:
		std::chrono::system_clock::time_point _previous;
		float _delta_time;

	};
}
#endif // !__MELTSHINE_TIMER_H__