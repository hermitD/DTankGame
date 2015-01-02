#include "stdafx.h"
#include "DGameUI.h"


CDGameUI::CDGameUI(void)
{
	m_pGameUIGraphic = NULL;
	m_pGameUISound = NULL;
	m_pGameUINet = NULL;

	m_pGameUIGraphic = SAFE_NEW CDGameUIGraphic;
	if (m_pGameUIGraphic == NULL)
	{
		MessageBox(NULL, _T("Failed to create CDGameUIGraphic"), _T("Error!"), MB_OK | MB_ICONASTERISK);
		exit(0);
	}
	m_pGameUISound = SAFE_NEW CDGameUISound;
	if (m_pGameUISound == NULL)
	{
		MessageBox(NULL, _T("Failed to create CDGameUISound"), _T("Error!"), MB_OK | MB_ICONASTERISK);
		exit(0);
	}
	m_pGameUINet = SAFE_NEW CDGameUINet;
	if (m_pGameUINet == NULL)
	{
		MessageBox(NULL, _T("Failed to create CDGameUINet"), _T("Error!"), MB_OK | MB_ICONASTERISK);
		exit(0);
	}
}


CDGameUI::~CDGameUI(void)
{
	SAFE_DELETE(m_pGameUIGraphic);
	SAFE_DELETE(m_pGameUISound);
	SAFE_DELETE(m_pGameUINet);
}
