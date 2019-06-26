#ifndef __MELTSHINE_EVENTLISTENER_H__
#define __MELTSHINE_EVENTLISTENER_H__

namespace meltshine
{
	enum EventType { ET_NONE, ET_KEYBOARD, ET_MOUSE, ET_COMMAND };
	class Event
	{
	public:
		Event();
		Event(EventType type);
		virtual ~Event();

		EventType GetType() const { return type_; };
		bool IsStopped() const { return is_stopped_; };
		void StopPropagation() { is_stopped_ = true; };

	protected:
		EventType type_;
		bool is_stopped_;
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
