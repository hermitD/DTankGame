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

static CUserManager UserManager;	//用户管理器
static CGameManager GameManager;	//游戏管理器


bool g_RecepFunc(SOCKET sct)	//用来响应客户端请求的函数
{
	int OpNum,length,result,RoomNum;
	int tankdirec;
	int player1or2;

	unsigned int UserID=(unsigned int)sct; //是一个唯一标示 所以可以作为id
	ACTION action;
	char UserName[256];

	CUserInfo user;
	GAMERESULT gameresult;
			 // 接收数据缓冲区  // 接收数据缓冲区大小
	recv(sct,(char*)&OpNum,4,0);	//得到用户请求的代号
	switch(OpNum)
	{
		case QUERY_USERS:	//查询用户信息
			length=UserManager.GetUserCount() * sizeof(CUserInfo);
			send(sct,(char*)&length,4,0);
			send(sct,(const char*)UserManager.GetAllUser(),length,0);
			break;

		case ENTER_ROOM:	//进入游戏室
			if(recv(sct,(char*)&RoomNum,4,0)==SOCKET_ERROR)
				break;
			result=GameManager.AddUser(UserID,RoomNum)&&UserManager.SetRoomNum(UserID,RoomNum)?OK:FAILED;
			
			//进入游戏室后如果人数为2 则开始游戏
			if (((CTankGameRoom *)(GameManager.FindRoom(UserID)))->num_user==2)
			{
				//对两个坦克坐标进行初始化
				((CTankGameRoom *)(GameManager.FindRoom(UserID)))->IsReady();
			}
			send(sct,(char*)&result,4,0);
			break;

		case EXIT_ROOM:		//退出游戏室
			result=GameManager.DeleteUser(UserID)&&UserManager.SetRoomNum(UserID,0)?OK:FAILED;
			send(sct,(char*)&result,4,0);
			break;

		case USER_ACTION:	//用户作出动作
			if(recv(sct,(char*)&length,4,0)==SOCKET_ERROR)
				break;
			if(recv(sct,(char*)&action,length,0)==SOCKET_ERROR)
				break;
			if( !GameManager.IsReady(UserID) ||		//如果游戏is not ready 
				GameManager.GetNextPlayerID(UserID)!=UserID)//或者下一个轮到的人不是自己
			{                                //注意这里userID功能是找到相应的GameRoom
				gameresult.GameEnd=false;
				gameresult.NextPlayerID=GameManager.GetNextPlayerID(UserID);
				result=FAILED;
			}
			else //轮到用户自己了
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

		case QUERY_BOARD:	//查询信息
			length=225;
			send(sct,(char*)&length,4,0);
			send(sct,GameManager.GetGameInfo(UserID),length,0);
			break;

		case REGISTER_USER:	//注册用户
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

		case LOGOUT:	//注销用户
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
				//这里一次移动的是一个坦克的距离  最好是搞一个常量
				//haaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa 
				//look the code !! i'm the god :)
				switch (tankdirec)
					//2 0 1 3 上下左右
					//	l	t	r	b
					//0 1 2 3 4 5 6 7
					//这里由于是char 最大值为127 所以可能存在问题
				{
				case 0:
					//如果方向不同那么只改变方向
					//改变方向,改变坐标
					//下
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
					//左
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
					//上
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
					//右
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
					//2 0 1 3 上下左右
					//	l	t	r	b
					//0 1 2 3 4 5 6 7
					//这里由于是char 最大值为127 所以可能存在问题
				{
				case 0:

					//下
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
					//左
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
					//上
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
					//右
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
				//	send(sct,(char*)&temp1,4,0);	//接受数据位0
					result =FAILED;//错误			//直接用result 代表数据 错误
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



		//添加一个退出游戏的消息并返回false
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
	SetReceptionist(g_RecepFunc);	//设置相应用户请求的函数
}