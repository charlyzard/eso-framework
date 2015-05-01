#pragma once
#include <windows.h>

// Version : eso.live.2.0.7.1154797
// All the pointers are 0x400000 based.

class Offsets
{

public:
	
	enum class ZoRenderManager
	{
		s_pZoRenderManager = 0x1B31F58 - 0x400000,
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
		GetUnitListAddress = 0x005A5EF0 - 0x400000,
	};
	
	enum class UnitList
	{
		GetFirstUnit = 0x00A02190 - 0x400000,									// UnitList::GetFirstUnit
		GetNextUnit = 0x00A03330 - 0x400000,									// UnitList::GetNextUnit
		GetIterUnit = 0x00A021D0 - 0x400000,									// UnitList::GetIterUnit
		m_playerUnit = 0x50,												// From : UnitList::GetPlayerUnit
	};
	
	enum class Unit
	{
		GetName = 0x009F9270 - 0x400000,										// Unit::GetName
		GetPosition = 0x009F1660 - 0x400000,									// Unit::GetPosition
		GetRenderHeading = 0x009F3D20 - 0x400000,								// Unit::GetRenderHeading
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
		ToRenderPosition = 0x0089FFE0 - 0x400000,
	};

};