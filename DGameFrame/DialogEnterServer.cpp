// DialogEnterServer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DGameFrame.h"
#include "DialogEnterServer.h"
#include "afxdialogex.h"


// CDialogEnterServer �Ի���

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


// CDialogEnterServer ��Ϣ�������


void CDialogEnterServer::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned char a1,a2,a3,a4;
	m_addressctrl.GetAddress(a1,a2,a3,a4);
	m_address.Format(_T("%d.%d.%d.%d"),a1,a2,a3,a4);
		
	CDialogEx::OnOK();
}
