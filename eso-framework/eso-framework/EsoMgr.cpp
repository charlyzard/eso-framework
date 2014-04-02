#include "EsoMgr.h"

EsoMgr* EsoMgr::s_singleton = NULL;

EsoMgr* EsoMgr::GetSingleton()
{

	if (s_singleton == NULL)
		s_singleton = new EsoMgr();

	return s_singleton;

}

void EsoMgr::Initialize()
{

}

void EsoMgr::Shutdown()
{

}

