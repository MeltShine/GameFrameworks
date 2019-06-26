#ifndef __MELTSHINE_INPUTHANDLER_H__
#define __MELTSHINE_INPUTHANDLER_H__
#include <array>
#include <Windows.h>
namespace meltshine
{
	class InputHandler
	{
	private:
		InputHandler();

	public:
		~InputHandler();

		bool Init(HWND window);
		bool GetKeyDown(const int& key_code) const;
		bool GetKeyPress(const int& key_code) const;
		bool GetKeyRelease(const int& key_code) const;
		bool GetKeyUp(const int& key_code) const;
		long GetCursorX() const { return _cursor_x; };
		long GetCursorY() const { return _cursor_y; };
		void GetCursorLocation(int& x, int& y);

	private:
		HWND _window;
		int _cursor_x;
		int _cursor_y;
		std::array<bool, 256> _key_state;
		std::array<bool, 256> _previous_key_state;

		void AcquireInput();
		void OnWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		inline bool KeyPressed(const int& key_code)
		{
			return GetAsyncKeyState(key_code) & 0x8000;
		};

		friend class Core;
	};

	
}
#endif // !__MELTSHINE_INPUTHANDLER_H__
