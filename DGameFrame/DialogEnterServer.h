#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDialogEnterServer �Ի���

class CDialogEnterServer : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogEnterServer)

public:
	CDialogEnterServer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogEnterServer();

// �Ի�������
	enum { IDD = IDD_ENTERSERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CEdit m_password;
	CIPAddressCtrl m_addressctrl;

	CString m_address;

	afx_msg void OnBnClickedOk();
};
