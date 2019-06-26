#include "KeyboardEventListener.h"

namespace meltshine
{
	KeyboardEvent::KeyboardEvent(
		char key_code, 
		bool is_pressed)
		: Event(ET_KEYBOARD)
		, _key_code(key_code)
		, _is_pressed(is_pressed)
	{
	}

	KeyboardEvent::~KeyboardEvent()
	{
	}

	KeyboardEventListener::KeyboardEventListener()
		: EventListener(ET_KEYBOARD)
	{
	}

	KeyboardEventListener::~KeyboardEventListener()
	{
	}

	void KeyboardEventListener::OnEvent(Event* evt)
	{
		if (evt->GetType() != ET_KEYBOARD)
		{
			return;
		}

		auto kbd_evt = static_cast<KeyboardEvent*>(evt);
		if (kbd_evt->_is_pressed && _on_key_pressed)
		{
			_on_key_pressed(kbd_evt->_key_code, kbd_evt);
		}
		else if(!kbd_evt->_is_pressed && _on_key_pressed)
		{
			_on_key_released(kbd_evt->_key_code, kbd_evt);
		}
	}
}