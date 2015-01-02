#include "stdafx.h"
#include "DGameMain.h"


CDGameMain::CDGameMain(void)
{
	
}
CDGameMain::CDGameMain(void * pObserve, CDGameUI *pDGameUI)
{
	m_pDTheGame = NULL;
	m_pDGameUI = pDGameUI;
	m_pObserve = pObserve;

	m_bLPointDownSign = false;
	m_bRPointDownSign = false;

	for (int i = 0; i < ASCII_NUM; i++)
	{
		m_bKeyArray[i] = false;
	}
}


CDGameMain::~CDGameMain(void)
{
	OnExit();
	m_pDGameUI = NULL;
	m_pObserve = NULL;
	SAFE_DELETE(m_pDTheGame);
}

void CDGameMain::OnInit( void) //像这种类似的函数就是在主程序中接受消息 然后给调用其成员来响应
{
	if (m_pDTheGame != NULL)
	{
		m_pDTheGame->OnInit();
	}

}

void CDGameMain::OnExit( void )
{
	if (m_pDTheGame != NULL)
	{
		m_pDTheGame->OnExit();
	}
}

void CDGameMain::Update( int dt )
{
	if (m_pDTheGame != NULL)
	{
		m_pDTheGame->Update(dt);
	}
}

void CDGameMain::Draw( int dt )
{
	if (m_pDTheGame != NULL)
	{
		m_pDTheGame->Draw(dt);
	}
}

void CDGameMain::OnLPointDrag( int nX, int nY )
{
	if (m_pDTheGame != NULL)
	{
		m_pDTheGame->OnLPointDrag(nX, nY);
	}
}

void CDGameMain::OnRPointDrag( int nX, int nY )
{
	if (m_pDTheGame != NULL)
	{
		m_pDTheGame->OnRPointDrag(nX, nY);
	}
}

void CDGameMain::OnLPointUp( int nX, int nY )
{
	m_bLPointDownSign = false;
	if (m_pDTheGame != NULL)
	{
		m_pDTheGame->m_bLPointDownSign = false;
		m_pDTheGame->OnLPointUp(nX, nY);
	}
}

void CDGameMain::OnRPointUp( int nX, int nY )
{
	m_bRPointDownSign = false;
	if (m_pDTheGame != NULL)
	{
		m_pDTheGame->m_bRPointDownSign = false;
		m_pDTheGame->OnRPointUp(nX, nY);
	}
}

void CDGameMain::OnLPointDown( int nX, int nY )
{
	m_bLPointDownSign = true;
	if (m_pDTheGame != NULL)
	{
		m_pDTheGame->m_bLPointDownSign = true;
		m_pDTheGame->OnLPointDown(nX, nY);
	}
}

void CDGameMain::OnRPointDown( int nX, int nY )
{
	m_bRPointDownSign = true;
	if (m_pDTheGame != NULL)
	{
		m_pDTheGame->m_bRPointDownSign = true;
		m_pDTheGame->OnRPointDown(nX, nY);
	}
}

void CDGameMain::OnKeyUp( WPARAM key )
{
	if (key >= 0 && key < ASCII_NUM)
	{
		m_bKeyArray[key] = false;
	}
	if (m_pDTheGame != NULL)
	{
		if (key >= 0 && key < ASCII_NUM)
		{
			m_pDTheGame->m_bKeyArray[key] = false;
		}
		m_pDTheGame->OnKeyUp(key);
	}
}

void CDGameMain::OnKeyDown( WPARAM key )
{
	if (key >= 0 && key < ASCII_NUM)
	{
		m_bKeyArray[key] = true;
	}
	if (m_pDTheGame != NULL)
	{
		if (key >= 0 && key < ASCII_NUM)
		{
			m_pDTheGame->m_bKeyArray[key] = true;
		}
		m_pDTheGame->OnKeyDown(key);
	}
}




//ChangeClientToGameCoor 
void CDGameMain::ChangeClientToGameCoor( int &gameX, int &gameY, int gameW, int gameH, int clientX, int clientY, int clientW, int clientH )
{
	if (clientW == 0)
	{
		clientW = 1;
	}
	if (clientH == 0)
	{
		clientH = 1;
	}
	gameX = (int)(gameW * clientX / (1.0f * clientW));
	gameY = (int)(gameH * clientY / (1.0f * clientH));
}



CDTheGame*  CDGameMain::RunLayer(CDTheGame *pDTheGame)
{
	CDTheGame* pLastGamePlay = m_pDTheGame;
	if (pLastGamePlay != NULL)	//如果不为空就退出
	{
		pLastGamePlay->OnExit();
	}
	m_pDTheGame = pDTheGame;	//把成员变量给本身然后进行初始化 进行新的游戏 
	if (m_pDTheGame != NULL)
	{
		//在这里把DGameMain与DTheGame_UIs的绑定
		m_pDTheGame->m_pObserve = this;
		m_pDTheGame->m_pDGameUI = m_pDGameUI;
		m_pDTheGame->OnInit();
	}

	return pLastGamePlay;
}