#pragma once
#include <windows.h>

// Version : eso.live.1.0.0.962092
// All the pointers are 0x400000 based.

class Offsets
{

public:

	enum class ZoRenderManager
	{
		s_pZoRenderManager = 0x1574288 - 0x400000,
		m_renderDeviceD3D9 = 0x4,											// From : ZoRenderManager::Present
		m_renderApiType = 0x6C,												// From : ZosClient::Initialize
	};

	enum class ZoRenderDeviceD3D9
	{
		m_d3ddevice9 = 0x84,												// From : ZoRenderDeviceD3D9::Present
	};

};