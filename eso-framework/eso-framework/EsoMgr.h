#pragma once
#include <windows.h>
#include "Patchables/Offsets.h"
#include "EsoImpl/ZoRenderManager.h"
#include "D3D9/D3D9Mgr.h"

class EsoMgr
{

public:
	DWORD m_baseAddress;
	ZoRenderManager* GetRenderManager() const;
	D3D9Mgr* GetD3D9Mgr();
	static EsoMgr* GetSingleton() { return s_singleton; };
	static void Initialize(HMODULE myModule);
	static void Shutdown();

private:
	D3D9Mgr m_d3d9Mgr;
	static HMODULE s_dllModule;
	static EsoMgr* s_singleton;

};