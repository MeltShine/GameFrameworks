#include "Application.h"

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return meltshine::Application::GetInstance()->WndProc(hWnd,
		message,
		wParam,
		lParam);
}

namespace meltshine
{
	Application::Application()
		: _hwnd()
		, _hinst()
		, _screen_width()
		, _screen_height()
	{
	}


	Application::~Application()
	{
	}

	Application* Application::GetInstance()
	{
		static Application instance;
		return &instance;
	}

	bool Application::Init(int width, int height, const TCHAR* title, HINSTANCE hinst)
	{
		_screen_width = width;
		_screen_height = height;
		_hinst = hinst;

		TCHAR class_name[MAX_CLASS_NAME];
		wsprintf(class_name, TEXT("%s_class"), title);

		// ������ Ŭ���� ��� �ڵ�
		{
			WNDCLASSEX wcex = {};
			wcex.cbSize = sizeof(wcex);
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = MainWndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = _hinst;
			wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
			wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);
			wcex.hCursor = LoadCursor(0, IDC_ARROW);
			wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
			wcex.lpszMenuName = NULL;
			wcex.lpszClassName = class_name;

			RegisterClassEx(&wcex);
		}

		// ������ ���� �ڵ�
		{
			// �۾� ������ �Է¹��� ũ�Ⱑ �ǵ��� ������ ũ�⸦ ����մϴ�.
			RECT rect = { 0,0,width,height };
			AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
			const int w = rect.right - rect.left;
			const int h = rect.bottom - rect.top;
			// ������ �ʱ� ���� ��ġ�� ����� �߾����� �����մϴ�.
			const int x = GetSystemMetrics(SM_CXSCREEN / 2 - w / 2);
			const int y = GetSystemMetrics(SM_CYSCREEN / 2 - h / 2);

			_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
				class_name,
				title,
				WS_OVERLAPPEDWINDOW,
				x, y, w, h,
				nullptr,
				nullptr,
				_hinst,
				nullptr);

			// �����찡 ���������� �����Ǿ����� Ȯ���մϴ�.
			if (_hwnd == NULL)
			{
				return false;
			}
		}
		// �����Լ� ȣ��
		if (!OnInit())
		{
			return false;
		}
		
		ShowWindow(_hwnd, SW_SHOW);
		UpdateWindow(_hwnd);
		return true;
	}

	bool Application::Init(int width, int height, const TCHAR* title)
	{
		return Init(width, height, title, GetModuleHandle(NULL));
	}

	int Application::Run()
	{
		MSG msg = {};
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// �����Լ� ȣ��
				OnRun();

				// �ݹ��Լ� ȣ��
				if (_on_run_callback)
				{
					_on_run_callback();
				}
			}
		}
		return static_cast<int>(msg.wParam);
	}

	void Application::GetScreenSize(int& w, int& h)
	{
		w = _screen_width;
		h = _screen_height;
	}

	bool Application::OnInit()
	{
		return true;
	}

	void Application::OnRun()
	{
	}

	LRESULT Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (_on_wnd_proc_callback)
		{
			_on_wnd_proc_callback(hWnd, message, wParam, lParam);
		}

		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		return 0;
	}

}