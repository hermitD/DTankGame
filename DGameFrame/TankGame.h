#pragma once
#include "dthegame.h"
#include "DrawGame.h"
#include "TankGameUserInfo.h"
#include "TankGameGlobals.h"


class CTankGame :
	public CDTheGame
{
public:
	CTankGame(void);
	~CTankGame(void);

	virtual void OnInit(void); // ��Ϸ��ʼ����ʱ������ when game init
	virtual void OnExit(void); // ��Ϸ����ʱ����� when game exit
	virtual void OnLPointDown(int nX, int nY); // ������������ʱ���� when left button down
	virtual void OnRPointDown(int nX, int nY); // ������Ҽ�����ʱ���� when right button down
	virtual void OnLPointDrag(int nX, int nY); // ����������קʱ���� when left button drag
	virtual void OnRPointDrag(int nX, int nY); // ������Ҽ���קʱ���� when right button drag
	virtual void OnLPointUp(int nX, int nY);	// ������Ҽ��ſ�ʱ���� when left button up
	virtual void OnRPointUp(int nX, int nY);	// ������Ҽ��ſ�ʱ���� when right button up
	virtual void OnKeyUp(WPARAM key);			// �����̰���ʱ���� when keyboard pressed
	virtual void OnKeyDown(WPARAM key);			// �����̷ſ�ʱ���� when keyboard released
	virtual void Update(int dt);				// ��ѭ���е��ã��������ݸ��� in main loop, use to update data
	virtual void Draw(int dt);					// ��ѭ���е��ã����ڻ�ͼ in main loop, use to draw something



	//Net things
	bool GetAllUserInfo();					//���������û���Ϣ
	bool Register( std::string& strUserName );//ע���û�
	bool Logout();							//ע���û�
	bool EnterRoom( int num );				//������Ϸ��
	bool ExitRoom();						//�˳���Ϸ��
	bool QueryBoard();						//��ѯ��Ϣ
	int GetUserCount()const;				//�õ��û���Ŀ
	bool IsNetFree();						//�ж������Ƿ����
	bool ExitGame();						//�˳���Ϸ
	bool IsGameStart();



	bool MoveTank(int direc); // ��������  2 0 1 3
	/*
	1.const ֻ������ member function
	2.const member function �����޸Ķ���������Ա
	3.const member function ���ܵ��÷� const member function
	*/

	CTankGameUserInfo GetUserInfo(const int num)const;	//�õ��û���Ϣ

	bool GetTankPos();	//��ȡ��������̹����Ϣ
	bool GetAllDatas(); //��ȡ���д��ڵ���Ϣ
	





	CDrawGame *m_pDrawGame;
	mapData m_stuMapData;

	CTankGameUserInfo m_info[128];	//�û���Ϣ
	int m_UserNum;					//�û�����
	bool m_bNetFree;

	bool m_bConnected;
	bool m_bEnteredRoom;

	char m_player1Pos[9]; 
	char m_player2Pos[9];
	//int m_player1Pos[9]; 
	//int m_player2Pos[9];

	char m_gamePlayer1or2;

	bool m_bgameIsStarted;

	


};

