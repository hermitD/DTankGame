#pragma once


// CDialogEnterRoom �Ի���

class CDialogEnterRoom : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogEnterRoom)

public:
	CDialogEnterRoom(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogEnterRoom();

// �Ի�������
	enum { IDD = IDD_ENTERROOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nRoomNumber;
};
