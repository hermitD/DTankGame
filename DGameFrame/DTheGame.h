#pragma once
#include "DGameUI.h"

class CDTheGame
{
public:
	CDTheGame(void);
	//��̬ʱ��ý����������������Ϊvirtual,����������ʱ���ȵ����������������,�ٵ��û������������,�������delete���ǻ����ָ��,��ֻ���û������������.
	virtual~CDTheGame(void);

	virtual void OnInit(void) = 0; // ��Ϸ��ʼ����ʱ������ when game init
	virtual void OnExit(void); // ��Ϸ����ʱ����� when game exit
	virtual void OnLPointDown(int nX, int nY); // ������������ʱ���� when left button down
	virtual void OnRPointDown(int nX, int nY); // ������Ҽ�����ʱ���� when right button down
	virtual void OnLPointDrag(int nX, int nY); // ����������קʱ���� when left button drag
	virtual void OnRPointDrag(int nX, int nY); // ������Ҽ���קʱ���� when right button drag
	virtual void OnLPointUp(int nX, int nY); // ������Ҽ��ſ�ʱ���� when left button up
	virtual void OnRPointUp(int nX, int nY); // ������Ҽ��ſ�ʱ���� when right button up
	virtual void OnKeyUp(WPARAM key); // �����̰���ʱ���� when keyboard pressed
	virtual void OnKeyDown(WPARAM key); // �����̷ſ�ʱ���� when keyboard released
	virtual void Update(int dt); // ��ѭ���е��ã��������ݸ��� in main loop, use to update data
	virtual void Draw(int dt); // ��ѭ���е��ã����ڻ�ͼ in main loop, use to draw something
	void *m_pObserve;
	CDGameUI *m_pDGameUI;

	bool m_bLPointDownSign;
	bool m_bRPointDownSign;
	bool m_bKeyArray[ASCII_NUM];


};

