#include "ZoRenderDeviceD3D9.h"

// TODO : Include D3D9 SDK and return a IDirect3DDevice9 object.
DWORD ZoRenderDeviceD3D9::GetDevice() const
{
	return *(DWORD*)(this + (DWORD)Offsets::ZoRenderDeviceD3D9::m_d3ddevice9);
}
