#pragma once
#include <windows.h>

class EsoMgr
{

public:
	static EsoMgr* GetSingleton();
	void Initialize();
	void Shutdown();

private:
	static EsoMgr* s_singleton;

};