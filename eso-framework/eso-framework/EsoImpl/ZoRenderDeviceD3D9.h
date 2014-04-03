#pragma once
#include <windows.h>
#include <d3d9.h>

class ZoRenderDeviceD3D9
{

public:
	IDirect3DDevice9* GetDevice() const;

};
