#include "EsoMgr.h"
#include <string>
#include <sstream>

void EsoMgr::Initialize(HMODULE myModule)
{

	s_dllModule = myModule;

	if (s_singleton == NULL)
		s_singleton = new EsoMgr();

	s_singleton->m_baseAddress = (DWORD)GetModuleHandle(NULL);

	s_singleton->GetLogger()->Initialize();
	D3D9Mgr::Initialize();

	s_singleton->GetLogger()->WriteLine("EsoMgr::Initialize done !");

}

void EsoMgr::Shutdown()
{

	s_singleton->GetLogger()->WriteLine("EsoMgr::Shutdown ...");

	D3D9Mgr::Shutdown();
	s_singleton->GetLogger()->Shutdown();

	delete s_singleton; 

	FreeLibraryAndExitThread(s_dllModule, ERROR_SUCCESS);

}

ZoRenderManager* EsoMgr::GetRenderManager() const
{
	return *(ZoRenderManager**)(m_baseAddress + (DWORD)Offsets::ZoRenderManager::s_pZoRenderManager);
}

ClientCoreHandles* EsoMgr::GetClientCore() const
{
	return *(ClientCoreHandles**)(m_baseAddress + (DWORD)Offsets::ClientCoreHandles::g_pClientCore);
}

Logger* EsoMgr::GetLogger()
{
	return &m_logger;
}

 void EsoMgr::OnFrame()
 {
	 Tester();
 }

 bool testKeyPressed = false;
 void EsoMgr::Tester()
 {
	 if (GetAsyncKeyState(VK_F1) & 0x8000 &&
		 !testKeyPressed)
	 {
		 testKeyPressed = true;
		 


	 }
	 else
	 {
		 testKeyPressed = GetAsyncKeyState(VK_F1) & 0x8000;
	 }
 }

EsoMgr* EsoMgr::s_singleton = NULL;
HMODULE EsoMgr::s_dllModule = NULL;

