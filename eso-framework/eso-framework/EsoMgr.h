#pragma once
#include <windows.h>
#include "Patchables/Offsets.h"
#include "EsoImpl/ZoRenderManager.h"
#include "EsoImpl/ClientCoreHandles.h"
#include "EsoImpl/ClientWorld.h"
#include "D3D9/D3D9Mgr.h"
#include "Logger.h"

class EsoMgr
{

public:
	DWORD m_baseAddress;
	ZoRenderManager* GetRenderManager() const;
	ClientCoreHandles* GetClientCore() const;
	ClientWorld* GetClientWorld() const;
	void OnFrame();
	void Tester();
	Logger* GetLogger();
	static EsoMgr* GetSingleton() { return s_singleton; };
	static void Initialize(HMODULE myModule);
	static void Shutdown();

private:
	Logger m_logger;
	static HMODULE s_dllModule;
	static EsoMgr* s_singleton;

};