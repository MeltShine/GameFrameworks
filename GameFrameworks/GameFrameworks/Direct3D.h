#ifndef __MELTSHINE_DIRECT3D_H__
#define __MELTSHINE_DIRECT3D_H__
#include <d3d9.h>
namespace meltshine
{
	class Direct3D
	{
	private:
		Direct3D();
	public:
		~Direct3D();

		bool Init(HWND hwnd, BOOL windowed, BOOL vsynced);

		LPDIRECT3D9 GetD3D() const { return _d3d; }
		LPDIRECT3DDEVICE9 GetDevice() const { return _device; }
		D3DPRESENT_PARAMETERS GetPresentParameters() const { return _d3dpp; }
		BOOL IsVSynced() const { return _vsynced; }
		BOOL IsWindowed() const { return _d3dpp.Windowed; }
		void SetVSync(BOOL vsynced);
		void SetWindowMode(BOOL windowed);
		void ResizeBackbuffer(UINT width, UINT height);

	private:
		HWND _hwnd;
		BOOL _vsynced;
		D3DPRESENT_PARAMETERS _d3dpp;
		LPDIRECT3D9 _d3d;
		LPDIRECT3DDEVICE9 _device;

		friend class Core;
	};
}
#endif // !__MELTSHINE_DIRECT3D_H__