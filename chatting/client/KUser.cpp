// KUser.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "client.h"
#include "KUser.h"
#include "clientDlg.h"
#include "../protocol/my.h"

// KUser

KUser::KUser()
: m_pView(NULL)
{
}

KUser::~KUser()
{
}


// KUser ��� �Լ�


void KUser::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	//AfxMessageBox(_T("������ ������ ������"));

	m_pView->AddMsg(_T("������ ������ ������"));

	CSocket::OnClose(nErrorCode);
}


int KUser::SendLogin(CString id)
{
	S_DATA sdata;

	ZeroMemory(&sdata, sizeof(sdata));
	sdata.cmd = CMD_CS_LOGIN;
	_tcscpy_s(sdata.id, id);
	//wcscpy(sdata.id, id);

	Send(&sdata, sizeof(S_DATA));


	return 0;
}


void KUser::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	S_DATA rdata;
	ZeroMemory(&rdata, sizeof(S_DATA));

	Receive(&rdata, sizeof(S_DATA));

	if (CMD_SC_RMSG == rdata.cmd){
		m_pView->AddMsg(rdata.msg);
	}
	else{
		m_pView->AddMsg("unknown command");
	}

	CSocket::OnReceive(nErrorCode);
}


int KUser::SendMsg(CString id, CString msg)
{
	S_DATA sdata;

	ZeroMemory(&sdata, sizeof(sdata));
	sdata.cmd = CMD_CS_MSG;
	_tcscpy_s(sdata.id, id);
	//wcscpy(sdata.id, id);
	_tcscpy_s(sdata.msg, msg);

	Send(&sdata, sizeof(S_DATA));

	return 0;
}
