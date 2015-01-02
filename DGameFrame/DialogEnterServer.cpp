// DialogEnterServer.cpp : 实现文件
//

#include "stdafx.h"
#include "DGameFrame.h"
#include "DialogEnterServer.h"
#include "afxdialogex.h"


// CDialogEnterServer 对话框

IMPLEMENT_DYNAMIC(CDialogEnterServer, CDialogEx)

CDialogEnterServer::CDialogEnterServer(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogEnterServer::IDD, pParent)
	, m_name(_T(""))
{

}

CDialogEnterServer::~CDialogEnterServer()
{
}

void CDialogEnterServer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, EDT_NAME, m_name);
	DDX_Control(pDX, EDT_PASSWORD, m_password);
	DDX_Control(pDX, IDC_IPADDRESS1, m_addressctrl);
}


BEGIN_MESSAGE_MAP(CDialogEnterServer, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogEnterServer::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogEnterServer 消息处理程序


void CDialogEnterServer::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned char a1,a2,a3,a4;
	m_addressctrl.GetAddress(a1,a2,a3,a4);
	m_address.Format(_T("%d.%d.%d.%d"),a1,a2,a3,a4);
		
	CDialogEx::OnOK();
}
