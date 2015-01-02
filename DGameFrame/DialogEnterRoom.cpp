// DialogEnterRoom.cpp : 实现文件
//

#include "stdafx.h"
#include "DGameFrame.h"
#include "DialogEnterRoom.h"
#include "afxdialogex.h"


// CDialogEnterRoom 对话框

IMPLEMENT_DYNAMIC(CDialogEnterRoom, CDialogEx)

CDialogEnterRoom::CDialogEnterRoom(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogEnterRoom::IDD, pParent)
	, m_nRoomNumber(0)
{

}

CDialogEnterRoom::~CDialogEnterRoom()
{
}

void CDialogEnterRoom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, EDT_ROOMNUMBER, m_nRoomNumber);
}


BEGIN_MESSAGE_MAP(CDialogEnterRoom, CDialogEx)
END_MESSAGE_MAP()


// CDialogEnterRoom 消息处理程序
