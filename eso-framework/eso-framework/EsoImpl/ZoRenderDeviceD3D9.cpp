#include "ZoRenderDeviceD3D9.h"
#include "../Patchables/Offsets.h"

IDirect3DDevice9* ZoRenderDeviceD3D9::GetDevice() const
{
	return *(IDirect3DDevice9**)(this + (DWORD)Offsets::ZoRenderDeviceD3D9::m_d3ddevice9);
}
