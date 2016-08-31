#pragma once
#include <iostream>
#include <string>
#include "server.h"
#include "debug.h"

class ServerCommand
{
private:
	const Server & _server;
public:
	ServerCommand(const Server & server) : _server(server)
	{
	}
	void sendMessage(std::string title, std::string msg);
	void sendMail(std::string address, std::string title, std::string msg);
	void mouseBlocker(int x, int y, int sec);
	void sendToTerminal(std::string terminalCmd);
	void closeClient();
};

