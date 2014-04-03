#pragma once
#include <windows.h>
#include <string>

class Logger
{
public:
	void Initialize();
	void Shutdown();
	void WriteLine(const std::string text) const;

private:
	bool m_consoleOpen;

};