#pragma once
#include <string>
#include <iostream>
#include "ConsoleLogger.h"
#include "debug.h"

class AnswerFromClient
{
private:
	std::string _answer;
	std::string _prepos;
	CConsoleLoggerEx & _keyloggerConsole;
public:
	AnswerFromClient(std::string answer, CConsoleLoggerEx & console) : _answer(answer), _keyloggerConsole(console)
	{
		coordinator();
	}
	void coordinator();
};
