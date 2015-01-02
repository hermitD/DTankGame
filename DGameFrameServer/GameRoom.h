

#ifndef __GAMEROOM__
#define __GAMEROOM__

#include "global.h"
#include<stdlib.h>
#include<stdio.h>

class CGameRoom
{  
 protected:
	  int room_num;
	 
	  
 public:
	  virtual bool AddUser(unsigned int UserID)=0; //����һ���û���
      virtual bool DeleteUser(unsigned int UserID)=0;//ɾ��һ���û���
      bool SetRoomNum(int RoomNum);//�趨��Ϸ�ұ��
      int GetRoomNum( );//������Ϸ�ұ�š� 
      virtual bool IsReady( )=0;//�Ƿ���Կ�ʼ��Ϸ��
      virtual bool Restart( )=0;//���¿�ʼ��Ϸ��
	  virtual const char* GetGameInfo()=0;//������Ϸ��Ϣ
	  virtual unsigned int GetWinnerID()=0;//����ʤ���ߵ�ID
      virtual unsigned int GetCoplayerID(unsigned int UserID)=0;//���ض��ֵ�ID
	  virtual unsigned int GetNextPlayerID()=0;//������һ���ֵ�����Ϸ�ߵ�ID
      virtual bool IsUserIn(unsigned int UserID)=0;//�ж��û��ǲ�������Ϸ���
      virtual GAMERESULT UserPlay(ACTION  action)=0;//����һ���û����������ظö����Ľ����
      
  };
#endif
