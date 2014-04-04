#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <map>

typedef HRESULT(__stdcall* Present_t)(LPDIRECT3DDEVICE9*, const RECT*, const RECT*, HWND, const RGNDATA*);
typedef HRESULT(__stdcall* Reset_t)(LPDIRECT3DDEVICE9*, D3DPRESENT_PARAMETERS*);
typedef HRESULT(__stdcall* SetDepthStencilSurface_t)(LPDIRECT3DDEVICE9*, IDirect3DSurface9*);

struct CUSTOMVERTEX
{
	float x, y, z;
	DWORD color;
};

class D3D9Mgr
{

public:
	static void Initialize();
	static void Shutdown();
	static void Draw3DEllipse(float* pos, float radius, int complexity, DWORD color);
	static void Draw3DBox(float* pos, float heading, float width, float height, DWORD color);

private:
	static IDirect3DSurface9* s_originalDepthStencilState;
	static IDirect3DPixelShader9* s_originalPShader;
	static IDirect3DVertexShader9* s_originalVShader;
	static std::map<D3DRENDERSTATETYPE, DWORD> s_originalRenderStates;
	static IDirect3DDevice9* s_d3d9Device;
	static IDirect3DSurface9* s_firstSurface;
	static DWORD s_presentAddress;
	static DWORD s_resetAddress;
	static DWORD s_setDepthStencilSurfaceAddress;
	static void OnFrame();
	static void SetupRenderStates();
	static void SetupViewProjMatrix();
	static void SaveDeviceState();
	static void RestoreDeviceState();
	static Present_t oPresent;
	static Reset_t oReset;
	static SetDepthStencilSurface_t oSetDepthStencilSurface;
	static HRESULT __stdcall MyPresent(LPDIRECT3DDEVICE9* pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);
	static HRESULT __stdcall MyReset(LPDIRECT3DDEVICE9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
	static HRESULT __stdcall MySetDepthStencilSurface(LPDIRECT3DDEVICE9* pDevice, IDirect3DSurface9* pNewZStencil);

};