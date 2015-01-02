#pragma once
#include "DGameUI.h"

class CDTheGame
{
public:
	CDTheGame(void);
	//多态时最好将基类的析构函数设为virtual,这样在析构时会先调用子类的析构函数,再调用基类的析构函数,否则如果delete的是基类的指针,则只调用基类的析构函数.
	virtual~CDTheGame(void);

	virtual void OnInit(void) = 0; // 游戏初始化的时候会调用 when game init
	virtual void OnExit(void); // 游戏结束时会调用 when game exit
	virtual void OnLPointDown(int nX, int nY); // 当鼠标左键按下时调用 when left button down
	virtual void OnRPointDown(int nX, int nY); // 当鼠标右键按下时调用 when right button down
	virtual void OnLPointDrag(int nX, int nY); // 当鼠标左键拖拽时调用 when left button drag
	virtual void OnRPointDrag(int nX, int nY); // 当鼠标右键拖拽时调用 when right button drag
	virtual void OnLPointUp(int nX, int nY); // 当鼠标右键放开时调用 when left button up
	virtual void OnRPointUp(int nX, int nY); // 当鼠标右键放开时调用 when right button up
	virtual void OnKeyUp(WPARAM key); // 当键盘按下时调用 when keyboard pressed
	virtual void OnKeyDown(WPARAM key); // 当键盘放开时调用 when keyboard released
	virtual void Update(int dt); // 主循环中调用，用于数据更新 in main loop, use to update data
	virtual void Draw(int dt); // 主循环中调用，用于绘图 in main loop, use to draw something
	void *m_pObserve;
	CDGameUI *m_pDGameUI;

	bool m_bLPointDownSign;
	bool m_bRPointDownSign;
	bool m_bKeyArray[ASCII_NUM];


};

