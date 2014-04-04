#include "ClientWorld.h"
#include "../Patchables/Offsets.h"

ZoCamera* ClientWorld::GetCamera() const
{
	return *(ZoCamera**)(this + (DWORD)Offsets::ClientWorld::m_camera);
}
