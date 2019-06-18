#ifndef __MELTSHINE_EVENTDISPATCHER_H__
#define __MELTSHINE_EVENTDISPATCHER_H__
#include <memory>
#include <list>
namespace meltshine
{
	class Event;
	class EventListener;
	class EventDispatcher
	{
	public:
		EventDispatcher();
		~EventDispatcher();

		static EventDispatcher& GetInstance();

		void AddEventListener(std::shared_ptr<EventListener> listener);
		void RemoveEventListener(std::shared_ptr<EventListener> listener);
		void RemoveAllEventListener();
		void DispatchEvent(Event* evt);

	private:
		std::list<std::shared_ptr<EventListener>> listeners_;

	};
}
#endif // !__MELTSHINE_EVENTDISPATCHER_H__
