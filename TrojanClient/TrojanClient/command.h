#pragma once
#define DEBUG true

#include <iostream> 
#include <string>
#include <windows.h> 
#include <thread>

class Command
{
private:
	std::string _cmd;
	int getSeparation(std::string cmd);
	std::string getTitle(std::string cmd);
	std::string getMessage(std::string cmd);
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