#ifndef __MELTSHINE_KEYBOARDEVENTLISTENER_H__
#define __MELTSHINE_KEYBOARDEVENTLISTENER_H__

#include "EventListener.h"
namespace meltshine
{
	class KeyboardEvent : public Event
	{
	public:
		KeyboardEvent(char key_code, bool is_pressed);
		virtual ~KeyboardEvent();

		char GetKeyCode() const { return _key_code; };
		bool IsPressed() const { return _is_pressed; };
		bool IsReleased() const { return !_is_pressed; };

	protected:
		char _key_code;
		bool _is_pressed;

		friend class KeyboardEventListener;
	};

	class KeyboardEventListener : public EventListener
	{
	protected:
		KeyboardEventListener();

	public:
		virtual ~KeyboardEventListener();
		static std::shared_ptr<KeyboardEventListener> Create();

		std::function<void(char, Event*)> _on_key_pressed;
		std::function<void(char, Event*)> _on_key_released;

	protected:
		// EventListener을(를) 통해 상속됨
		virtual void OnEvent(Event* evt) override;

		friend class EventDispatcher;
	};
}
#endif // !__MELTSHINE_KEYBOARDEVENTLISTENER_H__
