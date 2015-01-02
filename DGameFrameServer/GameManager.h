
#ifndef __GAMEMANAGER__
#define __GAMEMANAGER__

#include"TankGameRoom.h"

class CGameManager
{
private:
	CTankGameRoom rooms[128];
	int count;
	int room_num;
	char null_info[500];
	
public:
	CGameManager()
	{
		count=0;
		for(int i=0;i<500;i++)
			null_info[i]=0;
	}

	//增加一个用户到指定得游戏室中。
	bool AddUser(unsigned int UserID, int RoomNum);

	//删除一个用户
	bool DeleteUser(unsigned int UserID);

	//处理一个用户动作，返回该动作的结果。
	const GAMERESULT UserPlay(ACTION  action);

	//判断用户所在的游戏室是否可以开始游戏。
	bool IsReady(unsigned int UserID);


    //判断用户所在的游戏室是否已结束一场游戏。
	bool IsGameOver(unsigned int UserID);

	//返回用户所在游戏室的游戏信息。
    const char* GetGameInfo(unsigned int UserID);

	//用户所在的游戏室中，如果游戏已经结束，返回Winner的ID,否则返回0。
	unsigned int GetWinnerID(unsigned int UserID);

	//返回与用户同在一个游戏室的另一个用户的ID.
	unsigned int GetCoplayerID(unsigned int UserID);

	//返回用户所在游戏室中下一个轮到的用户的ID.
	unsigned int GetNextPlayerID(unsigned int UserID);

	//查找用户所在的游戏室，找不到则返回NULL
	CGameRoom*  FindRoom(unsigned int UserID);

	//重新开始游戏
	bool RestartGame(unsigned int UserID);
};
#endif
