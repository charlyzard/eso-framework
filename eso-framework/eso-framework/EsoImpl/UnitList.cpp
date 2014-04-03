#include "UnitList.h"

Unit* UnitList::GetPlayerUnit() const
{
	return *(Unit**)(this + (DWORD)Offsets::UnitList::m_playerUnit);
}
