#pragma once

#include <winsock2.h>
#include <iostream> 
#include <string>
#pragma comment(lib,"ws2_32.lib")

class Client
{
private:
	int _port;
	const char* _ip;
public:
	SOCKET sock;

	Client(int port, const char * ip) : _port(port), _ip(ip)
	{
	}
	void sender(const std::string& str) const;
	void receiver();
	int c_connect();
};



