#ifndef __MELTSHINE_MOUSEEVENTLISTENER_H__
#define __MELTSHINE_MOUSEEVENTLISTENER_H__

#include "EventListener.h"
namespace meltshine
{
	enum class MouseButtonState
	{
		MOUSE_NONE, MOUSE_DOWN, MOUSE_UP, MOUSE_MOVE, MOUSE_SCROLL
	};
	enum class MouseButton
	{
		BUTTON_NONE, BUTTON_LEFT, BUTTON_RIGHT, BUTTON_MIDDLE, BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_7, BUTTON_8
	};
	class MouseEvent : public Event
	{
	public:
		MouseEvent();
		virtual ~MouseEvent();

		MouseButton GetButton() const { return _button; };
		MouseButtonState GetButtonState() const { return _button_state; };
		void GetCursor(float& x, float& y) { x = _x; y = _y; };
		float GetCursorX() const { return _x; };
		float GetCursorY() const { return _y; };
		float GetScrollX() const { return _scroll_x; };
		float GetScrollY() const { return _scroll_y; };

	protected:
		MouseButtonState _button_state;
		MouseButton _button;
		float _x;
		float _y;
		float _scroll_x;
		float _scroll_y;

		friend class MouseEventListener;
		friend class InputHandler;
	};
	class MouseEventListener : public EventListener
	{
	protected:
		MouseEventListener();

	public:
		virtual ~MouseEventListener();

		static std::shared_ptr<MouseEventListener> Create();

		std::function<void(MouseButtonState, Event*)> _on_mouse_down;
		std::function<void(MouseButtonState, Event*)> _on_mouse_up;
		std::function<void(MouseButtonState, Event*)> _on_mouse_move;
		std::function<void(MouseButtonState, Event*)> _on_mouse_scroll;

	protected:
		// EventListener을(를) 통해 상속됨
		virtual void OnEvent(Event* evt) override;

		friend class EventDispatcher;
	};
}
#endif // !__MELTSHINE_MOUSEEVENTLISTENER_H__
