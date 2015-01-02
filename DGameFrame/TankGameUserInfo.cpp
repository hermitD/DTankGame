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
	return(m_UserIP);//�����û���IP
}

unsigned int CTankGameUserInfo::GetID()
{
	return(m_UserID);//�����û���ID
	
}

string CTankGameUserInfo::GetName()
{	
	return(m_UserName);//�����û���
}

bool CTankGameUserInfo::SetIP(std::string IP)
{
	strcpy(m_UserIP,IP.c_str());//���û���IP���뵽m_UserIP
	return (true);
}

bool CTankGameUserInfo::SetID(unsigned int ID)
{
	m_UserID=ID;//��ID���뵽m_UserID
	return(true);
}

bool CTankGameUserInfo::SetName(std::string Name)
{	
	strcpy(m_UserName,Name.c_str());//���û������뵽m_UserName
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
	m_RoomNum=num;//�趨�����
	return(true);
}

int CTankGameUserInfo::GetRoomNum()
{
	return(m_RoomNum);//���ط����
}