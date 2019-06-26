#include "InputHandler.h"

namespace meltshine
{
	InputHandler::InputHandler()
		: _window(nullptr)
		, _cursor_x(0)
		, _cursor_y(0)
	{
		_key_state.fill(0);
		_previous_key_state.fill(0);
	}

	InputHandler::~InputHandler()
	{
	}

	void InputHandler::AcquireInput()
	{
		// 이전 키 상태들을 저장합니다.
		_previous_key_state.swap(_key_state);
		
		// 현재 키 상태들을 저장합니다.
		for (size_t i = 0; i < _key_state.size(); ++i)
		{
			_key_state[i] = KeyPressed(static_cast<int>(i));
		}

		// 마우스 커서 위치를 갱신합니다.
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(_window, &pt);
		_cursor_x = pt.x;
		_cursor_y = pt.y;
	}

	void InputHandler::OnWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_MOUSEMOVE:
			break;
		case WM_MOUSEWHEEL:
			break;
		default:
			break;
		}
	}

	bool InputHandler::Init(HWND window)
	{
		if (window)
		{
			_window = window;
		}
		return false;
	}

	bool InputHandler::GetKeyDown(const int& key_code) const
	{
		return _previous_key_state[key_code] && _key_state[key_code];
	}

	bool InputHandler::GetKeyPress(const int& key_code) const
	{
		return !_previous_key_state[key_code] && _key_state[key_code];
	}

	bool InputHandler::GetKeyRelease(const int& key_code) const
	{
		return _previous_key_state[key_code] && !_key_state[key_code];
	}

	bool InputHandler::GetKeyUp(const int& key_code) const
	{
		return !_previous_key_state[key_code] && !_key_state[key_code];
	}

	void InputHandler::GetCursorLocation(int& x, int& y)
	{
	}

}