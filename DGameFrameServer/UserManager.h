#ifndef __USERMANAGER__
#define __USERMANAGER__

#include "userinfo.h"
class CUserManager
{
private:
	CUserInfo m_users[128];//定义用户信息
	int m_count;//定义用于记录游戏人数
public:
	CUserManager();
	bool AddUser(CUserInfo user);//增加一个用户
	bool DeleteUser(unsigned int User_ID);//删除一个用户
	bool SetRoomNum(unsigned int User_ID,int Room_num);//得到房间号
	int GetUserCount();//返回用户数目
	const CUserInfo* GetAllUser();//返回所有用户的信息
};

#endif