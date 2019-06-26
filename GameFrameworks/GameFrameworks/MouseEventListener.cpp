#include "MouseEventListener.h"

namespace meltshine
{
	MouseEvent::MouseEvent()
		: Event(EventType::EVENT_MOUSE)
		, _button(MouseButton::BUTTON_NONE)
		, _button_state(MouseButtonState::MOUSE_NONE)
		, _x(0.f)
		, _y(0.f)
		, _scroll_x(0.f)
		, _scroll_y(0.f)
	{
	}

	MouseEvent::~MouseEvent()
	{
	}

	MouseEventListener::MouseEventListener()
		: EventListener(EventType::EVENT_MOUSE)
	{
	}

	MouseEventListener::~MouseEventListener()
	{
	}

	std::shared_ptr<MouseEventListener> MouseEventListener::Create()
	{
		return std::shared_ptr<MouseEventListener>(new MouseEventListener);
	}

	void MouseEventListener::OnEvent(Event* evt)
	{
		auto mouse_evt = static_cast<MouseEvent*>(evt);
		switch (mouse_evt->_button_state)
		{
		case MouseButtonState::MOUSE_DOWN:
			if (_on_mouse_down)
			{
				_on_mouse_down(mouse_evt->_button_state, evt);
			}
			break;
		case MouseButtonState::MOUSE_UP:
			if (_on_mouse_up)
			{
				_on_mouse_up(mouse_evt->_button_state, evt);
			}
			break;
		case MouseButtonState::MOUSE_MOVE:
			if (_on_mouse_move)
			{
				_on_mouse_move(mouse_evt->_button_state, evt);
			}
			break;
		case MouseButtonState::MOUSE_SCROLL:
			if (_on_mouse_scroll)
			{
				_on_mouse_scroll(mouse_evt->_button_state, evt);
			}
			break;
		case MouseButtonState::MOUSE_NONE:
		default:
			evt->StopPropagation();
			break;
		}
	}
}