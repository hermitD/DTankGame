
// DGameFrameDlg.h : 头文件
//

#pragma once
#include "DGameMain.h"
#include "DGameUI.h"
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"

#include "TankGameUserInfo.h"




// CDGameFrameDlg 对话框
class CDGameFrameDlg : public CDialogEx
{
// 构造
public:

	int m_nHightClient;
	int m_nWideClient;


	CDGameMain *m_pDGameMain;
	CDGameUI *m_pDGameUI;

	


	// if other game just change
	//CTankGame *m_pTankGame;
	CDTheGame *m_pTankGame;

public:
	CDGameFrameDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CDGameFrameDlg(void);

// 对话框数据
	enum { IDD = IDD_DGAMEFRAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	DWORD m_dwLastTime; 


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	afx_msg void OnBnClickedButton1();
	CButton m_btnEnterServer;
	afx_msg void OnBnClickedButton2();
	CButton m_btnEnterRoom;
	afx_msg void OnBnClickedButton3();
	CButton m_btnQuitRoom;

	CListCtrl m_lstctrUsersOnline;
	CTankGameUserInfo* m_objUserInfo;
	int	m_userInfoNum;
	void updateUserOnlines();


	CButton m_btnPlayer1;
	afx_msg void OnBnClickedButton4();
	
	CButton m_btnPlayer2;
	afx_msg void OnBnClickedButton5();
	char m_gamePlayer1or2;
};
