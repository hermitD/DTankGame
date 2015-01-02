
// DGameFrameDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDGameFrameDlg 对话框



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


// CDGameFrameDlg 消息处理程序

BOOL CDGameFrameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	// TODO: 在此添加额外的初始化代码
	//ModifyStyle(NULL,WS_THICKFRAME);
	ModifyStyle(WS_THICKFRAME,NULL);	//使之不能resize
	
	srand((unsigned)time(NULL)); // wait for usr 

#ifdef ENABLE_CONSOLE
	::AllocConsole(); // open console resource
	//  直接关掉控制台窗口会出错，需要禁用掉
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
	//游戏初始化
	m_pDGameMain->OnInit();

	

	//初始化按钮使之符合逻辑~~
	m_btnEnterServer.EnableWindow(TRUE);
	m_btnEnterRoom.EnableWindow(FALSE);
	m_btnQuitRoom.EnableWindow(FALSE);

	

	
	//CGameTest *pGameTest = SAFE_NEW CGameTest; // new 出来后无需释放，由模板释放
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
	lvc.mask     =  LVCF_WIDTH|LVCF_TEXT;// 列表框样式
	lvc.cx       =  60; // 列表框宽度
	lvc.iImage   =  1;  // 与列表框关联的指定图像的索引值
	lvc.fmt      =  LVCFMT_LEFT; // 列表的对齐方式

	lvc.pszText  = L"ID";
	m_lstctrUsersOnline.InsertColumn(0,&lvc);

	lvc.pszText  = L"name";
	m_lstctrUsersOnline.InsertColumn(1,&lvc);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDGameFrameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDGameFrameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






BOOL CDGameFrameDlg::PreTranslateMessage(MSG* pMsg) //这里将函数封装一下使得 消息响应路由到自己的处理函数中
{
	// TODO: 在此添加专用代码和/或调用基类
	//various implements

	//这里处理过的消息要直接return True表示处理了,
	//不然还是继续路由到return CDialogEx::PreTranslateMessage(pMsg);也就是系统中
	//这里出现的问题是按键会出现'登'的声音,如此调整后现象消失
	//还有个好处截获了keyDown so 空格等不会自动去响应按键了
	//个人理解。

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
	else if (pMsg->message == WM_LBUTTONUP) // 鼠标弹起事件
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
	else if (pMsg->message == WM_RBUTTONUP) // 鼠标弹起事件
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
	else if (pMsg->message == WM_LBUTTONDOWN) // 鼠标按下事件
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
	else if (pMsg->message == WM_RBUTTONDOWN) // 鼠标按下事件
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
	else if(pMsg->message == WM_KEYDOWN) // 按下按键
	{
		m_pDGameMain->OnKeyDown(pMsg->wParam);	//http://msdn.microsoft.com/en-us/library/dd375731(v=vs.85).aspx
		return TRUE;
	}
	else if (pMsg->message == WM_KEYUP) // 放开按键
	{
		m_pDGameMain->OnKeyUp(pMsg->wParam);
		return TRUE;
	}

	//-- 这段代码是必须的
	if(pMsg->wParam == VK_RETURN) // 若按下的是回车键，则设为 Scroll Lock 键返回，避免按回车键退出窗口,无法避免按下F1键，正在改进中/已改进 //	ON_COMMAND(ID_HELP, CWinApp::OnHelp)//注释掉这一句按F1就不会调用系统帮助了
	{
		pMsg->wParam = VK_SCROLL;	
		//return TRUE;
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDGameFrameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//if (!IsIconic())		//最小化可以使游戏暂停刷新
	//{
//		if (nIDEvent == TIMERID_GAME)
//		{
//			KillTimer(TIMERID_GAME);
//
//			// 记录帧间隔
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
//			m_pDGameMain->Update(dt);//帧间隔
//
//			{ // 获取客户区域大小
//				CRect rc;
//				GetClientRect(&rc);
//				m_nWideClient=rc.Width();
//				m_nHightClient=rc.Height();
//				DeleteObject(rc);
//			}
//
//			CDC *pDC = GetDC();
//			// 双缓冲
//			CDC MemDC; // 首先定义一个显示设备对象，这个设备就是作为第二缓存的设备 GAME_PLAY_TIMER
//			CBitmap MemBitmap; //定义一个位图对象 	
//			// 随后建立与屏幕显示兼容的内存显示设备 
//			MemDC.CreateCompatibleDC(NULL); 	
//			// 这时还不能绘图，因为没有地方画   ^_^ 
//			// 下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小 
//			MemBitmap.CreateCompatibleBitmap(pDC,
//				m_pDGameUI->m_pGameUIGraphic->GetCameraW(),
//				m_pDGameUI->m_pGameUIGraphic->GetCameraH()); 	
//
//			// 将位图选入到内存显示设备中 
//			// 只有选入了 位图的内存显示设备 才有地方绘图，画到指定的位图上 
//			CBitmap   *pOldBit = MemDC.SelectObject(&MemBitmap); 	
//			// 先用背景色将位图清除干净，这里我用的是RGB(0,0,0)作为背景 
//			// 你也可以用自己应该用的颜色 
//			MemDC.FillSolidRect(m_pDGameUI->m_pGameUIGraphic->GetCameraX(), m_pDGameUI->m_pGameUIGraphic->GetCameraY(),
//				m_pDGameUI->m_pGameUIGraphic->GetCameraW(), m_pDGameUI->m_pGameUIGraphic->GetCameraH(), RGB(0,0,0)); // 每次都载入一大张RGB颜色的图
//
//
//			m_pDGameUI->m_pGameUIGraphic->SetMemDc(&MemDC); //设置memDC给画图层来画
//
////#ifdef GDIPLUSE_VERSION // set something
////			Graphics gh(MemDC.m_hDC);
////
////			m_pConbineFunc->m_pGraphic->SetGDIPlusWM(&gh);
////#endif
////
//			///***********************************************/ 绘图
//
//			m_pDGameMain->Draw(dt);
//
//
//
//#ifdef DEBUG_INFOS
//
//			{ // 用于显示调试信息
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
//				str.Format(_T("窗口大小(%3d, %3d)"), m_nWideClient, m_nHightClient);
//				m_pDGameUI->m_pGameUIGraphic->DrawTextWM(100, _T("宋体"), RGB(250, 250, 250), 640, 0, str);
//
//				str.Format(_T("游戏区域(%3d, %3d)"), GAME_SCREEN_W, GAME_SCREEN_H);
//				m_pDGameUI->m_pGameUIGraphic->DrawTextWM(100, _T("宋体"), RGB(250, 250, 250), 640, 14, str);
//				str.Format(_T("客户坐标(%3d, %3d)"), (int)point.x, (int)point.y);
//				m_pDGameUI->m_pGameUIGraphic->DrawTextWM(100, _T("宋体"), RGB(250, 250, 250), 640, 28, str);
//				str.Format(_T("游戏坐标(%3d, %3d)"), x, y);
//				m_pDGameUI->m_pGameUIGraphic->DrawTextWM(100, _T("宋体"), RGB(250, 250, 250), 640, 42, str);
//				str.Format(_T("游戏间隔 %3d"), dt);
//				m_pDGameUI->m_pGameUIGraphic->DrawTextWM(100, _T("宋体"), RGB(250, 250, 250), 640, 56, str);
//			}
//#endif			
//
//			///***********************************************/ 绘图结束，开始后事，不要在下面添加代码
//			// 这一段程序段是必须的//检测窗口大小//Dlg外的程序会用到WIDE_CLIENT和HIGH_CLIENT
//			// 将内存中的图拷贝到屏幕上进行显示 //-- 重要，将缓冲里面的绘制好的图放到pDC里才能显示//--这句话非常重要
////#ifdef GDIPLUSE_VERSION // set null
////			m_pConbineFunc->m_pGraphic->SetNullGDIPlusWM();
////#endif
////
//			m_pDGameUI->m_pGameUIGraphic->SetNullMemDC();
//			pDC->StretchBlt(0, 0, m_nWideClient, m_nHightClient,
//				&MemDC,
//				m_pDGameUI->m_pGameUIGraphic->GetCameraX(), m_pDGameUI->m_pGameUIGraphic->GetCameraY(),
//				m_pDGameUI->m_pGameUIGraphic->GetCameraW(), m_pDGameUI->m_pGameUIGraphic->GetCameraH(),
//				SRCCOPY); // 只截取屏幕大小的部分
//			// 绘图完成后的清理 
//			MemDC.SelectObject(pOldBit);
//			MemBitmap.DeleteObject(); 
//			MemDC.DeleteDC(); 
//			pOldBit->DeleteObject(); // 这句貌似可删可不删
//			pDC = NULL;
//			//ReleaseDC(pDC); // winhand.cpp Line XX错误 发生错误的一种可能的原因：
//			//程序中申请了DC的指针：CDC* pDC = this->GetDC()；在使用完后调用了删除函数：pDC->DeleteDC()；问题在这儿，在获取的对象的DC后，不要轻易使用用删除函数，应改成：ReleaseDC(pDC);除非是自己创建的DC，否则不要删除，发生这类错误一般很难定位。
//			SetTimer(TIMERID_GAME, MOMENT_TIME, NULL);
//		}


//以下结构是为了DTankGame重写
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


		m_pDGameMain->Update(dt);//帧间隔	--> datas 
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
	// unicode下 CString 转string的方法
	USES_CONVERSION;
//	CString str1;
	std::string address(W2A(dialogEnterServer.m_address));
	if (!m_pDGameMain->m_pDGameUI->m_pGameUINet->Connect(address))
	{
		MessageBox(_T("无法连接到服务器!"));
		return;
	}else
	{
		MessageBox(_T("成功连接到服务器!"));
				//设置按钮无效
		//EnableDlgItem(GetDlgItem(hWnd),IDOK,MF_BYCOMMAND|MF_GRAYED);
		m_btnEnterServer.EnableWindow(FALSE);
		m_btnEnterRoom.EnableWindow(TRUE);

	}
	//设置游戏中成员变量
	((CTankGame*)m_pTankGame)->m_bConnected = true;
	//m_bConnected=true;


	std::string name(W2A(dialogEnterServer.m_name));
	if(!((CTankGame*)m_pTankGame)->Register(name))
	{
		//MessageBox(_T("Failed to Register"));
		MessageBox(_T("Failed to Register,Error User"));
		AfxGetMainWnd()->CloseWindow();
		//MessageBox(_T("无法登陆到服务器。可能系统负荷过高，请稍后再试"));

		return;
	}
	

	//设置一下焦点 不然退出后会使得窗口焦点丢失导致按键消息发送不过去
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
		//MessageBox(_T("游戏室已满，请换一间再试"));
		MessageBox(_T("游戏室进入失败"));
		return;
	}else
	{
		CString temp;
		//temp.Format(_T("已成功进入游戏室 %d :)"),dialogEnterServer.m_nRoomNumber);
		temp.Format(_T("亲已成功接受治疗 %d :)"),dialogEnterServer.m_nRoomNumber);
		//MessageBox(temp);

		m_btnEnterRoom.EnableWindow(FALSE);
		m_btnQuitRoom.EnableWindow(TRUE);
	}

	//if(!m_pDGameMain->m_pDGameUI->m_pGameUINet->EnterRoom(dialogEnterServer.m_nRoomNumber))
	//{
	//	MessageBox(_T("游戏室已满，请换一间再试"));
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
	if( MessageBox(_T("确实要放弃治疗么亲？"),_T("确认"),MB_OKCANCEL) != IDOK )
		return;
	
	
	if(!((CTankGame*)m_pTankGame)->ExitRoom())
	{
		MessageBox(_T("退出失败！:("));
		return;
	}
	MessageBox(_T("退出成功 :)"));

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
	lvItem.state     = 0; // 子项的状态
	lvItem.stateMask = 0; // 状态有效的屏蔽位
	lvItem.iImage    = 0; // 与列表框关联的指定图像的索引值
	lvItem.iSubItem  = 0; // 子项的索引值（可以视为列号）

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
	// TODO: 在此添加控件通知处理程序代码
	m_gamePlayer1or2 = 1;

	((CTankGame*)m_pTankGame)->m_gamePlayer1or2 = m_gamePlayer1or2;
	m_btnPlayer2.EnableWindow(FALSE);

}


void CDGameFrameDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_gamePlayer1or2 = 2;
	((CTankGame*)m_pTankGame)->m_gamePlayer1or2 = m_gamePlayer1or2;
	m_btnPlayer1.EnableWindow(FALSE);
}
