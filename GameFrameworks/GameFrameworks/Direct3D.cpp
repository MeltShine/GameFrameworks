#include "Direct3D.h"


namespace meltshine
{
	Direct3D::Direct3D()
		: _hwnd()
		, _d3d()
		, _device()
		, _d3dpp()
		, _vsynced()
	{
	}


	Direct3D::~Direct3D()
	{
		if (_device)
		{
			_device->Release();
			_device = nullptr;
		}
		if (_d3d)
		{
			_d3d->Release();
			_d3d = nullptr;
		}
	}

	bool Direct3D::Init(HWND hwnd, BOOL windowed, BOOL vsynced)
	{
		_d3d = Direct3DCreate9(D3D_SDK_VERSION);

		memset(&_d3dpp, NULL, sizeof(_d3dpp));
		_d3dpp.hDeviceWindow = hwnd;
		_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		
		// 창 & 전체화면 모드 설정
		if (windowed == TRUE)
		{
			// 창 모드 설정
			_d3dpp.BackBufferWidth = 0;
			_d3dpp.BackBufferHeight = 0;
			_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
			_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		}
		else
		{
			// 전체화면 모드 설정
			D3DDISPLAYMODE mode = {};
			_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
			_d3dpp.BackBufferWidth = mode.Width;
			_d3dpp.BackBufferHeight = mode.Height;
			_d3dpp.BackBufferFormat = mode.Format;
			_d3dpp.FullScreen_RefreshRateInHz = mode.RefreshRate;
		}
		_d3dpp.Windowed = windowed;

		// V-Sync 초기 설정
		if (vsynced == TRUE)
		{
			// V-Sync 켜기
			_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		}
		else
		{
			// V-Sync 끄기
			_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
			_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		}
		_vsynced = vsynced;

		// Depth Stencil 설정
		_d3dpp.EnableAutoDepthStencil = TRUE;
		_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

		HRESULT hr = {};
		hr = _d3d->CreateDevice(D3DADAPTER_DEFAULT,
						   D3DDEVTYPE_HAL,
						   hwnd,
						   D3DCREATE_HARDWARE_VERTEXPROCESSING,
						   &_d3dpp,
						   &_device);
		if (FAILED(hr))
		{
			return false;
		}
		
		_hwnd = hwnd;
		_vsynced = vsynced;
		return true;
	}

	void Direct3D::SetVSync(BOOL vsynced)
	{
		if (_vsynced == vsynced)
		{
			return;
		}
		if (vsynced == TRUE)
		{
			// V-Sync 켜기
			_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		}
		else
		{
			// V-Sync 끄기
			_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
			_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		}
		_vsynced = vsynced;
		_device->Reset(&_d3dpp);
	}

	void Direct3D::SetWindowMode(BOOL windowed)
	{
		if (_d3dpp.Windowed == windowed)
		{
			return;
		}
		if (windowed == TRUE)
		{
			// 창 모드 설정
			_d3dpp.BackBufferWidth = 0;
			_d3dpp.BackBufferHeight = 0;
			_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
			_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		}
		else
		{
			// 전체화면 모드 설정
			D3DDISPLAYMODE mode = {};
			_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
			_d3dpp.BackBufferWidth = mode.Width;
			_d3dpp.BackBufferHeight = mode.Height;
			_d3dpp.BackBufferFormat = mode.Format;
			_d3dpp.FullScreen_RefreshRateInHz = mode.RefreshRate;
		}
		_d3dpp.Windowed = windowed;
		_device->Reset(&_d3dpp);
	}

	void Direct3D::ResizeBackbuffer(UINT width, UINT height)
	{
		if(!_d3dpp.Windowed)
		{
			return;
		}

		_d3dpp.BackBufferHeight = height;
		_d3dpp.BackBufferWidth = width;

		_device->Reset(&_d3dpp);
	}

}