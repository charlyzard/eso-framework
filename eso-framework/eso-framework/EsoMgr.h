#pragma once
#include <windows.h>
#include "Patchables/Offsets.h"
#include "EsoImpl/ZoRenderManager.h"

class EsoMgr
{

public:
	DWORD m_baseAddress;
	ZoRenderManager* GetRenderManager() const;
	static EsoMgr* GetSingleton() { return s_singleton; };
	static void Initialize(HMODULE myModule);
	static void Shutdown();

private:
	static HMODULE s_dllModule;
	static EsoMgr* s_singleton;

};