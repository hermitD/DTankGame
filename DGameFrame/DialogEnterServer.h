#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDialogEnterServer 对话框

class CDialogEnterServer : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogEnterServer)

public:
	CDialogEnterServer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogEnterServer();

// 对话框数据
	enum { IDD = IDD_ENTERSERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CEdit m_password;
	CIPAddressCtrl m_addressctrl;

	CString m_address;

	afx_msg void OnBnClickedOk();
};
