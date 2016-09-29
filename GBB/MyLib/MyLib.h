#include <WinSock2.h>


bool IniWinNet();
int CloseWinNet();

int CreateServer(int port);
int Close(SOCKET s);

int Listen();
SOCKET Accept();
int Send(SOCKET c, char* buf, int len);
int Receive(SOCKET c, char* buf, int len);
SOCKET CreateClient();
int Connect(SOCKET c, int port, char* ip);