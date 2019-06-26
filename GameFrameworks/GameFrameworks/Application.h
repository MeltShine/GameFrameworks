#ifndef __MELTSHINE_APPLICATION_H__
#define __MELTSHINE_APPLICATION_H__
#include <Windows.h>
#include <functional>

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
namespace meltshine
{
	class Application
	{
	public:
		Application(const Application&) = delete;
		void operator=(const Application&) = delete;
		virtual ~Application();

		// �̱���
		static Application* GetInstance();

		// ����Լ�
		bool Init(int width,
			int height,
			const TCHAR* title,
			HINSTANCE hinst);
		bool Init(int width,
			int height,
			const TCHAR* title);
		int Run();

		// ��� (Getter)
		inline HWND GetWindowHandle() const { return _hwnd; }
		inline HINSTANCE GetInstanceHandle() const { return _hinst; }
		inline int GetScreenWidth() const { return _screen_width; }
		inline int GetScreenHeight() const { return _screen_height; }
		void GetScreenSize(int& w, int& h);

		// ��� (Setter)
		inline void SetOnRunCallback(std::function<void()> callback)
		{
			_on_run_callback = std::move(callback);
		}

		inline void SetOnWndProcCallback(std::function<void(HWND, UINT, WPARAM, LPARAM)> callback)
		{
			_on_wnd_proc_callback = std::move(callback);
		}

	protected:
		HWND _hwnd;
		HINSTANCE _hinst;
		int _screen_width;
		int _screen_height;

		// �ݹ��Լ�
		std::function<void()> _on_run_callback;
		std::function<void(HWND, UINT, WPARAM, LPARAM)> _on_wnd_proc_callback;

		// �̱����� ���� ���ѵ� ������
		Application();

		// ��������Լ�
		virtual bool OnInit();
		virtual void OnRun();
		virtual LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		// friends
		friend LRESULT CALLBACK::MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}
#endif // !__MELTSHINE_APPLICATION_H__