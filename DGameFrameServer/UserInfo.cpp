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
	return(m_UserIP);//�����û���IP
}

unsigned int CUserInfo::GetID()
{
	return(m_UserID);//�����û���ID
}

string CUserInfo::GetName()
{	
	return(m_UserName);//�����û���
}

bool CUserInfo::SetIP(std::string IP)
{
	strcpy_s(m_UserIP,IP.c_str());//���û���IP���뵽m_UserIP
	return (true);
}

bool CUserInfo::SetID(unsigned int ID)
{
	m_UserID=ID;//��ID���뵽m_UserID
	return(true);
}

bool CUserInfo::SetName(std::string Name)
{	
	strcpy_s(m_UserName,Name.c_str());//���û������뵽m_UserName
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
	m_RoomNum=num;//�趨�����
	return(true);
}

int CUserInfo::GetRoomNum()
{
	return(m_RoomNum);//���ط����
}



	