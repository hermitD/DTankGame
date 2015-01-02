#include "stdafx.h"

#include"GameManager.h"

 //the num for determine the rooms used;


	//����һ���û���ָ������Ϸ���С�
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
	//ɾ��һ���û�
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
//����һ���û����������ظö����Ľ����
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

//�ж��û����ڵ���Ϸ���Ƿ���Կ�ʼ��Ϸ��
bool CGameManager::IsReady(unsigned int UserID)
{
	if(FindRoom(UserID)!=NULL)
		return(FindRoom(UserID)->IsReady());
	else 
		return(false);
}
 


//�ж��û����ڵ���Ϸ���Ƿ��ѽ���һ����Ϸ��
bool CGameManager::IsGameOver(unsigned int UserID)
{
	if(FindRoom(UserID)->GetWinnerID()!=0)
		return(true);
	else 
		return(false);
}


//�����û�������Ϸ�ҵ���Ϸ��Ϣ��
const char* CGameManager::GetGameInfo(unsigned int UserID)
{
	if(FindRoom(UserID)!=NULL)
		return(FindRoom(UserID)->GetGameInfo());
	else 
		return(null_info);
}

//�û����ڵ���Ϸ���У������Ϸ�Ѿ�����������Winner��ID,���򷵻�0��

unsigned int CGameManager::GetWinnerID(unsigned int UserID)
{
	CGameRoom *room=FindRoom(UserID);
	if(room!=NULL)
		return(room->GetWinnerID());
	else 
		return(0);

}
	//�������û�ͬ��һ����Ϸ�ҵ���һ���û���ID.
unsigned int CGameManager::GetCoplayerID(unsigned int UserID)
{
	return(FindRoom(UserID)->GetCoplayerID(UserID));
}


	//�����û�������Ϸ������һ���ֵ����û���ID.
unsigned int CGameManager::GetNextPlayerID(unsigned int UserID)
{
	CGameRoom *room=FindRoom(UserID);
	if(room!=NULL)
		return(room->GetNextPlayerID());
	else
		return(0);
}



	//�����û����ڵ���Ϸ�ң��Ҳ����򷵻�NULL
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