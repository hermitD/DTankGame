#pragma once

#include <string>
using namespace std;


class CTankGameUserInfo
{
public:
	CTankGameUserInfo(void);
	~CTankGameUserInfo(void);

private:
	char m_UserName[64];//�����û���
	char m_UserIP[32];//�����û���IP
	unsigned int m_UserID;//�����û���ID
	bool m_Free;//�����û��Ƿ����
	int m_RoomNum;//�����û����ڵķ���
public:
	std::string GetIP();//�õ�IP
	unsigned int GetID();//�õ�ID
	std::string GetName();//�õ��û���
	bool SetIP(std::string IP);//�趨IP
	bool SetID(unsigned int ID);//�趨ID
	bool SetName(std::string name);//�趨�û���
	bool SetFree();//�趨�û�����
	bool IsFree();//�ж��Ƿ����
	bool SetRoomNum(int num);//�趨�����
	int GetRoomNum();//�õ������


};

