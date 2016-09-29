// server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "../mylib/mylib.h"
#include "../protocol/my.h"
#include <vector>
using namespace std;

typedef struct _USER{
	SOCKET c;
	TCHAR id[10];
}S_USER;

vector<S_USER> g_vUser;
int GetUserIndex(SOCKET c);
void AddNewUser(SOCKET c);
void RemoveUser(SOCKET c);
DWORD WINAPI MyProc(LPVOID para);

void AddNewUser(SOCKET c){
	S_USER user;
	user.c = c;
	ZeroMemory(user.id, sizeof(user.id));

	g_vUser.push_back(user);
}

void RemoveUser(SOCKET c){
	int index = GetUserIndex(c);

	if (-1 != index){
		g_vUser.erase(g_vUser.begin() + index);
	}
}

int GetUserIndex(SOCKET c){
	for (int a = 0; a < g_vUser.size();a++){
		if (c == g_vUser[a].c){
			return a;
		}
	}
	return -1;
}

void SendRmsg(SOCKET c, TCHAR* id){
	S_DATA sdata;

	for (int a = 0; a < g_vUser.size();a++){
		ZeroMemory(&sdata, sizeof(S_DATA));
		sdata.cmd = CMD_SC_RMSG;
		strcpy(sdata.id, id);

		sprintf(sdata.msg, "%s님이 입장하셨습니다.\n", id);
		Send(g_vUser[a].c, (char*)&sdata, sizeof(S_DATA));
	}
}

void SendRmsgEx(SOCKET c, TCHAR* id, TCHAR* msg){
	S_DATA sdata;

	for (int a = 0; a < g_vUser.size(); a++){
		ZeroMemory(&sdata, sizeof(S_DATA));
		sdata.cmd = CMD_SC_RMSG;
		strcpy(sdata.id, id);
		strcpy(sdata.msg, msg);
		Send(g_vUser[a].c, (char*)&sdata, sizeof(S_DATA));
	}
}

DWORD WINAPI MyProc(LPVOID para){
	printf("새로운 접속이 왔습니다.\n");
	SOCKET c = (SOCKET)para;
	
	AddNewUser(c);
	while (1){
		//Sleep(3000);
		//break;

		S_DATA rdata;
		ZeroMemory(&rdata, sizeof(S_DATA));

		int re = ReceiveN(c, (char*)&rdata, sizeof(S_DATA));
		if (-1 == re){
			break;
		}
		//printf("%d", re);

		if (CMD_CS_LOGIN == rdata.cmd){
			printf("새로운 유저 로그인 : %s\n", rdata.id);
			//SendRmsg(c, rdata.id);
			TCHAR msg[80];
			sprintf(msg, "%s님이 입장하셨습니다.", rdata.id);
			SendRmsgEx(c, rdata.id, msg);
			
		}
		else if (CMD_CS_MSG == rdata.cmd){
			TCHAR msg[80];
			sprintf(msg, "%s : %s", rdata.id, rdata.msg);
			SendRmsgEx(c, rdata.id, msg);
		}
		else{
			printf("unknown command\n");
			break;
		}
	}
	Close(c);
	RemoveUser(c);

	printf("유저 접속 종료\n");
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	IniWinNet();

	CreateServer(2016);

	Listen();

	while (1){
		SOCKET c = Accept();

		CreateThread(NULL, 0, MyProc, (LPVOID)c, NULL, 0);

	}

	CloseWinNet();
	return 0;
}

