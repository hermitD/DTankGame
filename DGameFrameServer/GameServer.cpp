#include "stdafx.h"

#include <memory.h>
#include "global.h"
#include "GameServer.h"
#include "UserInfo.h"
#include "UserManager.h"
#include "GameManager.h"
#include "ADOlib.h"
#include <winsock2.h>
#include <string>
using namespace std;

static CUserManager UserManager;	//�û�������
static CGameManager GameManager;	//��Ϸ������


bool g_RecepFunc(SOCKET sct)	//������Ӧ�ͻ�������ĺ���
{
	int OpNum,length,result,RoomNum;
	int tankdirec;
	int player1or2;

	unsigned int UserID=(unsigned int)sct; //��һ��Ψһ��ʾ ���Կ�����Ϊid
	ACTION action;
	char UserName[256];

	CUserInfo user;
	GAMERESULT gameresult;
			 // �������ݻ�����  // �������ݻ�������С
	recv(sct,(char*)&OpNum,4,0);	//�õ��û�����Ĵ���
	switch(OpNum)
	{
		case QUERY_USERS:	//��ѯ�û���Ϣ
			length=UserManager.GetUserCount() * sizeof(CUserInfo);
			send(sct,(char*)&length,4,0);
			send(sct,(const char*)UserManager.GetAllUser(),length,0);
			break;

		case ENTER_ROOM:	//������Ϸ��
			if(recv(sct,(char*)&RoomNum,4,0)==SOCKET_ERROR)
				break;
			result=GameManager.AddUser(UserID,RoomNum)&&UserManager.SetRoomNum(UserID,RoomNum)?OK:FAILED;
			
			//������Ϸ�Һ��������Ϊ2 ��ʼ��Ϸ
			if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->num_user==2)
			{
				//������̹��������г�ʼ��
				((CTankGameRoom *)(GameManager.FindRoom(UserID)))->IsReady();
			}
			send(sct,(char*)&result,4,0);
			break;

		case EXIT_ROOM:		//�˳���Ϸ��
			result=GameManager.DeleteUser(UserID)&&UserManager.SetRoomNum(UserID,0)?OK:FAILED;
			send(sct,(char*)&result,4,0);
			break;

		case USER_ACTION:	//�û���������
			if(recv(sct,(char*)&length,4,0)==SOCKET_ERROR)
				break;
			if(recv(sct,(char*)&action,length,0)==SOCKET_ERROR)
				break;
			if( !GameManager.IsReady(UserID) ||		//�����Ϸis not ready 
				GameManager.GetNextPlayerID(UserID)!=UserID)//������һ���ֵ����˲����Լ�
			{                                //ע������userID�������ҵ���Ӧ��GameRoom
				gameresult.GameEnd=false;
				gameresult.NextPlayerID=GameManager.GetNextPlayerID(UserID);
				result=FAILED;
			}
			else //�ֵ��û��Լ���
			{
				action.UserID=UserID;
				gameresult=GameManager.UserPlay(action);
				result=OK;
			}
			send(sct,(char*)&result,4,0);
			length=225;
			send(sct,(char*)&length,4,0);
			send(sct,GameManager.GetGameInfo(UserID),length,0);
			if(gameresult.GameEnd)
				GameManager.RestartGame(UserID);
			break;

		case QUERY_BOARD:	//��ѯ��Ϣ
			length=225;
			send(sct,(char*)&length,4,0);
			send(sct,GameManager.GetGameInfo(UserID),length,0);
			break;

		case REGISTER_USER:	//ע���û�
			{

			if(recv(sct,(char*)&length,4,0)==SOCKET_ERROR)
				break;
			if(recv(sct,(char*)UserName,length,0)==SOCKET_ERROR)
				break;
			UserName[length]='\0';
			user.SetID(UserID);
			user.SetName(UserName);
			user.SetIP("Unknown");
			CADOlib ado;
			int SqlResult = ado.SelectAName(UserName);
			send(sct,(char*)&SqlResult,4,0);
			result=UserManager.AddUser(user)?OK:FAILED;
			send(sct,(char*)&result,4,0);
			break;
			}

		case LOGOUT:	//ע���û�
			UserManager.DeleteUser(UserID);
			break;

		case MOVE_TANK:
			if(recv(sct,(char*)&tankdirec,4,0)==SOCKET_ERROR)
				break;

			if(recv(sct,(char*)&player1or2,4,0)==SOCKET_ERROR)
				break;
//			int temp;
			if (player1or2==1)
			{
				//����һ���ƶ�����һ��̹�˵ľ���  ����Ǹ�һ������
				//haaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa 
				//look the code !! i'm the god :)
				switch (tankdirec)
					//2 0 1 3 ��������
					//	l	t	r	b
					//0 1 2 3 4 5 6 7
					//����������char ���ֵΪ127 ���Կ��ܴ�������
				{
				case 0:
					//�������ͬ��ôֻ�ı䷽��
					//�ı䷽��,�ı�����
					//��
					//t +64 b +64
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[8]!=TANK_DIREC_DOWN)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[8]=TANK_DIREC_DOWN;
						break;
					}
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]+64<100)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]+=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[2]+=1;

						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]+=64;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]-=100;
						//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]-=36;
					}

					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[7]+64<100)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[7]+=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[6]+=1;

						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[7]+=64;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[7]-=100;
						//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]-=36;
					}
					break;
				case 1:
					//��
					//l -64 r -64
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[8]!=TANK_DIREC_LEFT)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[8]=TANK_DIREC_LEFT;
						break;
					}
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[8]!=TANK_DIREC_LEFT)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[8]=TANK_DIREC_LEFT;
						break;
					}
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[1]-64>=0)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[1]-=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[0]-=1;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[1]+=36;
						if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[1]>=100)
						{
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[0]+=1;
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[1]-=100;

						}
					}
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[5]-64>=0)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[5]-=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[4]-=1;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[5]+=36;
						if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[5]>=100)
						{
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[4]+=1;
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[5]-=100;

						}
					}


					break;
				case 2:
					//��
					//t -64 b -64
					//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]-64;
					//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[7]-64;
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[8]!=TANK_DIREC_TOP)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[8]=TANK_DIREC_TOP;
						break;
					}

					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]-64>=0)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]-=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[2]-=1;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]+=36;
						if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]>=100)
						{
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[2]+=1;
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]-=100;

						}
					}
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[7]-64>=0)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[7]-=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[6]-=1;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[7]+=36;
						if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[7]>=100)
						{
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[6]+=1;
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[7]-=100;

						}
					}
					break;
				case 3:
					//��
					//l +64 r +64
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[8]!=TANK_DIREC_RIGHT)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[8]=TANK_DIREC_RIGHT;
						break;
					}

					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[1]+64<100)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[1]+=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[0]+=1;

						//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[1]+=64;
						//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[1]-=100;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[1]-=36;
					}

					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[5]+64<100)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[5]+=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[4]+=1;

						//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[5]+=64;
						//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[5]-=100;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[5]-=36;
					}
					break;
					

				default:
					break;
				}
			}
			if (player1or2==2)
			{
				//haaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa 
				//look the code !! i'm the god :)
				switch (tankdirec)
					//2 0 1 3 ��������
					//	l	t	r	b
					//0 1 2 3 4 5 6 7
					//����������char ���ֵΪ127 ���Կ��ܴ�������
				{
				case 0:

					//��
					//t +64 b +64
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[8]!=TANK_DIREC_DOWN)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[8]=TANK_DIREC_DOWN;
						break;
					}

					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[3]+64<100)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[3]+=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[2]+=1;

						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[3]+=64;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[3]-=100;
						//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]-=36;
					}

					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[7]+64<100)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[7]+=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[6]+=1;

						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[7]+=64;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[7]-=100;
						//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]-=36;
					}
					break;

				case 1:
					//��
					//l -64 r -64
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[8]!=TANK_DIREC_LEFT)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[8]=TANK_DIREC_LEFT;
						break;
					}
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[1]-64>=0)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[1]-=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[0]-=1;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[1]+=36;
						if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[1]>=100)
						{
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[0]+=1;
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[1]-=100;

						}
					}
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[5]-64>=0)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[5]-=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[4]-=1;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[5]+=36;
						if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[5]>=100)
						{
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[4]+=1;
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[5]-=100;

						}
					}


					break;
				case 2:
					//��
					//t -64 b -64
					//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[3]-64;
					//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[7]-64;
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[8]!=TANK_DIREC_TOP)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[8]=TANK_DIREC_TOP;
						break;
					}
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[3]-64>=0)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[3]-=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[2]-=1;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[3]+=36;
						if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[3]>=100)
						{
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[2]+=1;
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[3]-=100;

						}
					}
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[7]-64>=0)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[7]-=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[6]-=1;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[7]+=36;
						if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[7]>=100)
						{
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[6]+=1;
							((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[7]-=100;

						}
					}
					break;
				case 3:
					//��
					//l +64 r +64
					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[8]!=TANK_DIREC_RIGHT)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[8]=TANK_DIREC_RIGHT;
					}

					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[1]+64<100)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[1]+=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[0]+=1;

						//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[1]+=64;
						//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[1]-=100;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[1]-=36;
					}

					if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[5]+64<100)
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[5]+=64;
					}else
					{
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[4]+=1;

						//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[5]+=64;
						//((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos[5]-=100;
						((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos[5]-=36;
					}
					break;


				default:
					break;
				}
			}
			





			//result=(tankdirec>=0&&tankdirec<=3)?OK:FAILED;
			result = OK;
			send(sct,(char*)&result,4,0);
			break;

		case GET_TANK_POS:

			//if(recv(sct,(char*)&tankdirec,4,0)==SOCKET_ERROR)
			//	break;
			{
			//if(((CTankGameRoom *)(GameManager.FindRoom(UserID)))->gamestart == false)
			//{
			//	length=4;
			//	result = FAILED;
			//	char *temp1Pose="error";
			//	char *temp2Pose="error";
			//	send(sct,(char*)&length,4,0);
			//	send(sct,(char*)&temp1Pose,length,0);
			//	send(sct,(char*)&temp2Pose,length,0);
			//	send(sct,(char*)&result,4,0);
			//	break;
			//}
			
			length=9;
			char temp1Pose[9],temp2Pose[9];
			memcpy(temp1Pose,((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos,sizeof(temp1Pose));
			memcpy(temp2Pose,((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos,sizeof(temp2Pose));
			
			//temp1Pose=((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player1Pos;
			//char *temp2Pose=((CTankGameRoom *)(GameManager.FindRoom(UserID)))->player2Pos;
			send(sct,(char*)&length,4,0);
			send(sct,(char*)&temp1Pose,length,0);
			send(sct,(char*)&temp2Pose,length,0);

			result = OK;
			send(sct,(char*)&result,4,0);
			break;

			}


		case IS_GAME_START:
			{
				if (((CTankGameRoom *)(GameManager.FindRoom(UserID))==NULL))
				{
					int temp1=0;
				//	send(sct,(char*)&temp1,4,0);	//��������λ0
					result =FAILED;//����			//ֱ����result �������� ����
					send(sct,(char*)&result,4,0);
					break;
				}
				int temp = ((CTankGameRoom *)(GameManager.FindRoom(UserID)))->gamestart;
				//send(sct,(char*)&temp,4,0);
				result =(temp==TRUE?OK:FAILED);
				send(sct,(char*)&result,4,0);
				break;

			}

		case GET_ALL_DATA:
			{
				length=sizeof(mapData);
				send(sct,(char*)&length,4,0);
				send(sct,(char*)&(((CTankGameRoom *)(GameManager.FindRoom(UserID)))->strMapdata),length,0);
				result =OK;
				send(sct,(char*)&result,4,0);


			}



		//���һ���˳���Ϸ����Ϣ������false
		case EXIT_GAME:
			return false;
			break;
	}
	return(true);
}

bool CGameServer::IsOK() const
{
	return(CTCPServer::IsOK());
}

bool CGameServer::TurnOn()
{
	return(CTCPServer::TurnOn());
}

bool CGameServer::TurnOff()
{
	return(CTCPServer::TurnOff());
}

string CGameServer::GetServerIP()
{
	return(GetIPAddr());
}

CGameServer::CGameServer(unsigned short nPortNum):CTCPServer(nPortNum)
{
	SetReceptionist(g_RecepFunc);	//������Ӧ�û�����ĺ���
}