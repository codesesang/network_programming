#include "stdafx.h"

#pragma comment(lib, "ws2_32")
#include "mylib.h"

//소켓 만들고 바인딩
SOCKET _g_s;
int CreateServer(int port){
	
	_g_s = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _g_s){
		return -1;
	}
	SOCKADDR_IN saddr;
	ZeroMemory(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (SOCKET_ERROR == bind(_g_s, (SOCKADDR *)&saddr, sizeof(saddr))){
		return -2;
	}

	return 0;
}

SOCKET Listen(){
	if (SOCKET_ERROR == listen(_g_s, SOMAXCONN)){
		return -1;
	}

	return 0;
}

SOCKET Accept(){
	SOCKET c;
	SOCKADDR_IN caddr;

	int len;
	len = sizeof(caddr);
	c = accept(_g_s, (SOCKADDR*)&caddr, &len);
	if (INVALID_SOCKET  == c){
		return INVALID_SOCKET; 
	}

	return c;
}

int Send(SOCKET c, char* buf, int len){
	
	int re=0;
	len = send(c, buf, len, 0);

	return re;
}

int ReceiveN(SOCKET c, char* buf, int len){


	int receive;
	char* ptr;
	int left;

	ptr = buf;
	left = len;

	while (0<left){
		receive = recv(c, ptr, left, 0);
		if (SOCKET_ERROR == receive){
			return -1;
		}
		else if (0 == receive){
			break;
		}
		else{
			left -= receive;
			ptr += receive;
		}

		
	}

	return len - left;
}

SOCKET CreateClient(){
	SOCKET c;
	c = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == c){
		return INVALID_SOCKET;
	}

	return c;
}

int Connect(SOCKET c, int port, char* ip){
	SOCKADDR_IN saddr;
	ZeroMemory(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(ip);

	if (SOCKET_ERROR == connect(c, (SOCKADDR*)&saddr, sizeof(saddr))){
		return -1;
	}

	return 0;
}

void Close(SOCKET s){
	closesocket(s);
}

//초기화
bool IniWinNet(){
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2,2), &wsa)){
		return false;
	}

	return true;
}

//종료
void CloseWinNet(){

	WSACleanup();

}