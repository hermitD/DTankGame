#ifndef __TANKGAMEROOM__
#define __TANKGAMEROOM__
#include"GameRoom.h"
class CTankGameRoom:public CGameRoom   //the drive class of CGameRoom
{

//used to be private

public:
	char board[15][15]; //0x00 for empty;0x01 for black; 0x02 for white
	//board[0][0]~[3] player1; black
	//board[1][0]~[3] player2; white


	mapData strMapdata;

	char player1Pos[9]; 
	char player2Pos[9];
	//int  player1Pos[9]; 
	//int  player2Pos[9];

    int num_user;
	unsigned int user_black;
	unsigned int user_white;
	unsigned int winner_id;
	unsigned int nextplayer_id;
	bool success(int row,int column);
	bool succ;
	
	bool gamestart;

	
public:
	CTankGameRoom();
		
	virtual bool AddUser(unsigned int UserID);//加入一个用户。
    virtual bool DeleteUser(unsigned int UserID);//删除一个用户。
    virtual bool IsReady();//是否可以开始游戏。
    virtual bool Restart();//重新开始游戏。
    virtual bool IsUserIn(unsigned int UserID);//判断用户是不是在游戏室里。
    virtual GAMERESULT UserPlay(ACTION  action);//处理一个用户动作，返回该动作的结果。
    virtual const char* GetGameInfo();//得到信息。
    virtual unsigned int GetWinnerID();//如果游戏已经结束，返回Winner的ID,否则返回0。
	virtual unsigned int GetCoplayerID(unsigned int UserID);//返回对手的ID
	virtual unsigned int GetNextPlayerID();//返回下一个轮到的游戏者的ID

	//virtual void ConvertboardToPos();	//将board信息转化为PlayerPos

};


#endif
