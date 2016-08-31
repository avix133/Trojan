#pragma once

#include <Windows.h>
#include <string>

class Autostart
{
private:
	BOOL RegisterMyProgramForStartup(PCWSTR pathToExe);
	PCWSTR _pszAppName;
public:
	Autostart(PCWSTR pszAppName) : _pszAppName(pszAppName)
	{
	}
	BOOL IsMyProgramRegisteredForStartup();
	void RegisterProgram();
};