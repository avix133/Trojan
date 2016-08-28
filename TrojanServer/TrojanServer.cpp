
#include "stdafx.h"
#include <winsock2.h>
#include <process.h>
#include <string>
#include <thread>
#include <iostream>
#pragma comment(lib,"ws2_32.lib" )

//using namespace std;
unsigned int __stdcall  ServClient(void *data);
void sender(SOCKET Client);




int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	int iResult;
	sockaddr_in addr; //ip
	SOCKET sock, client;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);//2.2 

	if (iResult)
	{
		std::cout << "ERROR! WSA startup failed";
		Sleep(1000);
		return 0;
	}

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock == INVALID_SOCKET)
	{
		std::cout << "ERROR! Invalid socket\n";
		Sleep(1000);
		return 0;
	}

	iResult = bind(sock, (sockaddr*)&addr, sizeof(sockaddr_in)); //TUTAJ BLAD

	if (iResult)
	{
		std::cout << "ERROR! bind failed %u" << GetLastError();
		Sleep(5000);
		return 0;
	}

	iResult = listen(sock, SOMAXCONN);

	if (iResult)
	{
		std::cout << "ERROR! iResult failed %u" << GetLastError();
		Sleep(1000);
		return 0;
	}
	std::cout << "Listening...\n";

	while (client = accept(sock, 0, 0)) /*accepting and "threading" clients*/
	{
		if (client == INVALID_SOCKET)
		{
			std::cout << "ERROR! invalid client socket" << GetLastError();
			continue;
		}
		_beginthreadex(0, 0, ServClient, (void*)&client, 0, 0);

	}
	return 0;
}


unsigned int __stdcall ServClient(void *data)
{
	SOCKET* client = (SOCKET*)data;
	SOCKET Client = *client;
	std::cout << "Client connected!\n";
	std::thread t_sender(sender, Client);

	t_sender.detach();

	char chunk[200];
	while (recv(Client, chunk, sizeof(chunk), 0))
	{
		std::cout << GetCurrentThreadId() << "\t" << chunk << std::endl;
	}
	return 0;
}

void sender(SOCKET Client)
{
	char ptr[1024];
	std::string txt;

	while (1)
	{
		std::getline(std::cin, txt);
		const char * c = txt.c_str();
		sprintf(ptr, c);
		send(Client, c, sizeof(ptr), 0);
	}

}
