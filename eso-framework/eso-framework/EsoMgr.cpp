#include "EsoMgr.h"
#include <string>
#include <sstream>
#include <vector>

void EsoMgr::Initialize(HMODULE myModule)
{

	s_dllModule = myModule;

	if (s_singleton == NULL)
		s_singleton = new EsoMgr();

	s_singleton->m_baseAddress = (DWORD)GetModuleHandle(NULL);

	s_singleton->GetLogger()->Initialize();
	D3D9Mgr::Initialize();

	s_singleton->GetLogger()->WriteLine("EsoMgr::Initialize done !");

}

void EsoMgr::Shutdown()
{

	s_singleton->GetLogger()->WriteLine("EsoMgr::Shutdown ...");

	D3D9Mgr::Shutdown();
	s_singleton->GetLogger()->Shutdown();

	delete s_singleton; 

	FreeLibraryAndExitThread(s_dllModule, ERROR_SUCCESS);

}

ZoRenderManager* EsoMgr::GetRenderManager() const
{
	return *(ZoRenderManager**)(m_baseAddress + (DWORD)Offsets::ZoRenderManager::s_pZoRenderManager);
}

ClientCoreHandles* EsoMgr::GetClientCore() const
{
	return *(ClientCoreHandles**)(m_baseAddress + (DWORD)Offsets::ClientCoreHandles::g_pClientCore);
}

ClientWorld* EsoMgr::GetClientWorld() const
{
	return *(ClientWorld**)(m_baseAddress + (DWORD)Offsets::ClientWorld::g_pClientWorld);
}

Logger* EsoMgr::GetLogger()
{
	return &m_logger;
}

 void EsoMgr::OnFrame()
 {
	 Tester();
	 GraphicTester();

 }

 bool testKeyPressed = false;
 void EsoMgr::Tester()
 {
	 if (GetAsyncKeyState(VK_F1) & 0x8000 &&
		 !testKeyPressed)
	 {
		 testKeyPressed = true;
		 GetLogger()->WriteLine("Tester");
		 float position[4] = {1, 1, 1, 1};
		 ClientCoreHandles * cch = GetClientCore();
		 UnitList * ul = cch->GetUnitList();

		 /*
		 Unit * player = ul->GetPlayerUnit();
		 player->GetPosition(position);
		 std::ostringstream ss;
		 GetLogger()->WriteLine("Position :");
		 ss << "X: " << position[0] << " Y: " << position[1] << " Z: " << position[2];
		 GetLogger()->WriteLine(ss.str());
		 //GetLogger()->WriteLine("Name :");
		 //GetLogger()->WriteLine(player->GetName());

		 GetLogger()->WriteLine("Render Heading :");
		 std::ostringstream sr;
		 sr << player->GetRenderHeading();
		 GetLogger()->WriteLine(sr.str());

		 float rposition[4] = { 1, 1, 1, 1 };
		 player->GetRenderPosition(rposition);
		 std::ostringstream sp;
		 GetLogger()->WriteLine("Render Position :");
		 sp << "X: " << rposition[0] << " Y: " << rposition[1] << " Z: " << rposition[2];
		 GetLogger()->WriteLine(sp.str());

		 GetLogger()->WriteLine("Unit Type :");
		 std::ostringstream st;
		 st << (int)player->GetType();
		 GetLogger()->WriteLine(st.str());
		 */

		 std::vector<Unit*> units = ul->GetUnits();
		 GetLogger()->WriteLine("Units Size :");
		 std::ostringstream sun;
		 sun << units.size();
		 GetLogger()->WriteLine(sun.str());




	 }
	 else
	 {
		 testKeyPressed = GetAsyncKeyState(VK_F1) & 0x8000;
	 }
 }

 void EsoMgr::GraphicTester()
 {
	 ClientCoreHandles * cch = GetClientCore();
	 UnitList * ul = cch->GetUnitList();
	 std::vector<Unit*> units = ul->GetUnits();
	 int totalUnits = units.size();

	 GetLogger()->WriteLine("Units :");

	 for (int unIndex = 0; unIndex < totalUnits; unIndex++) {
		 float where[3] = { 1, 1, 1 };
		 units[unIndex]->GetRenderPosition(where);
		 std::ostringstream sun;
		 sun << "X: " << where[0] << " Y: " << where[1] << " Z: " << where[2] << " Type : " << (int)units[unIndex]->GetType();
		 GetLogger()->WriteLine(sun.str());
		 //D3D9Mgr::Draw3DBox(where, 1, 10.0f, 10.0f, (int)units[unIndex]->GetType() * 46894);
		 D3D9Mgr::Draw3DEllipse(where, 20, 2, 0xFFFFFFFF);
	 }
 }

EsoMgr* EsoMgr::s_singleton = NULL;
HMODULE EsoMgr::s_dllModule = NULL;

