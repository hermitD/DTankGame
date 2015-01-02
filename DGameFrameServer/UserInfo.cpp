#include "stdafx.h"

#include "userinfo.h"


using namespace std;

CUserInfo::CUserInfo()
{ 
	m_UserName[0]=m_UserIP[0]='\0';
	m_UserID=m_RoomNum=0;
	m_Free=false;
}


string CUserInfo::GetIP()
{
	return(m_UserIP);//返回用户的IP
}

unsigned int CUserInfo::GetID()
{
	return(m_UserID);//返回用户的ID
}

string CUserInfo::GetName()
{	
	return(m_UserName);//返回用户名
}

bool CUserInfo::SetIP(std::string IP)
{
	strcpy_s(m_UserIP,IP.c_str());//把用户的IP加入到m_UserIP
	return (true);
}

bool CUserInfo::SetID(unsigned int ID)
{
	m_UserID=ID;//把ID加入到m_UserID
	return(true);
}

bool CUserInfo::SetName(std::string Name)
{	
	strcpy_s(m_UserName,Name.c_str());//把用户名加入到m_UserName
	return(true);
}

bool CUserInfo::SetFree()
{
	return (m_Free=true);
}

bool CUserInfo::IsFree()
{
	return (m_Free);
}

bool CUserInfo::SetRoomNum(int num)
{
	m_RoomNum=num;//设定房间号
	return(true);
}

int CUserInfo::GetRoomNum()
{
	return(m_RoomNum);//返回房间号
}



	