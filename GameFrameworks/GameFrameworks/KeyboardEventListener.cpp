#include "KeyboardEventListener.h"

namespace meltshine
{
	KeyboardEvent::KeyboardEvent(
		char key_code, 
		bool is_pressed)
		: Event(EventType::EVENT_KEYBOARD)
		, _key_code(key_code)
		, _is_pressed(is_pressed)
	{
	}

	KeyboardEvent::~KeyboardEvent()
	{
	}

	KeyboardEventListener::KeyboardEventListener()
		: EventListener(EventType::EVENT_KEYBOARD)
	{
	}

	KeyboardEventListener::~KeyboardEventListener()
	{
	}

	std::shared_ptr<KeyboardEventListener> KeyboardEventListener::Create()
	{
		return std::shared_ptr<KeyboardEventListener>(new KeyboardEventListener);
	}

	void KeyboardEventListener::OnEvent(Event* evt)
	{
		auto kbd_evt = static_cast<KeyboardEvent*>(evt);
		if (kbd_evt->_is_pressed && _on_key_pressed)
		{
			_on_key_pressed(kbd_evt->_key_code, kbd_evt);
		}
		else if(!kbd_evt->_is_pressed && _on_key_pressed)
		{
			_on_key_released(kbd_evt->_key_code, kbd_evt);
		}
		else
		{
			evt->StopPropagation();
		}
	}
}