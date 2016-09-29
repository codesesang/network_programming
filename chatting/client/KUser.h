#pragma once
class CclientDlg;
// KUser 명령 대상입니다.

class KUser : public CSocket
{
public:
	KUser();
	virtual ~KUser();
	virtual void OnClose(int nErrorCode);
	CclientDlg* m_pView;
	int SendLogin(CString id);
	virtual void OnReceive(int nErrorCode);
	int SendMsg(CString id, CString msg);
};


