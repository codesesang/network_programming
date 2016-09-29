// GBB_Client.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "../MyLib/GBB2.h"
#include "../MyLib/MyLib.h"

#pragma comment(lib,"ws2_32")

int Game2(SOCKET c)
{
	S_DATA sdata;
	S_DATA rdata;

	while (1)
	{
		char msg[20];

		printf("$");

		fgets(msg, sizeof(msg), stdin);

		if (0 == strcmp("exit", msg))
		{
			break;
		}
		else
		{
			sprintf(sdata.id, "haha");
			sprintf(sdata.data, msg);

			Send(c, (char*)&sdata, sizeof(sdata));
		}

		ZeroMemory(&rdata, sizeof(rdata));
		Receive(c, (char*)&rdata, sizeof(rdata));

		printf("%s\n", rdata.data);
	}

	return 0;
}

int Game(SOCKET c)
{
	S_DATA sdata;
	S_DATA rdata;
	char id[20] = "HANKYUL";

	for (int i = 0; i < 10; i++)
	{
		char data[30];

		printf("GA BA BO : ");
		scanf("%s", data);
		
		ZeroMemory(&sdata, sizeof(sdata));
		strcpy(sdata.id, id);
		strcpy(sdata.data, data);

		Send(c, (char*)&sdata, sizeof(sdata));

		ZeroMemory(&rdata, sizeof(rdata));
		Receive(c, (char*)&rdata, sizeof(rdata));

		printf("%s %s\n", rdata.id, rdata.data);
	}

	Close(c);

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	IniWinNet();

	SOCKET c = CreateClient();

	Connect(c, 2016, "1.209.148.150");

	Game(c);

	CloseWinNet();

	return 0;
}

