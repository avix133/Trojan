#include "serverCommand.h"
#include <sstream>
#include <ctime>

void ServerCommand::closeClient()
{
	_server.sender("$$");
}


void ServerCommand::sendMail(std::string address, std::string title, std::string msg) //1$title##msg@@address
{
	std::string temp = "1$" + title + "##" + msg + "@@" + address;
	if (DEBUG)
		std::cout << "Sending code: " << temp << std::endl;

	_server.sender(temp);
}

void ServerCommand::mouseBlocker(int x, int y, int sec) //2$X..Y
{
	std::ostringstream ss;
	ss << x;
	std::string str_x = ss.str();
	ss << y;
	std::string str_y = ss.str();

	std::string temp = "2$" + str_x + ".." + str_y;

	std::time_t start;
	time(&start);
	std::cout << "Clients mouse is blocked!\n";
		while(1)
		{
			std::time_t stop;
			time(&stop);
				if (start + sec <= stop )
					break;
				
				_server.sender(temp);
				
		}
	std::cout << "Clients mouse is unlocked!\n";
}

void ServerCommand::sendMessage(std::string title, std::string msg) //3$title##msg
{
	std::string temp = "3$" + title + "##" + msg;
	if (DEBUG)
		std::cout << "Sending code: " << temp << std::endl;

	_server.sender(temp);
}

