#pragma once
#include <windows.h>

// Version : eso.live.2.0.5.1150504
// All the pointers are 0x400000 based.

class Offsets
{

public:
	
	enum class ZoRenderManager
	{
		s_pZoRenderManager = 0x1B31F60 - 0x400000,
		m_renderDeviceD3D9 = 0x4,											// From : ZoRenderManager::Present
		m_renderApiType = 0x84,												// From : ZosClient::Initialize
	};

	enum class ZoRenderDeviceD3D9
	{
		m_d3ddevice9 = 0x90,												// From : ZoRenderDeviceD3D9::Present
	};

	enum class ClientCoreHandles
	{
		g_pClientCore = 0x198EC5C - 0x400000,
		m_unitList = 0xD8,													// From : CancelCast
		GetUnitListAddress = 0x005A6080 - 0x400000,
	};
	
	enum class UnitList
	{
		GetFirstUnit = 0x00A01D40 - 0x400000,									// UnitList::GetFirstUnit
		GetNextUnit = 0x00A02EE0 - 0x400000,									// UnitList::GetNextUnit
		GetIterUnit = 0x00A01D80 - 0x400000,									// UnitList::GetIterUnit
		m_playerUnit = 0x50,												// From : UnitList::GetPlayerUnit
	};
	
	enum class Unit
	{
		GetName = 0x009F8E20 - 0x400000,										// Unit::GetName
		GetPosition = 0x009F1210 - 0x400000,									// Unit::GetPosition
		GetRenderHeading = 0x009F38D0 - 0x400000,								// Unit::GetRenderHeading
		m_type = 0x94,														// From : Unit::IsKillable
	};
	
	enum class CameraManager
	{
		s_pCameraManager = 0x198DC68 - 0x400000,
	};
	
	enum class ClientWorld
	{
		g_pClientWorld = 0x198E6DC - 0x400000,
		m_camera = 0x5E0,													// From : UpdateZoRenderData
	};
	
	enum class ZoCamera
	{
		m_viewMatrix = 0x44,												// From : ZoCamera::GetViewMatrix
		m_projectionMatrix = 0x84,											// From : ZoCamera::GetProjectionMatrix
	};
	
	enum class WorldPosition
	{
		ToRenderPosition = 0x0089FC60 - 0x400000,
	};

};