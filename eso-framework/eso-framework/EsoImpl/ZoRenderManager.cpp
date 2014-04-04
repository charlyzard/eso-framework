#include "ZoRenderManager.h"
#include "../Patchables/Offsets.h"
#include <iostream>

ZoRenderManager::RENDER_API ZoRenderManager::GetRenderApiType() const
{
	return *(RENDER_API*)(this + (DWORD)Offsets::ZoRenderManager::m_renderApiType);
}

ZoRenderDeviceD3D9* ZoRenderManager::GetRenderDeviceD3D9() const
{
	return *(ZoRenderDeviceD3D9**)(this + (DWORD)Offsets::ZoRenderManager::m_renderDeviceD3D9);
}

