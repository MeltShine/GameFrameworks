#include "Core.h"

#include "PathUtil.h"
#include "ConfigUtil.h"
#include "Direct3D.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "SceneController.h"
#include "Scene.h"
#include "Timer.h"
#include "TextureCache.h"
#include "FontCache.h"
#include "AudioPlayer.h"

#ifdef _DEBUG
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
// #include <new.h>������ operator new�� malloc�� 
// Derived�ؼ� ���� �� ���, ��� �� �� ����.
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif

namespace meltshine
{
	Core::Core()
		: _window(nullptr)
		, _instance(nullptr)
	{
	}

	Core::~Core()
	{
		ConfigUtil::Write(TEXT("Graphics"), TEXT("Width"), _d3d->_d3dpp.BackBufferWidth);
		ConfigUtil::Write(TEXT("Graphics"), TEXT("Height"), _d3d->_d3dpp.BackBufferHeight);
		ConfigUtil::Write(TEXT("Graphics"), TEXT("Windowed"), _d3d->_d3dpp.Windowed);
		ConfigUtil::Write(TEXT("Graphics"), TEXT("V-Synced"), _d3d->_vsynced);
	}

	std::shared_ptr<Core> Core::Create()
	{
		return std::shared_ptr<Core>(new Core);
	}

	bool Core::Init(HWND window, HINSTANCE instance)
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		if (!window || !instance)
		{
			MessageBox(
				0, 
				TEXT("Core�� �ʱ�ȭ�ϴµ� �����߽��ϴ�. \n: ���� 'window' �Ǵ� 'instance'�� ��ȿ���� �ʽ��ϴ�."),
				TEXT("MeltShine GameFrameworks Error!"), MB_OK);
			return false;
		}

		// ��� ����
		_window = window;
		_instance = instance;

		PathUtil::Init();
		ConfigUtil::Init(PathUtil::GetDirectory());
		
		BOOL windowed = ConfigUtil::ReadInt(TEXT("Graphics"), TEXT("Windowed"));
		BOOL vsynced = ConfigUtil::ReadInt(TEXT("Graphics"), TEXT("V-Synced"));
		_d3d = std::shared_ptr<Direct3D>(new Direct3D);
		
		if (!_d3d || !_d3d->Init(_window, windowed, vsynced))
		{
			MessageBox(
				0,
				TEXT("Core�� �ʱ�ȭ�ϴµ� �����߽��ϴ�. \n: Direct3D�� �ʱ�ȭ�ϴµ� �����߽��ϴ�."),
				TEXT("MeltShine GameFrameworks Error!"), MB_OK);
			return false;
		}

		_renderer = std::shared_ptr<Renderer>(new Renderer);
		if (!_renderer || !_renderer->Init(_d3d->_device))
		{
			MessageBox(
				0,
				TEXT("Core�� �ʱ�ȭ�ϴµ� �����߽��ϴ�. \n: Renderer�� �ʱ�ȭ�ϴµ� �����߽��ϴ�."),
				TEXT("MeltShine GameFrameworks Error!"), MB_OK);
			return false;
		}

		_obj_mgr = std::shared_ptr<ObjectManager>(new ObjectManager);
		if (!_obj_mgr || !_obj_mgr->Init(shared_from_this()))
		{
			MessageBox(
				0,
				TEXT("Core�� �ʱ�ȭ�ϴµ� �����߽��ϴ�. \n: ObjectManager�� �ʱ�ȭ�ϴµ� �����߽��ϴ�."),
				TEXT("MeltShine GameFrameworks Error!"), MB_OK);
			return false;
		}

		_sc_ctrl = std::shared_ptr<SceneController>(new SceneController);
		if (!_sc_ctrl)
		{
			MessageBox(
				0,
				TEXT("Core�� �ʱ�ȭ�ϴµ� �����߽��ϴ�. \n: SceneController�� �����ϴµ� �����߽��ϴ�."),
				TEXT("MeltShine GameFrameworks Error!"), MB_OK);
			return false;
		}

		_timer = std::shared_ptr<Timer>(new Timer);
		if (!_timer)
		{
			MessageBox(
				0,
				TEXT("Core�� �ʱ�ȭ�ϴµ� �����߽��ϴ�. \n: Timer�� �����ϴµ� �����߽��ϴ�."),
				TEXT("MeltShine GameFrameworks Error!"), MB_OK);
			return false;
		}

		_texture_cache = std::shared_ptr<TextureCache>(new TextureCache);
		if (!_texture_cache || !_texture_cache->Init(_d3d->_device))
		{
			MessageBox(
				0,
				TEXT("Core�� �ʱ�ȭ�ϴµ� �����߽��ϴ�. \n: TextureCache�� �ʱ�ȭ�ϴµ� �����߽��ϴ�."),
				TEXT("MeltShine GameFrameworks Error!"), MB_OK);
			return false;
		}

		_font_cache = std::shared_ptr<FontCache>(new FontCache);
		if (!_font_cache || !_font_cache->Init(_d3d->_device))
		{
			MessageBox(
				0,
				TEXT("Core�� �ʱ�ȭ�ϴµ� �����߽��ϴ�. \n: FontCache�� �ʱ�ȭ�ϴµ� �����߽��ϴ�."),
				TEXT("MeltShine GameFrameworks Error!"), MB_OK);
			return false;
		}

		_audio_player = std::shared_ptr<AudioPlayer>(new AudioPlayer);
		if (!_audio_player || !_audio_player->Init(32, FMOD_LOOP_NORMAL))
		{
			MessageBox(
				0,
				TEXT("Core�� �ʱ�ȭ�ϴµ� �����߽��ϴ�. \n: AudioPlayer�� �ʱ�ȭ�ϴµ� �����߽��ϴ�."),
				TEXT("MeltShine GameFrameworks Error!"), MB_OK);
			return false;
		}

		return true;
	}

	void Core::Run()
	{
		_timer->CalculateDeltaTime();
		auto dt = _timer->GetDeltaTime();
		auto scene = _sc_ctrl->GetCurrentScene();
		scene->Update(dt);
		scene->LateUpdate();
		scene->Render();
		_renderer->Render();
		_audio_player->Update();
	}

	void Core::GetWinSize(int& w, int& h) const
	{
		RECT rect = {};
		GetClientRect(_window, &rect);
		w = rect.right - rect.left;
		h = rect.bottom - rect.top;
	}

	int Core::GetWinWidth() const
	{
		RECT rect = {};
		GetClientRect(_window, &rect);
		return rect.right - rect.left;
	}

	int Core::GetWinHeight() const
	{
		RECT rect = {};
		GetClientRect(_window, &rect);
		return rect.bottom - rect.top;
	}

}