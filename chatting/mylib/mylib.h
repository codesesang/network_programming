#include <WinSock2.h>
bool IniWinNet();
void CloseWinNet();

int CreateServer(int port);
SOCKET Listen();
SOCKET Accept();

int Send(SOCKET c, char* buf, int len);

int ReceiveN(SOCKET c, char* buf, int len);
SOCKET CreateClient();
int Connect(SOCKET c, int port, char* ip);
void Close(SOCKET s);