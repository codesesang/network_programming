#include "stdafx.h"
#include "MyLib.h"


#pragma comment(lib,"ws2_32")


SOCKET g_s;


bool IniWinNet()
{
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
		return false;

	return true;
}


int CreateServer(int port)
{
	g_s = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == g_s)
		return -1;

	SOCKADDR_IN saddr;

	ZeroMemory(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (SOCKET_ERROR == bind(g_s, (SOCKADDR*)&saddr, sizeof(saddr)))
		return -2;

	return 0;
}

int Close(SOCKET s)
{
	closesocket(s);

	return 0;
}


int Listen()
{
	if (SOCKET_ERROR == listen(g_s, SOMAXCONN))
		return -1;

	return 0;
}


SOCKET Accept()
{
	SOCKET c;
	SOCKADDR caddr;
	int len = sizeof(caddr);

	if (INVALID_SOCKET == (c = accept(g_s, (SOCKADDR*)&caddr, &len)))
		return INVALID_SOCKET;

	return c;
}


int Send(SOCKET c, char* buf, int len)
{
	int re = send(c, buf, len, 0);

	return re;
}


int Receive(SOCKET c, char* buf, int len)
{
	int re;
	int receive;
	char* ptr;
	int left;

	ptr = buf;
	left = len;

	while (0 < left)
	{
		receive = recv(c, ptr, left, 0);
		if (SOCKET_ERROR == receive)
			return -1;

		else if (0 == receive)
			break;

		else
		{
			left -= receive;
			ptr += receive;
		}	
	}
	return len - left;
}


SOCKET CreateClient()
{
	SOCKET c = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == c)
		return INVALID_SOCKET;

	return c;
}

int Connect(SOCKET c, int port, char* ip)
{
	SOCKADDR_IN saddr;

	ZeroMemory(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr(ip);
	saddr.sin_port = htons(port);

	if (SOCKET_ERROR == connect(c, (SOCKADDR*)&saddr, sizeof(saddr)))
		return -1;

	return 0;
}

int CloseWinNet()
{
	WSACleanup();

	return 0;
}