#include "stdafx.h"
#include"usermanager.h"



CUserManager::CUserManager()
{
	m_count=0;//给m_count付初值表示有0个游戏者
}

bool CUserManager::AddUser(CUserInfo user)
{
	m_users[m_count++]=user;
	return(m_count<128);
}

bool CUserManager::DeleteUser(unsigned int UserID)//删除一个游戏者，并把下一个游戏者前提
{
	for(int i=0;i<m_count;i++)
	{
		if(m_users[i].GetID()==UserID)
		{
			for(int j=i+1;j<m_count;j++)
				m_users[j-1]=m_users[j];
			m_count--;
			return(true);
		}
	}
	return(false);
}

bool CUserManager::SetRoomNum(unsigned int UserID,int RoomNum)
{
	for(int i=0;i<m_count;i++)
		if(m_users[i].GetID()==UserID)
		{
			m_users[i].SetRoomNum(RoomNum);
			return(true);
		}
	return(false);
}

int CUserManager::GetUserCount()
{
	return(m_count);//返回游戏人数
}

const CUserInfo* CUserManager::GetAllUser()
{
	return(m_users);
}
