#include "Unit.h"
#include "../EsoMgr.h"
#include "../Patchables/Offsets.h"

Unit::UNIT_TYPE Unit::GetType() const
{
	return *(UNIT_TYPE*)(this + (DWORD)Offsets::Unit::m_type);
}

char* Unit::GetName() const
{

	char* result = NULL;

	DWORD oFunc = EsoMgr::GetSingleton()->m_baseAddress + (DWORD)Offsets::Unit::GetName;

	__asm
	{
		mov ecx, this
		call oFunc
		mov result, eax
	}

	return result;

}

void Unit::GetPosition(float* pos) const
{

	DWORD oFunc = EsoMgr::GetSingleton()->m_baseAddress + (DWORD)Offsets::Unit::GetPosition;

	__asm
	{
			push pos
			mov ecx, this
			call oFunc
	}

}

void Unit::GetRenderPosition(float* pos) const
{

	DWORD oFunc = EsoMgr::GetSingleton()->m_baseAddress + (DWORD)Offsets::WorldPosition::ToRenderPosition;
	float worldPos[3];

	GetPosition(worldPos);

	__asm
	{
		push pos
			lea ecx, worldPos
			call oFunc
	}

}

float Unit::GetRenderHeading() const
{

	DWORD oFunc = EsoMgr::GetSingleton()->m_baseAddress + (DWORD)Offsets::Unit::GetRenderHeading;
	float result;

	__asm
	{
		mov ecx, this
			call oFunc
			fstp result
	}

	return result;

}
