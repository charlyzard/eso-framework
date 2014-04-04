#include "ClientCoreHandles.h"
#include "../Patchables/Offsets.h"

UnitList* ClientCoreHandles::GetUnitList() const
{
	return *(UnitList**)(this + (DWORD)Offsets::ClientCoreHandles::m_unitList);
}
