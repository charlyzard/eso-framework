#include "UnitList.h"
#include "../Patchables/Offsets.h"
#include "../EsoMgr.h"

Unit* UnitList::GetPlayerUnit() const
{
	return *(Unit**)(this + (DWORD)Offsets::UnitList::m_playerUnit);
}

DWORD UnitList::GetFirstUnit() const
{

	DWORD oFunc = EsoMgr::GetSingleton()->m_baseAddress + (DWORD)Offsets::UnitList::GetFirstUnit;
	DWORD result;

	__asm
	{
		mov ecx, this
			call oFunc
			mov result, eax
	}

	return result;

}

DWORD UnitList::GetNextUnit(DWORD pIter) const
{

	DWORD oFunc = EsoMgr::GetSingleton()->m_baseAddress + (DWORD)Offsets::UnitList::GetNextUnit;
	DWORD result;

	__asm
	{
		push pIter
		mov ecx, this
			call oFunc
			mov result, eax
	}

	return result;

}

Unit* UnitList::GetIterUnit(DWORD pIter) const
{
	DWORD oFunc = EsoMgr::GetSingleton()->m_baseAddress + (DWORD)Offsets::UnitList::GetIterUnit;
	Unit* result;

	__asm
	{
		push pIter
			mov ecx, this
			call oFunc
			mov result, eax
	}

	return result;
}

std::vector<Unit*> UnitList::GetUnits()
{

	std::vector<Unit*> result;

	for (DWORD it = GetFirstUnit(); it; it = GetNextUnit(it))
	{

		Unit* unit = GetIterUnit(it);

		if (unit)
		{
			result.push_back(unit);
		}

	}

	return result;

}
