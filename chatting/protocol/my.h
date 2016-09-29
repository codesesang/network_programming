

//my.h

#define CMD_CS_LOGIN 0
#define CMD_CS_MSG 1
#define CMD_SC_RMSG 2

typedef struct _S_DATA{
	int cmd;
	TCHAR id[10];
	TCHAR msg[80];
}S_DATA;