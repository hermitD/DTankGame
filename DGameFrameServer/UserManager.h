#ifndef __USERMANAGER__
#define __USERMANAGER__

#include "userinfo.h"
class CUserManager
{
private:
	CUserInfo m_users[128];//�����û���Ϣ
	int m_count;//�������ڼ�¼��Ϸ����
public:
	CUserManager();
	bool AddUser(CUserInfo user);//����һ���û�
	bool DeleteUser(unsigned int User_ID);//ɾ��һ���û�
	bool SetRoomNum(unsigned int User_ID,int Room_num);//�õ������
	int GetUserCount();//�����û���Ŀ
	const CUserInfo* GetAllUser();//���������û�����Ϣ
};

#endif