#include "stdafx.h"
#include "GameTest.h"


CGameTest::CGameTest(void)
{
}


CGameTest::~CGameTest(void)
{
}


void CGameTest::OnInit(void)
{

}

void CGameTest::Draw(int dt)
{
	m_pDGameUI->m_pGameUIGraphic->DrawRect(300,300,100,100,RGB(255,255,255));

}