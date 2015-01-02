#pragma once

#include <string>
using namespace std;


class CTankGameUserInfo
{
public:
	CTankGameUserInfo(void);
	~CTankGameUserInfo(void);

private:
	char m_UserName[64];//定义用户名
	char m_UserIP[32];//定义用户的IP
	unsigned int m_UserID;//定义用户的ID
	bool m_Free;//定义用户是否空闲
	int m_RoomNum;//定义用户所在的房间
public:
	std::string GetIP();//得到IP
	unsigned int GetID();//得到ID
	std::string GetName();//得到用户名
	bool SetIP(std::string IP);//设定IP
	bool SetID(unsigned int ID);//设定ID
	bool SetName(std::string name);//设定用户名
	bool SetFree();//设定用户空闲
	bool IsFree();//判断是否空闲
	bool SetRoomNum(int num);//设定房间号
	int GetRoomNum();//得到房间号


};

