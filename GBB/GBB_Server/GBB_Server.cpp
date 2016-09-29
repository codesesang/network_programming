// GBB_Server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "../MyLib/GBB2.h"
#include "../MyLib/MyLib.h"

#pragma comment(lib,"ws2_32")

int GetUser(char* para)
{
	int re = 0;

	if (0 == strncmp(para, "GA", 2))
	{
		re = 0;
	}
	else if (0 == strncmp(para, "BA", 2))
	{
		re = 1;
	}
	else if (0 == strncmp(para, "BO", 2))
	{
		re = 2;
	}

	return re;
}

char g_word[10][20] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten" };

DWORD WINAPI Game1(LPVOID para)
{
	SOCKET c = (SOCKET)para;

	S_DATA sdata;
	S_DATA rdata;

	while (1)
	{
		ZeroMemory(&rdata, sizeof(rdata));
		Receive(c, (char*)&rdata, sizeof(rdata));

		printf("%s %s\n", rdata.id, rdata.data);

		int index = rand() % 10;
		ZeroMemory(&sdata, sizeof(sdata));

		strcpy(sdata.id, "server");
		strcpy(sdata.data, g_word[index]);

		Send(c, (char*)&sdata, sizeof(sdata));
	}

	Close(c);

	return 0;
}

DWORD WINAPI Game(LPVOID para)
{
	SOCKET c = (SOCKET)para;

	int count = 0;
	int wcount = 0;
	float wrate;

	S_DATA sdata;
	S_DATA rdata;

	for (int i = 0; i < 10; i++)
	{
		int com = rand() % 3;
		int user;
		bool iswin = false;

		ZeroMemory(&rdata, sizeof(rdata));
		Receive(c, (char*)&rdata, sizeof(rdata));
		user = GetUser(rdata.data);

		count++;
		
		if (((0 == user) && (2 == com)) || 
			((1 == user) && (0 == com)) || 
			((2 == user) && (1 == com)))
		{
			wcount++;
			iswin = true;
		}
		ZeroMemory(&sdata, sizeof(sdata));
		strcpy(sdata.id, rdata.id);
		
		wrate = (float)wcount / count;
		if (iswin)
		{
			sprintf(sdata.data, "You Win : %.2f", wrate);
		}
		else
		{
			sprintf(sdata.data, "You Lose : %.2f", wrate);
		}
		Send(c, (char*)&sdata, sizeof(sdata));
		printf("%s,%s\n", rdata.id, rdata.data);
	}

	Close(c);

	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int port = 2016;

	IniWinNet();

	CreateServer(port);

	Listen();

	while (1)
	{
		SOCKET c = Accept();

		CreateThread(NULL, 0, Game1, (LPVOID)c, NULL, 0);
	}

	CloseWinNet();

	return 0;
}

