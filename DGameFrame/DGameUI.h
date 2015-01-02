#pragma once
#include "DGameUIGraphic.h"
#include "DGameUISound.h"
#include "DGameUINet.h"


class CDGameUI
{
public:
	CDGameUI(void);
	~CDGameUI(void);

	CDGameUIGraphic *m_pGameUIGraphic;
	CDGameUISound	*m_pGameUISound;
	CDGameUINet		*m_pGameUINet;
};

