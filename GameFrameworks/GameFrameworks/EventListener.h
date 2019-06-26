#ifndef __MELTSHINE_EVENTLISTENER_H__
#define __MELTSHINE_EVENTLISTENER_H__

#include <memory>
#include <functional>
namespace meltshine
{
	enum class EventType { EVENT_NONE, EVENT_KEYBOARD, EVENT_MOUSE, EVENT_COMMAND };
	class Event
	{
	public:
		Event();
		Event(EventType type);
		virtual ~Event();

		EventType GetType() const { return _type; };
		bool IsStopped() const { return _is_stopped; };
		void StopPropagation() { _is_stopped = true; };

	protected:
		EventType _type;
		bool _is_stopped;

		friend class EventDispatcher;
	};
	class EventListener
	{
	public:
		EventListener();
		EventListener(EventType type);
		virtual ~EventListener();

		virtual void OnEvent(Event* evt) = 0;
		EventType GetType() const { return _type; };
		bool IsRegistered() const { return _is_registered; };

	protected:
		EventType _type;
		bool _is_registered;

		friend class EventDispatcher;
	};
}
#endif // !__MELTSHINE_EVENTLISTENER_H__
