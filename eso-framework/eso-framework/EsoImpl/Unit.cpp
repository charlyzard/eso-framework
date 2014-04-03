#include "Unit.h"
#include "../EsoMgr.h"

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
