
#ifndef __GAMEMANAGER__
#define __GAMEMANAGER__

#include"TankGameRoom.h"

class CGameManager
{
private:
	CTankGameRoom rooms[128];
	int count;
	int room_num;
	char null_info[500];
	
public:
	CGameManager()
	{
		count=0;
		for(int i=0;i<500;i++)
			null_info[i]=0;
	}

	//����һ���û���ָ������Ϸ���С�
	bool AddUser(unsigned int UserID, int RoomNum);

	//ɾ��һ���û�
	bool DeleteUser(unsigned int UserID);

	//����һ���û����������ظö����Ľ����
	const GAMERESULT UserPlay(ACTION  action);

	//�ж��û����ڵ���Ϸ���Ƿ���Կ�ʼ��Ϸ��
	bool IsReady(unsigned int UserID);


    //�ж��û����ڵ���Ϸ���Ƿ��ѽ���һ����Ϸ��
	bool IsGameOver(unsigned int UserID);

	//�����û�������Ϸ�ҵ���Ϸ��Ϣ��
    const char* GetGameInfo(unsigned int UserID);

	//�û����ڵ���Ϸ���У������Ϸ�Ѿ�����������Winner��ID,���򷵻�0��
	unsigned int GetWinnerID(unsigned int UserID);

	//�������û�ͬ��һ����Ϸ�ҵ���һ���û���ID.
	unsigned int GetCoplayerID(unsigned int UserID);

	//�����û�������Ϸ������һ���ֵ����û���ID.
	unsigned int GetNextPlayerID(unsigned int UserID);

	//�����û����ڵ���Ϸ�ң��Ҳ����򷵻�NULL
	CGameRoom*  FindRoom(unsigned int UserID);

	//���¿�ʼ��Ϸ
	bool RestartGame(unsigned int UserID);
};
#endif
