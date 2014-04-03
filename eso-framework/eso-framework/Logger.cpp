#include "Logger.h"
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>

void Logger::Initialize()
{

	if (!m_consoleOpen)
	{
		AllocConsole();
		LONG lStdHandle = (LONG)GetStdHandle(STD_OUTPUT_HANDLE);
		int hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		FILE* fp = _fdopen(hConHandle, "w");
		*stdout = *fp;
		setvbuf(stdout, NULL, _IONBF, 0);
		m_consoleOpen = true;
	}

}

void Logger::Shutdown()
{

	if (m_consoleOpen)
	{
		FreeConsole();
		m_consoleOpen = false;
	}

}

void Logger::WriteLine(const std::string text) const
{
	std::cout << text << std::endl;
}
