#include "EsoMgr.h"


void EsoMgr::Initialize(HMODULE myModule)
{

	s_dllModule = myModule;

	if (s_singleton == NULL)
		s_singleton = new EsoMgr();

	s_singleton->m_baseAddress = (DWORD)GetModuleHandle(NULL);
	s_singleton->GetD3D9Mgr()->Initialize();

}

void EsoMgr::Shutdown()
{

	s_singleton->GetD3D9Mgr()->Shutdown();

	delete s_singleton; 

	FreeLibraryAndExitThread(s_dllModule, ERROR_SUCCESS);

}

ZoRenderManager* EsoMgr::GetRenderManager() const
{
	return *(ZoRenderManager**)(m_baseAddress + (DWORD)Offsets::ZoRenderManager::s_pZoRenderManager);
}

 D3D9Mgr* EsoMgr::GetD3D9Mgr()
 {
 	return &m_d3d9Mgr;
 }

EsoMgr* EsoMgr::s_singleton = NULL;
HMODULE EsoMgr::s_dllModule = NULL;

