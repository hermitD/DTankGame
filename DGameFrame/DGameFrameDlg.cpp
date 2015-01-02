
// DGameFrameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DGameFrame.h"
#include "DGameFrameDlg.h"
#include "DGameDefines.h"
#include "GameTest.h"
#include "TankGame.h"

#include "DialogEnterServer.h"
#include "DialogEnterRoom.h"

#include "afxdialogex.h"
#include <windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDGameFrameDlg �Ի���



CDGameFrameDlg::CDGameFrameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDGameFrameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDGameFrameDlg::~CDGameFrameDlg(void)
{

	SAFE_DELETE(m_pDGameMain);
	SAFE_DELETE(m_pDGameUI);

#ifdef ENABLE_CONSOLE
	FreeConsole();
#endif
}



void CDGameFrameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btnEnterServer);
	DDX_Control(pDX, IDC_BUTTON2, m_btnEnterRoom);
	DDX_Control(pDX, IDC_BUTTON3, m_btnQuitRoom);
	DDX_Control(pDX, IDC_LIST1, m_lstctrUsersOnline);
	DDX_Control(pDX, IDC_BUTTON4, m_btnPlayer1);
	DDX_Control(pDX, IDC_BUTTON5, m_btnPlayer2);
}

BEGIN_MESSAGE_MAP(CDGameFrameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CDGameFrameDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDGameFrameDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDGameFrameDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDGameFrameDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDGameFrameDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CDGameFrameDlg ��Ϣ�������

BOOL CDGameFrameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//ModifyStyle(NULL,WS_THICKFRAME);
	ModifyStyle(WS_THICKFRAME,NULL);	//ʹ֮����resize
	
	srand((unsigned)time(NULL)); // wait for usr 

#ifdef ENABLE_CONSOLE
	::AllocConsole(); // open console resource
	//  ֱ�ӹص�����̨���ڻ������Ҫ���õ�
	{
		TCHAR buf[100];
		GetConsoleTitle(buf, 100);
		HWND hwnd = :: FindWindow(NULL, buf);
		HMENU hmenu = :: GetSystemMenu(hwnd, FALSE);
		::RemoveMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
	}
	freopen("CONOUT$", "w+t", stdout);
	
	PRINTLOG("Hello World!\n"); // for tests
#endif

//	_CrtSetBreakAlloc(359);	 set for find leak 
//	_CrtSetBreakAlloc(350);
	m_dwLastTime = 0;
	{
	CRect rc;
	GetClientRect(&rc);
	m_nWideClient=rc.Width();
	m_nHightClient=rc.Height();
	DeleteObject(rc);
	}

	m_pDGameUI = SAFE_NEW CDGameUI;
	if (m_pDGameUI == NULL)
	{
		MessageBox(_T("UI errors~~"));
		exit(0);
	}
	m_pDGameMain = SAFE_NEW CDGameMain(this, m_pDGameUI);
	if (m_pDGameMain == NULL)
	{
		MessageBox(_T("Main Game errors~~"));
		exit(0);
	}
	//��Ϸ��ʼ��
	m_pDGameMain->OnInit();

	

	//��ʼ����ťʹ֮�����߼�~~
	m_btnEnterServer.EnableWindow(TRUE);
	m_btnEnterRoom.EnableWindow(FALSE);
	m_btnQuitRoom.EnableWindow(FALSE);

	

	
	//CGameTest *pGameTest = SAFE_NEW CGameTest; // new �����������ͷţ���ģ���ͷ�
	//m_pDGameMain->RunLayer(pGameTest);
	//pGameTest = NULL;

	//CTankGame *pTankGame = SAFE_NEW CTankGame;
	//pTankGame->m_pDrawGame->m_pView = this; // only in tht tank game;
	//m_pDGameMain->RunLayer(pTankGame);
	//pTankGame = NULL;


	m_pTankGame = SAFE_NEW CTankGame;
	((CTankGame*)m_pTankGame)->m_pDrawGame->m_pView = this;	//only in tht tank game;
	m_pDGameMain->RunLayer(m_pTankGame);


	//pTankGame->m_pDrawGame->Init(this);	//only int the tank game




	


	SetTimer(TIMERID_GAME, MOMENT_TIME, NULL);



	LVCOLUMN lvc = {0};
	lvc.mask     =  LVCF_WIDTH|LVCF_TEXT;// �б����ʽ
	lvc.cx       =  60; // �б����
	lvc.iImage   =  1;  // ���б�������ָ��ͼ�������ֵ
	lvc.fmt      =  LVCFMT_LEFT; // �б�Ķ��뷽ʽ

	lvc.pszText  = L"ID";
	m_lstctrUsersOnline.InsertColumn(0,&lvc);

	lvc.pszText  = L"name";
	m_lstctrUsersOnline.InsertColumn(1,&lvc);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDGameFrameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDGameFrameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDGameFrameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






BOOL CDGameFrameDlg::PreTranslateMessage(MSG* pMsg) //���ｫ������װһ��ʹ�� ��Ϣ��Ӧ·�ɵ��Լ��Ĵ�������
{
	// TODO: �ڴ����ר�ô����/����û���
	//various implements

	//���ﴦ�������ϢҪֱ��return True��ʾ������,
	//��Ȼ���Ǽ���·�ɵ�return CDialogEx::PreTranslateMessage(pMsg);Ҳ����ϵͳ��
	//������ֵ������ǰ��������'��'������,��˵�����������ʧ
	//���и��ô��ػ���keyDown so �ո�Ȳ����Զ�ȥ��Ӧ������
	//������⡣

	if (pMsg->message == WM_MOUSEMOVE)
	{
		if (m_pDGameMain->m_bLPointDownSign)
		{
			CPoint point;
			int x = 0;
			int y = 0;

			GetCursorPos(&point);
			ScreenToClient(&point);
			m_pDGameMain->ChangeClientToGameCoor(x, y, m_pDGameUI->m_pGameUIGraphic->GetCameraW(), m_pDGameUI->m_pGameUIGraphic->GetCameraH(),
				(int)point.x, (int)point.y, m_nWideClient, m_nHightClient);
			x += m_pDGameUI->m_pGameUIGraphic->GetCameraX();
			y += m_pDGameUI->m_pGameUIGraphic->GetCameraY();
			m_pDGameMain->OnLPointDrag(x, y);
			//return TRUE;
		}
	}
	else if (pMsg->message == WM_LBUTTONUP) // ��굯���¼�
	{
		
		CPoint point;
		int x = 0;
		int y = 0;

		GetCursorPos(&point);
		ScreenToClient(&point);
		m_pDGameMain->ChangeClientToGameCoor(x, y, m_pDGameUI->m_pGameUIGraphic->GetCameraW(), m_pDGameUI->m_pGameUIGraphic->GetCameraH(),
			(int)point.x, (int)point.y, m_nWideClient, m_nHightClient);
		x += m_pDGameUI->m_pGameUIGraphic->GetCameraX();
		y += m_pDGameUI->m_pGameUIGraphic->GetCameraY();
		m_pDGameMain->OnLPointUp(x, y);

		PRINTLOG("LBUTTONUP X: %d Y: %d\n",x,y);
		//return TRUE;

	}
	else if (pMsg->message == WM_RBUTTONUP) // ��굯���¼�
	{
		CPoint point;
		int x = 0;
		int y = 0;

		GetCursorPos(&point);
		ScreenToClient(&point);
		m_pDGameMain->ChangeClientToGameCoor(x, y, m_pDGameUI->m_pGameUIGraphic->GetCameraW(), m_pDGameUI->m_pGameUIGraphic->GetCameraH(),
			(int)point.x, (int)point.y, m_nWideClient, m_nHightClient);
		x += m_pDGameUI->m_pGameUIGraphic->GetCameraX();
		y += m_pDGameUI->m_pGameUIGraphic->GetCameraY();
		m_pDGameMain->OnRPointUp(x, y);
		//return TRUE;
	}
	else if (pMsg->message == WM_LBUTTONDOWN) // ��갴���¼�
	{
		CPoint point;
		int x = 0;
		int y = 0;

		GetCursorPos(&point);
		ScreenToClient(&point);
		m_pDGameMain->ChangeClientToGameCoor(x, y, m_pDGameUI->m_pGameUIGraphic->GetCameraW(), m_pDGameUI->m_pGameUIGraphic->GetCameraH(),
			(int)point.x, (int)point.y, m_nWideClient, m_nHightClient);
		x += m_pDGameUI->m_pGameUIGraphic->GetCameraX();
		y += m_pDGameUI->m_pGameUIGraphic->GetCameraY();
		m_pDGameMain->OnLPointDown(x, y);

		//return TRUE;
	}
	else if (pMsg->message == WM_RBUTTONDOWN) // ��갴���¼�
	{
		CPoint point;
		int x = 0;
		int y = 0;

		GetCursorPos(&point);
		ScreenToClient(&point);
		m_pDGameMain->ChangeClientToGameCoor(x, y, m_pDGameUI->m_pGameUIGraphic->GetCameraW(), m_pDGameUI->m_pGameUIGraphic->GetCameraH(),
			(int)point.x, (int)point.y, m_nWideClient, m_nHightClient);
		x += m_pDGameUI->m_pGameUIGraphic->GetCameraX();
		y += m_pDGameUI->m_pGameUIGraphic->GetCameraY();
		m_pDGameMain->OnRPointDown(x, y);

		//return TRUE;
	}
	else if(pMsg->message == WM_KEYDOWN) // ���°���
	{
		m_pDGameMain->OnKeyDown(pMsg->wParam);	//http://msdn.microsoft.com/en-us/library/dd375731(v=vs.85).aspx
		return TRUE;
	}
	else if (pMsg->message == WM_KEYUP) // �ſ�����
	{
		m_pDGameMain->OnKeyUp(pMsg->wParam);
		return TRUE;
	}

	//-- ��δ����Ǳ����
	if(pMsg->wParam == VK_RETURN) // �����µ��ǻس���������Ϊ Scroll Lock �����أ����ⰴ�س����˳�����,�޷����ⰴ��F1�������ڸĽ���/�ѸĽ� //	ON_COMMAND(ID_HELP, CWinApp::OnHelp)//ע�͵���һ�䰴F1�Ͳ������ϵͳ������
	{
		pMsg->wParam = VK_SCROLL;	
		//return TRUE;
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDGameFrameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//if (!IsIconic())		//��С������ʹ��Ϸ��ͣˢ��
	//{
//		if (nIDEvent == TIMERID_GAME)
//		{
//			KillTimer(TIMERID_GAME);
//
//			// ��¼֡���
//			DWORD dwCurTime = ::GetTickCount();
//			DWORD dt = 0;
//			dt = dwCurTime - m_dwLastTime;
//			if (dt > MAX_MOMENT_TIME)
//			{
//				dt = MOMENT_TIME;
//			}
//			m_dwLastTime = dwCurTime;
//
//
//			m_pDGameMain->Update(dt);//֡���
//
//			{ // ��ȡ�ͻ������С
//				CRect rc;
//				GetClientRect(&rc);
//				m_nWideClient=rc.Width();
//				m_nHightClient=rc.Height();
//				DeleteObject(rc);
//			}
//
//			CDC *pDC = GetDC();
//			// ˫����
//			CDC MemDC; // ���ȶ���һ����ʾ�豸��������豸������Ϊ�ڶ�������豸 GAME_PLAY_TIMER
//			CBitmap MemBitmap; //����һ��λͼ���� 	
//			// ���������Ļ��ʾ���ݵ��ڴ���ʾ�豸 
//			MemDC.CreateCompatibleDC(NULL); 	
//			// ��ʱ�����ܻ�ͼ����Ϊû�еط���   ^_^ 
//			// ���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С 
//			MemBitmap.CreateCompatibleBitmap(pDC,
//				m_pDGameUI->m_pGameUIGraphic->GetCameraW(),
//				m_pDGameUI->m_pGameUIGraphic->GetCameraH()); 	
//
//			// ��λͼѡ�뵽�ڴ���ʾ�豸�� 
//			// ֻ��ѡ���� λͼ���ڴ���ʾ�豸 ���еط���ͼ������ָ����λͼ�� 
//			CBitmap   *pOldBit = MemDC.SelectObject(&MemBitmap); 	
//			// ���ñ���ɫ��λͼ����ɾ����������õ���RGB(0,0,0)��Ϊ���� 
//			// ��Ҳ�������Լ�Ӧ���õ���ɫ 
//			MemDC.FillSolidRect(m_pDGameUI->m_pGameUIGraphic->GetCameraX(), m_pDGameUI->m_pGameUIGraphic->GetCameraY(),
//				m_pDGameUI->m_pGameUIGraphic->GetCameraW(), m_pDGameUI->m_pGameUIGraphic->GetCameraH(), RGB(0,0,0)); // ÿ�ζ�����һ����RGB��ɫ��ͼ
//
//
//			m_pDGameUI->m_pGameUIGraphic->SetMemDc(&MemDC); //����memDC����ͼ������
//
////#ifdef GDIPLUSE_VERSION // set something
////			Graphics gh(MemDC.m_hDC);
////
////			m_pConbineFunc->m_pGraphic->SetGDIPlusWM(&gh);
////#endif
////
//			///***********************************************/ ��ͼ
//
//			m_pDGameMain->Draw(dt);
//
//
//
//#ifdef DEBUG_INFOS
//
//			{ // ������ʾ������Ϣ
//				CString str;
//				CPoint point;
//				int x = 0;
//				int y = 0;
//
//				GetCursorPos(&point);
//				ScreenToClient(&point);
//				m_pDGameMain->ChangeClientToGameCoor(x, y,  m_pDGameUI->m_pGameUIGraphic->GetCameraW(),  m_pDGameUI->m_pGameUIGraphic->GetCameraH(),
//					(int)point.x, (int)point.y, m_nWideClient, m_nHightClient);
//				x +=  m_pDGameUI->m_pGameUIGraphic->GetCameraX();
//				y +=  m_pDGameUI->m_pGameUIGraphic->GetCameraY();
//
//
//				str.Format(_T("���ڴ�С(%3d, %3d)"), m_nWideClient, m_nHightClient);
//				m_pDGameUI->m_pGameUIGraphic->DrawTextWM(100, _T("����"), RGB(250, 250, 250), 640, 0, str);
//
//				str.Format(_T("��Ϸ����(%3d, %3d)"), GAME_SCREEN_W, GAME_SCREEN_H);
//				m_pDGameUI->m_pGameUIGraphic->DrawTextWM(100, _T("����"), RGB(250, 250, 250), 640, 14, str);
//				str.Format(_T("�ͻ�����(%3d, %3d)"), (int)point.x, (int)point.y);
//				m_pDGameUI->m_pGameUIGraphic->DrawTextWM(100, _T("����"), RGB(250, 250, 250), 640, 28, str);
//				str.Format(_T("��Ϸ����(%3d, %3d)"), x, y);
//				m_pDGameUI->m_pGameUIGraphic->DrawTextWM(100, _T("����"), RGB(250, 250, 250), 640, 42, str);
//				str.Format(_T("��Ϸ��� %3d"), dt);
//				m_pDGameUI->m_pGameUIGraphic->DrawTextWM(100, _T("����"), RGB(250, 250, 250), 640, 56, str);
//			}
//#endif			
//
//			///***********************************************/ ��ͼ��������ʼ���£���Ҫ��������Ӵ���
//			// ��һ�γ�����Ǳ����//��ⴰ�ڴ�С//Dlg��ĳ�����õ�WIDE_CLIENT��HIGH_CLIENT
//			// ���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ //-- ��Ҫ������������Ļ��ƺõ�ͼ�ŵ�pDC�������ʾ//--��仰�ǳ���Ҫ
////#ifdef GDIPLUSE_VERSION // set null
////			m_pConbineFunc->m_pGraphic->SetNullGDIPlusWM();
////#endif
////
//			m_pDGameUI->m_pGameUIGraphic->SetNullMemDC();
//			pDC->StretchBlt(0, 0, m_nWideClient, m_nHightClient,
//				&MemDC,
//				m_pDGameUI->m_pGameUIGraphic->GetCameraX(), m_pDGameUI->m_pGameUIGraphic->GetCameraY(),
//				m_pDGameUI->m_pGameUIGraphic->GetCameraW(), m_pDGameUI->m_pGameUIGraphic->GetCameraH(),
//				SRCCOPY); // ֻ��ȡ��Ļ��С�Ĳ���
//			// ��ͼ��ɺ������ 
//			MemDC.SelectObject(pOldBit);
//			MemBitmap.DeleteObject(); 
//			MemDC.DeleteDC(); 
//			pOldBit->DeleteObject(); // ���ò�ƿ�ɾ�ɲ�ɾ
//			pDC = NULL;
//			//ReleaseDC(pDC); // winhand.cpp Line XX���� ���������һ�ֿ��ܵ�ԭ��
//			//������������DC��ָ�룺CDC* pDC = this->GetDC()����ʹ����������ɾ��������pDC->DeleteDC()��������������ڻ�ȡ�Ķ����DC�󣬲�Ҫ����ʹ����ɾ��������Ӧ�ĳɣ�ReleaseDC(pDC);�������Լ�������DC������Ҫɾ���������������һ����Ѷ�λ��
//			SetTimer(TIMERID_GAME, MOMENT_TIME, NULL);
//		}


//���½ṹ��Ϊ��DTankGame��д
	if (nIDEvent == TIMERID_GAME)
	{
		KillTimer(TIMERID_GAME);

		DWORD dwCurTime = ::GetTickCount();
		DWORD dt = 0;
		dt = dwCurTime - m_dwLastTime;
		if (dt > MAX_MOMENT_TIME)
		{
			dt = MOMENT_TIME;
		}
		m_dwLastTime = dwCurTime;


		m_pDGameMain->Update(dt);//֡���	--> datas 
		m_pDGameMain->Draw(dt);	//	--> GUIs


		static int updateUsers;
		if (updateUsers++ >30)
		{
			updateUserOnlines();
			updateUsers=0;
		}
		

		SetTimer(TIMERID_GAME, MOMENT_TIME, NULL);
	}

	
	/*}*/
	CDialogEx::OnTimer(nIDEvent);
}

void CDGameFrameDlg::OnBnClickedButton1()
{
	//Enter Server
	
	CDialogEnterServer dialogEnterServer;
	if( dialogEnterServer.DoModal() == IDCANCEL)
		return;
	// unicode�� CString תstring�ķ���
	USES_CONVERSION;
//	CString str1;
	std::string address(W2A(dialogEnterServer.m_address));
	if (!m_pDGameMain->m_pDGameUI->m_pGameUINet->Connect(address))
	{
		MessageBox(_T("�޷����ӵ�������!"));
		return;
	}else
	{
		MessageBox(_T("�ɹ����ӵ�������!"));
				//���ð�ť��Ч
		//EnableDlgItem(GetDlgItem(hWnd),IDOK,MF_BYCOMMAND|MF_GRAYED);
		m_btnEnterServer.EnableWindow(FALSE);
		m_btnEnterRoom.EnableWindow(TRUE);

	}
	//������Ϸ�г�Ա����
	((CTankGame*)m_pTankGame)->m_bConnected = true;
	//m_bConnected=true;


	std::string name(W2A(dialogEnterServer.m_name));
	if(!((CTankGame*)m_pTankGame)->Register(name))
	{
		//MessageBox(_T("Failed to Register"));
		MessageBox(_T("Failed to Register,Error User"));
		AfxGetMainWnd()->CloseWindow();
		//MessageBox(_T("�޷���½��������������ϵͳ���ɹ��ߣ����Ժ�����"));

		return;
	}
	

	//����һ�½��� ��Ȼ�˳����ʹ�ô��ڽ��㶪ʧ���°�����Ϣ���Ͳ���ȥ
	this->SetFocus();

	return;
	
}


void CDGameFrameDlg::OnBnClickedButton2()
{
	//Enter Room

	CDialogEnterRoom dialogEnterServer;

	if( dialogEnterServer.DoModal() == IDCANCEL)
		return;

	if (!((CTankGame*)m_pTankGame)->EnterRoom(dialogEnterServer.m_nRoomNumber))
	{
		//MessageBox(_T("��Ϸ���������뻻һ������"));
		MessageBox(_T("��Ϸ�ҽ���ʧ��"));
		return;
	}else
	{
		CString temp;
		//temp.Format(_T("�ѳɹ�������Ϸ�� %d :)"),dialogEnterServer.m_nRoomNumber);
		temp.Format(_T("���ѳɹ��������� %d :)"),dialogEnterServer.m_nRoomNumber);
		//MessageBox(temp);

		m_btnEnterRoom.EnableWindow(FALSE);
		m_btnQuitRoom.EnableWindow(TRUE);
	}

	//if(!m_pDGameMain->m_pDGameUI->m_pGameUINet->EnterRoom(dialogEnterServer.m_nRoomNumber))
	//{
	//	MessageBox(_T("��Ϸ���������뻻һ������"));
	//	return;
	//}
	


	((CTankGame*)m_pTankGame)->m_bEnteredRoom= true;
	//m_bEnteredRoom=true;


	this->SetFocus();
	return;
}


void CDGameFrameDlg::OnBnClickedButton3()
{
	//  Quit Room
	if( MessageBox(_T("ȷʵҪ��������ô�ף�"),_T("ȷ��"),MB_OKCANCEL) != IDOK )
		return;
	
	
	if(!((CTankGame*)m_pTankGame)->ExitRoom())
	{
		MessageBox(_T("�˳�ʧ�ܣ�:("));
		return;
	}
	MessageBox(_T("�˳��ɹ� :)"));

	m_btnEnterRoom.EnableWindow(TRUE);
	m_btnQuitRoom.EnableWindow(FALSE);

	((CTankGame*)m_pTankGame)->m_bEnteredRoom= false;
//	m_bEnteredRoom=false;


	this->SetFocus();

	return;

	
}
void CDGameFrameDlg::updateUserOnlines()
{

	m_lstctrUsersOnline.DeleteAllItems();


	LVITEM lvItem    = {0};
	lvItem.mask      = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM|LVIF_STATE;
	lvItem.state     = 0; // �����״̬
	lvItem.stateMask = 0; // ״̬��Ч������λ
	lvItem.iImage    = 0; // ���б�������ָ��ͼ�������ֵ
	lvItem.iSubItem  = 0; // ���������ֵ��������Ϊ�кţ�

	int nRow = 0;
	CString strID;
	CString strName;

	m_objUserInfo=((CTankGame*)m_pTankGame)->m_info;
	m_userInfoNum=((CTankGame*)m_pTankGame)->m_UserNum;
	for (int i=0;i<m_userInfoNum;i++,nRow++)
	{
		strID.Format(_T("%d"),m_objUserInfo[i].GetID());
		//strName.Format(_T("%s"),m_objUserInfo[i].GetName().c_str());
		strName =m_objUserInfo[i].GetName().c_str();
		lvItem.iItem = nRow;
		m_lstctrUsersOnline.InsertItem(&lvItem);
		m_lstctrUsersOnline.SetItemText(nRow,0,strID);
		m_lstctrUsersOnline.SetItemText(nRow,1,strName);

	}


}

void CDGameFrameDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_gamePlayer1or2 = 1;

	((CTankGame*)m_pTankGame)->m_gamePlayer1or2 = m_gamePlayer1or2;
	m_btnPlayer2.EnableWindow(FALSE);

}


void CDGameFrameDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_gamePlayer1or2 = 2;
	((CTankGame*)m_pTankGame)->m_gamePlayer1or2 = m_gamePlayer1or2;
	m_btnPlayer1.EnableWindow(FALSE);
}
