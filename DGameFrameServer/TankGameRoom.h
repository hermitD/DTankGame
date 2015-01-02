#ifndef __TANKGAMEROOM__
#define __TANKGAMEROOM__
#include"GameRoom.h"
class CTankGameRoom:public CGameRoom   //the drive class of CGameRoom
{

//used to be private

public:
	char board[15][15]; //0x00 for empty;0x01 for black; 0x02 for white
	//board[0][0]~[3] player1; black
	//board[1][0]~[3] player2; white


	mapData strMapdata;

	char player1Pos[9]; 
	char player2Pos[9];
	//int  player1Pos[9]; 
	//int  player2Pos[9];

    int num_user;
	unsigned int user_black;
	unsigned int user_white;
	unsigned int winner_id;
	unsigned int nextplayer_id;
	bool success(int row,int column);
	bool succ;
	
	bool gamestart;

	
public:
	CTankGameRoom();
		
	virtual bool AddUser(unsigned int UserID);//����һ���û���
    virtual bool DeleteUser(unsigned int UserID);//ɾ��һ���û���
    virtual bool IsReady();//�Ƿ���Կ�ʼ��Ϸ��
    virtual bool Restart();//���¿�ʼ��Ϸ��
    virtual bool IsUserIn(unsigned int UserID);//�ж��û��ǲ�������Ϸ���
    virtual GAMERESULT UserPlay(ACTION  action);//����һ���û����������ظö����Ľ����
    virtual const char* GetGameInfo();//�õ���Ϣ��
    virtual unsigned int GetWinnerID();//�����Ϸ�Ѿ�����������Winner��ID,���򷵻�0��
	virtual unsigned int GetCoplayerID(unsigned int UserID);//���ض��ֵ�ID
	virtual unsigned int GetNextPlayerID();//������һ���ֵ�����Ϸ�ߵ�ID

	//virtual void ConvertboardToPos();	//��board��Ϣת��ΪPlayerPos

};


#endif
