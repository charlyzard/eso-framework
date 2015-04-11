#include "ClientCoreHandles.h"
#include "../Patchables/Offsets.h"
#include "../EsoMgr.h"

UnitList* ClientCoreHandles::GetUnitList() const
{
	UnitList* ulAdress;
	DWORD oFunc = (EsoMgr::GetSingleton()->m_baseAddress +(DWORD)Offsets::ClientCoreHandles::GetUnitListAddress);
	DWORD offsete = (DWORD)Offsets::ClientCoreHandles::m_unitList;
	__asm
	{
			mov     ecx, this
			add     ecx, offsete
			call    oFunc
			mov	ulAdress, eax
	}

	return ulAdress;
}