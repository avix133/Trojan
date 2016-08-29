#pragma once
#define DEBUG true

#include "trojan.h"
#include "sendmail.h"
#include <iostream> 
#include <string>
#include <windows.h> 
#include <thread>

class Command
{
private:
	std::string _cmd;
	int getSeparation(std::string cmd, std::string code);
	std::string getTitle(std::string cmd);
	std::string getMessage(std::string cmd, bool address);
	std::string getAddress(std::string cmd);
public:
	Command(std::string cmd)
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