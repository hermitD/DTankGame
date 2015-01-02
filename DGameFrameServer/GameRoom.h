

#ifndef __GAMEROOM__
#define __GAMEROOM__

#include "global.h"
#include<stdlib.h>
#include<stdio.h>

class CGameRoom
{  
 protected:
	  int room_num;
	 
	  
 public:
	  virtual bool AddUser(unsigned int UserID)=0; //加入一个用户。
      virtual bool DeleteUser(unsigned int UserID)=0;//删除一个用户。
      bool SetRoomNum(int RoomNum);//设定游戏室编号
      int GetRoomNum( );//返回游戏室编号。 
      virtual bool IsReady( )=0;//是否可以开始游戏。
      virtual bool Restart( )=0;//重新开始游戏。
	  virtual const char* GetGameInfo()=0;//返回游戏信息
	  virtual unsigned int GetWinnerID()=0;//返回胜利者的ID
      virtual unsigned int GetCoplayerID(unsigned int UserID)=0;//返回对手的ID
	  virtual unsigned int GetNextPlayerID()=0;//返回下一个轮到的游戏者的ID
      virtual bool IsUserIn(unsigned int UserID)=0;//判断用户是不是在游戏室里。
      virtual GAMERESULT UserPlay(ACTION  action)=0;//处理一个用户动作，返回该动作的结果。
      
  };
#endif
