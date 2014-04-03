#include "EsoMgr.h"


void EsoMgr::Initialize(HMODULE myModule)
{

	s_dllModule = myModule;

	if (s_singleton == NULL)
		s_singleton = new EsoMgr();

	s_singleton->m_baseAddress = (DWORD)GetModuleHandle(NULL);

}

void EsoMgr::Shutdown()
{

	delete s_singleton; 

	FreeLibraryAndExitThread(s_dllModule, ERROR_SUCCESS);

}

ZoRenderManager* EsoMgr::GetRenderManager() const
{
	return *(ZoRenderManager**)(m_baseAddress + (DWORD)Offsets::ZoRenderManager::s_pZoRenderManager);
}

EsoMgr* EsoMgr::s_singleton = NULL;
HMODULE EsoMgr::s_dllModule = NULL;

