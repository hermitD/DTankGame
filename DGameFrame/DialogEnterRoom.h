#pragma once


// CDialogEnterRoom 对话框

class CDialogEnterRoom : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogEnterRoom)

public:
	CDialogEnterRoom(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogEnterRoom();

// 对话框数据
	enum { IDD = IDD_ENTERROOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nRoomNumber;
};
