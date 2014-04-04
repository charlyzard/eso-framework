#pragma once
#include <windows.h>
#include <vector>
#include "Unit.h"

class UnitList
{
public:
	Unit* GetPlayerUnit() const;
	std::vector<Unit*> GetUnits();

private:
	DWORD GetFirstUnit() const;
	DWORD GetNextUnit(DWORD pIter) const;
	Unit* GetIterUnit(DWORD pIter) const;

};