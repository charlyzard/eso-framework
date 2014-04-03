#pragma once
#include <windows.h>
#include "../Patchables/Offsets.h"
#include "ZoRenderDeviceD3D9.h"

class ZoRenderManager
{

	enum class RENDER_API : int
	{
		D3D9,
		D3D11,
		OPENGL,
		RAPI_UNKNOWN
	};

public:
	RENDER_API GetRenderApiType() const;
	ZoRenderDeviceD3D9* GetRenderDeviceD3D9() const;

};