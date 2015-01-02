#pragma once
#include "dthegame.h"
class CGameTest :
	public CDTheGame
{
public:
	CGameTest(void);
	~CGameTest(void);

	virtual void OnInit(void);
	virtual void Draw(int dt); 

};

