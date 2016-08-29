#include "command.h"
#include "sendmail.h"

/*Converts command and directs them to proper functions*/
void Command::execCommand()
{
	std::string prepos;
	prepos = _cmd.substr(0, 2);
	_cmd.erase(0, 2);
	if (DEBUG)
	{
		std::cout << "\nPrepos: " << prepos << std::endl;
		std::cout << "CMD: " << _cmd << std::endl;
	}

	/*V DIRECTOR V*/
	if (prepos.compare("1$") == 0) //MailSender gets format: 1$title##msg@@addres
	{
		if (DEBUG)
			std::cout << "Mailing...\n";
		//std::string addres = 
		std::string msg = getMessage(_cmd);
		std::string title = getTitle(_cmd);
		if (DEBUG)
			std::cout << "Title: " << title << "\nMsg: " << msg << std::endl;
		//mail("avix133help@gmail.com", title.c_str(), msg.c_str());
	}
	else if (prepos.compare("2$") == 0) //Downloader
	{
		if (DEBUG)
			std::cout << "Downloading...\n";
	}
	else if (prepos.compare("3$") == 0) //MessageSender gets format: 3$title##msg
	{
		if (DEBUG)
			std::cout << "Message..\n";

		std::string msg = getMessage(_cmd);
		std::string title = getTitle(_cmd);
		
		MessageBox(NULL, msg.c_str() , title.c_str(), MB_ICONINFORMATION | MB_OKCANCEL);
	}
	else
	{
		if (DEBUG)
			std::cout << "Command is invalid!\n";
	}

}
int Command::getSeparation(std::string cmd)
{
std::string temp_str;
std::string temp_str2;
	if (cmd.length() != 0)
	{
		for (int i = 0; i < cmd.length()-1; i++)
		{
			temp_str = cmd.at(i);
			temp_str2 = cmd.at(i + 1);
			if (temp_str.compare("#") == 0 && temp_str2.compare("#") == 0)
			{
				return i;
			}
		}
		if (DEBUG)
			std::cout << "Only title in command\n";
		return 0;
	}
	else
	{
		if (DEBUG)
			std::cout << "Cmd.length = 0!\n";
		return 0;
	}
}

std::string Command::getTitle(std::string cmd)
{
int n;
	if ((n = getSeparation(cmd)) != 0)
	{
		if (DEBUG)
			std::cout << "getTitle returned: " << n << std::endl;

		return cmd.substr(0, n);
	}
	else return cmd;
}

std::string Command::getMessage(std::string cmd)
{
int n;

	if((n = getSeparation(cmd)) != 0)
	{
		n += 2; //2 cuz of ##
		if (DEBUG)
			std::cout << "getMessage returned: " << n << std::endl;
		return cmd.substr(n, (cmd.length() - n));
	}
	else return cmd;
}