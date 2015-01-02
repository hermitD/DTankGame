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

	virtual void OnInit(void); // 游戏初始化的时候会调用 when game init
	virtual void OnExit(void); // 游戏结束时会调用 when game exit
	virtual void OnLPointDown(int nX, int nY); // 当鼠标左键按下时调用 when left button down
	virtual void OnRPointDown(int nX, int nY); // 当鼠标右键按下时调用 when right button down
	virtual void OnLPointDrag(int nX, int nY); // 当鼠标左键拖拽时调用 when left button drag
	virtual void OnRPointDrag(int nX, int nY); // 当鼠标右键拖拽时调用 when right button drag
	virtual void OnLPointUp(int nX, int nY);	// 当鼠标右键放开时调用 when left button up
	virtual void OnRPointUp(int nX, int nY);	// 当鼠标右键放开时调用 when right button up
	virtual void OnKeyUp(WPARAM key);			// 当键盘按下时调用 when keyboard pressed
	virtual void OnKeyDown(WPARAM key);			// 当键盘放开时调用 when keyboard released
	virtual void Update(int dt);				// 主循环中调用，用于数据更新 in main loop, use to update data
	virtual void Draw(int dt);					// 主循环中调用，用于绘图 in main loop, use to draw something



	//Net things
	bool GetAllUserInfo();					//返回所有用户信息
	bool Register( std::string& strUserName );//注册用户
	bool Logout();							//注销用户
	bool EnterRoom( int num );				//进入游戏室
	bool ExitRoom();						//退出游戏室
	bool QueryBoard();						//查询信息
	int GetUserCount()const;				//得到用户数目
	bool IsNetFree();						//判断网络是否空闲
	bool ExitGame();						//退出游戏
	bool IsGameStart();



	bool MoveTank(int direc); // 上下左右  2 0 1 3
	/*
	1.const 只能声名 member function
	2.const member function 不能修改对象的任意成员
	3.const member function 不能调用非 const member function
	*/

	CTankGameUserInfo GetUserInfo(const int num)const;	//得到用户信息

	bool GetTankPos();	//获取服务器的坦克信息
	bool GetAllDatas(); //获取所有存在的信息
	





	CDrawGame *m_pDrawGame;
	mapData m_stuMapData;

	CTankGameUserInfo m_info[128];	//用户信息
	int m_UserNum;					//用户数量
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

