#include "stdafx.h"

#include"GameManager.h"

 //the num for determine the rooms used;


	//增加一个用户到指定得游戏室中。
bool CGameManager::AddUser(unsigned int UserID, int RoomNum)
{
	for(int i=0;i<count;i++)
	{
		if(rooms[i].GetRoomNum()==RoomNum)//if there is a room with this Roomnum
			return(rooms[i].AddUser(UserID));
	}
	int num=count++;
	rooms[num].SetRoomNum(RoomNum);
	return(rooms[num].AddUser(UserID));
}
	//删除一个用户
bool CGameManager::DeleteUser(unsigned int UserID)
{
	if(FindRoom(UserID)!=NULL)
	{
		FindRoom(UserID)->DeleteUser(UserID);
		return(true);
	}
	else 
		return(false);  //there is no such user with this ID

}
//处理一个用户动作，返回该动作的结果。
const GAMERESULT CGameManager::UserPlay(ACTION  action)
{
    GAMERESULT result;
	if(FindRoom(action.UserID)!=NULL)
		return(FindRoom(action.UserID)->UserPlay(action));
	else 
	{
		result.GameEnd=true;
		result.NextPlayerID=action.UserID;
		return(result);
	}
}

//判断用户所在的游戏室是否可以开始游戏。
bool CGameManager::IsReady(unsigned int UserID)
{
	if(FindRoom(UserID)!=NULL)
		return(FindRoom(UserID)->IsReady());
	else 
		return(false);
}
 


//判断用户所在的游戏室是否已结束一场游戏。
bool CGameManager::IsGameOver(unsigned int UserID)
{
	if(FindRoom(UserID)->GetWinnerID()!=0)
		return(true);
	else 
		return(false);
}


//返回用户所在游戏室的游戏信息。
const char* CGameManager::GetGameInfo(unsigned int UserID)
{
	if(FindRoom(UserID)!=NULL)
		return(FindRoom(UserID)->GetGameInfo());
	else 
		return(null_info);
}

//用户所在的游戏室中，如果游戏已经结束，返回Winner的ID,否则返回0。

unsigned int CGameManager::GetWinnerID(unsigned int UserID)
{
	CGameRoom *room=FindRoom(UserID);
	if(room!=NULL)
		return(room->GetWinnerID());
	else 
		return(0);

}
	//返回与用户同在一个游戏室的另一个用户的ID.
unsigned int CGameManager::GetCoplayerID(unsigned int UserID)
{
	return(FindRoom(UserID)->GetCoplayerID(UserID));
}


	//返回用户所在游戏室中下一个轮到的用户的ID.
unsigned int CGameManager::GetNextPlayerID(unsigned int UserID)
{
	CGameRoom *room=FindRoom(UserID);
	if(room!=NULL)
		return(room->GetNextPlayerID());
	else
		return(0);
}



	//查找用户所在的游戏室，找不到则返回NULL
CGameRoom*  CGameManager::FindRoom(unsigned int UserID)
{
	for(int i=0;i<count;i++)
	{
		if(rooms[i].IsUserIn(UserID))
		{
		 	return(&rooms[i]);
		}
	}
	return(NULL);

}

bool CGameManager::RestartGame(unsigned int UserID)
{
	if(FindRoom(UserID)==NULL)
		return(false);
	else
		return(FindRoom(UserID)->Restart());
}



/*************************************************/
//end :>