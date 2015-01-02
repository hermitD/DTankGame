#include "stdafx.h"
#include "TankGameUserInfo.h"


CTankGameUserInfo::CTankGameUserInfo(void)
{
	m_UserName[0]=m_UserIP[0]='\0';
	m_UserID=m_RoomNum=0;
	m_Free=false;
}


CTankGameUserInfo::~CTankGameUserInfo(void)
{
}

string CTankGameUserInfo::GetIP()
{
	return(m_UserIP);//返回用户的IP
}

unsigned int CTankGameUserInfo::GetID()
{
	return(m_UserID);//返回用户的ID
	
}

string CTankGameUserInfo::GetName()
{	
	return(m_UserName);//返回用户名
}

bool CTankGameUserInfo::SetIP(std::string IP)
{
	strcpy(m_UserIP,IP.c_str());//把用户的IP加入到m_UserIP
	return (true);
}

bool CTankGameUserInfo::SetID(unsigned int ID)
{
	m_UserID=ID;//把ID加入到m_UserID
	return(true);
}

bool CTankGameUserInfo::SetName(std::string Name)
{	
	strcpy(m_UserName,Name.c_str());//把用户名加入到m_UserName
	return(true);
}

bool CTankGameUserInfo::SetFree()
{
	return (m_Free=true);
}

bool CTankGameUserInfo::IsFree()
{
	return (m_Free);
}

bool CTankGameUserInfo::SetRoomNum(int num)
{
	m_RoomNum=num;//设定房间号
	return(true);
}

int CTankGameUserInfo::GetRoomNum()
{
	return(m_RoomNum);//返回房间号
}