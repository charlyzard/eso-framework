#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

typedef HRESULT(__stdcall* Present_t)(LPDIRECT3DDEVICE9*, const RECT*, const RECT*, HWND, const RGNDATA*);
typedef HRESULT(__stdcall* Reset_t)(LPDIRECT3DDEVICE9*, D3DPRESENT_PARAMETERS*);

class D3D9Mgr
{

public:
	static void Initialize();
	static void Shutdown();

private:
	static DWORD s_presentAddress;
	static DWORD s_resetAddress;
	static void OnFrame();
	static Present_t oPresent;
	static Reset_t oReset;
	static HRESULT __stdcall MyPresent(LPDIRECT3DDEVICE9* pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);
	static HRESULT __stdcall MyReset(LPDIRECT3DDEVICE9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);

};