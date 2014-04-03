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

	enum class ClientCoreHandles
	{
		g_pClientCore = 0x13CFE04 - 0x400000,
		m_unitList = 0xC,													// From : CancelCast
	};

	enum class UnitList
	{
		m_playerUnit = 0x50,												// From : UnitList::GetPlayerUnit
	};

	enum class Unit
	{
		GetName = 0x807240 - 0x400000,										// Unit::GetName
		m_type = 0x68,														// From : Unit::IsKillable
	};

	enum class CameraManager
	{
		s_pCameraManager = 0x13CEE08 - 0x400000,
	};

};