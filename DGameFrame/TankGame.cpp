#include "stdafx.h"
#include "TankGame.h"
#include "Bullet.h"
#include "TankGameGlobals.h"

CTankGame::CTankGame(void)
{
	m_pDrawGame = SAFE_NEW CDrawGame ;

	m_UserNum = 0;
	m_bNetFree=true;
	m_bConnected = false;

	m_gamePlayer1or2=0;
	m_bgameIsStarted=false;
}


CTankGame::~CTankGame(void)
{
	if (!m_bConnected)
	{
		goto Final;
	}
	ExitRoom();
	Logout();
	int bRtn = ExitGame();
	m_pDGameUI->m_pGameUINet->Disconnect();

Final:	
	SAFE_DELETE(m_pDrawGame);

}

void CTankGame::OnInit (void)
{
	m_pDrawGame->Init(m_pDrawGame->m_pView);
	m_pDrawGame->DrawGameInit();
}

void CTankGame::OnExit( void )
{

}

void CTankGame::OnLPointUp( int nX, int nY )
{
	
}

void CTankGame::OnRPointUp( int nX, int nY )
{

}

void CTankGame::OnLPointDrag( int nX, int nY )
{

}

void CTankGame::OnRPointDrag( int nX, int nY )
{

}

void CTankGame::OnLPointDown( int nX, int nY )
{

}

void CTankGame::OnRPointDown( int nX, int nY )
{

}

void CTankGame::OnKeyUp( WPARAM key )
{

}
CRect rc(CRect(200,100,264,164));//坦克起始坐标 注意与CDrawGame::DrawGame() 中CTank的一致性。不然会混乱
void CTankGame::OnKeyDown( WPARAM key )
{

	if (m_bgameIsStarted==FALSE)
		return;
//		goto DoNothing;
		

	vector<stuCmdObj> cmdObj;
	stuCmdObj cmd;				//命令结构体
	cmd.nId = 1;
	cmd.cmd = MOVE;
	cmd.type = TANK;

	switch (key)
	{

	case 's':				
	case 'S':
		/*if (MoveTank(2))
		{
			rc+=CPoint(0,20);
			cmd.rcXy = rc;
			cmd.nDir = 0;
			cmdObj.push_back(cmd);
			m_pDrawGame->EditDrawGameObj(cmdObj);
		}*/
		MoveTank(0);
		break;
	case 'a':
	case 'A':
		/*if (MoveTank(1))
		{
			rc-=CPoint(20,0);
			cmd.rcXy = rc;
			cmd.nDir = 1;
			cmdObj.push_back(cmd);
			m_pDrawGame->EditDrawGameObj(cmdObj);
		}*/
		MoveTank(1);
		break;
	case 'w':
	case 'W':
		/*if (MoveTank(0))
		{
			rc-=CPoint(0,20);
			cmd.rcXy = rc;
			cmd.nDir = 2;
			cmdObj.push_back(cmd);
			m_pDrawGame->EditDrawGameObj(cmdObj);
		}*/
		MoveTank(2);
		break;
	case 'd':
	case 'D':
		/*if (MoveTank(3))
		{
			rc+=CPoint(20,0);
			cmd.rcXy = rc;
			cmd.nDir = 3;
			cmdObj.push_back(cmd);
			m_pDrawGame->EditDrawGameObj(cmdObj);
		}*/
		MoveTank(3);
		break;
	case ' ':
		cmd.cmd = FIRE;
		cmdObj.push_back(cmd);
		m_pDrawGame->EditDrawGameObj(cmdObj);
		break;
	default:
		break;
	}

//DoNothing

}

void CTankGame::Update( int dt )
{

	/*if(!m_bConnected)
	return;
	CMyGameDoc *pDoc = (CMyGameDoc*)GetActiveDocument();

	if(pDoc->m_client.IsNetFree())
	pDoc->m_client.GetAllUserInfo();
	if(m_bEnteredRoom && pDoc->m_client.IsNetFree())
	pDoc->m_client.QueryBoard();
	pDoc->UpdateAllViews(NULL);*/
	

	static int bulletfresh;
	bulletfresh++;
	if (bulletfresh == 5)
	{
		for (int i=0;i<m_pDrawGame->m_vBullet.size();i++)
		{
			((CBullet*)((m_pDrawGame->m_vBullet)[i].pDrawObj))->MoveOneStep();
		}

		bulletfresh =0;
	}

	//现在更新的信息存在m_player1Pos, m_player2Pos中
	//然后依照这些更新出来的信息来把vec进行相应的更新

	//用户1的更新
	if (m_bgameIsStarted)
	{
			GetTankPos(); //更新所有坦克的信息
		vector<stuCmdObj> cmdObj;
		stuCmdObj cmd;				//命令结构体
		cmd.nId = 1;
		cmd.cmd = MOVE;
		cmd.type = TANK;
		CRect cRect1((int)(m_player1Pos[0]*100+m_player1Pos[1]),(int)(m_player1Pos[2]*100+m_player1Pos[3]),
			(int)(m_player1Pos[4]*100+m_player1Pos[5]),(int)(m_player1Pos[6]*100+m_player1Pos[7]));
		//	rc+=CPoint(20,0);
		cmd.rcXy = cRect1;
		//2013  上下左右
		switch (m_player1Pos[8])
		{
		case TANK_DIREC_TOP:
			cmd.nDir =2;
			break;
		case TANK_DIREC_DOWN:
			cmd.nDir =0;
			break;
		case TANK_DIREC_LEFT:
			cmd.nDir =1;
			break;
		case TANK_DIREC_RIGHT:
			cmd.nDir =3;
			break;
		default:
			break;
		}
		cmdObj.push_back(cmd);


		//用户2的更新
		cmd.nId = 2;
		cmd.cmd = MOVE;
		cmd.type = TANK;
		CRect cRect2((int)(m_player2Pos[0]*100+m_player2Pos[1]),(int)(m_player2Pos[2]*100+m_player2Pos[3]),
			(int)(m_player2Pos[4]*100+m_player2Pos[5]),(int)(m_player2Pos[6]*100+m_player2Pos[7]));
		//	rc+=CPoint(20,0);
		cmd.rcXy = cRect2;
		//2013  上下左右
		switch (m_player2Pos[8])
		{
		case TANK_DIREC_TOP:
			cmd.nDir =2;
			break;
		case TANK_DIREC_DOWN:
			cmd.nDir =0;
			break;
		case TANK_DIREC_LEFT:
			cmd.nDir =1;
			break;
		case TANK_DIREC_RIGHT:
			cmd.nDir =3;
			break;
		default:
			break;
		}
		cmdObj.push_back(cmd);


		//提交
		m_pDrawGame->EditDrawGameObj(cmdObj);
	}


	static int usersfresh;
	usersfresh++;
	if (usersfresh == 20)
	{
		GetAllUserInfo();
		usersfresh =0;
	}

	static int gamestart;
	gamestart++;
	if (gamestart == 50)
	{
		if (IsGameStart())		//如果游戏开始了 设置游戏开始标志
		{
			m_bgameIsStarted = TRUE;			
		}
		gamestart= 0;
		
	}
	




}



void CTankGame::Draw( int dt )
{

	//m_pDGameUI->m_pGameUIGraphic->DrawLine(600,0,600,600,5);


	//m_pDGameUI->m_pGameUIGraphic->DrawRect(300,300,200,200,RGB(255,255,0));

	m_pDrawGame->DrawGame();

	//m_pDGameUI->m_pGameUINet->
	

}

bool CTankGame::IsNetFree()
{
	return m_bNetFree;
}


bool CTankGame::Register( string& strUserName )		//注册用户
{
	if(!m_bConnected)
		return(false);
	int result,sqlResult;
	int OpNum = REGISTER_USER;
	int length = strUserName.length();
	m_bNetFree=false;
	m_pDGameUI->m_pGameUINet->Send( &OpNum, 4 );
	m_pDGameUI->m_pGameUINet->Send( &length, 4 );
	m_pDGameUI->m_pGameUINet->Send( strUserName.c_str(), length );
	m_pDGameUI->m_pGameUINet->Receive( &sqlResult, 4 );
	m_pDGameUI->m_pGameUINet->Receive( &result, 4 );
	m_bNetFree=true;

//	return (sqlResult ==TRUE);	//查询成功
	return sqlResult;
	//return( result == OK );

}

//得到用户信息
bool CTankGame:: GetAllUserInfo( )
{
	if(!m_bConnected)
		return(false);
	if(!m_bNetFree)
		return(false);
	int length;
	int OpNum = QUERY_USERS;
	m_bNetFree=false;
	m_pDGameUI->m_pGameUINet->Send( &OpNum, 4 );
	m_pDGameUI->m_pGameUINet->Receive( &length, 4 );
	//info = new CUserInfo[length/sizeof(CUserInfo)];
	//memset( info, 0, length );
	m_pDGameUI->m_pGameUINet->Receive( m_info, length );
	m_UserNum = length / sizeof(CTankGameUserInfo);
	m_bNetFree=true;
	return true;

}

//查询信息
bool CTankGame::QueryBoard()
{
	if(!m_bConnected)
		return(false);
	int length;
	char board[225];
	int OpNum=QUERY_BOARD;
	m_bNetFree=false;
	m_pDGameUI->m_pGameUINet->Send(&OpNum,4);
	m_pDGameUI->m_pGameUINet->Receive(&length,4);
	m_pDGameUI->m_pGameUINet->Receive(board,length);
	m_bNetFree=true;
	//drawer.SetBoard(board);
	return(true);
}

////处理鼠标单击
//bool CTankGame::MouseClick( int x, int y )
//{
//	if(!m_bConnected)
//		return(false);
//	int OpNum = USER_ACTION;
//	int result;
//	ACTION action;
//
//	action.Action = PLAY;
//	int length = sizeof(ACTION);
//	char info[225];			//存储棋盘信息
//
//	//判断棋子是否则在棋盘内
//	if( (x < 55 ) || ( x > 370 ) || ( y < 40 ) || ( y > 350 ) )
//		return false;
//	int col=(x-55)/21;
//	int row=(y-40)/21;
//	if( (row < 0) || (row > 14) || (col < 0) || (col > 14) )
//		return false;
//	action.ActionInfo=(col<<8)+row;
//	m_bNetFree=false;
//	Send( &OpNum, 4 );
//	Send( &length, 4 );
//	Send( &action, length );
//	Receive( &result, 4 );
//	Receive( &length, 4 );    //接收长度
//	Receive( info, length );
//	m_bNetFree=true;
//	drawer.SetBoard( info );	//更新棋盘信息
//
//
//	return (result==OK);
//
//}

//// 画棋盘
//bool CGameClient::Draw( CDC *pDC )	
//{
//	drawer.Draw( pDC );
//	return true;
//}

//进入游戏室
bool CTankGame::EnterRoom( int num )
{
	if(!m_bConnected)
		return(false);
	int OpNum = ENTER_ROOM;
	int result;
	m_bNetFree=false;
	m_pDGameUI->m_pGameUINet->Send( &OpNum, 4 );
	m_pDGameUI->m_pGameUINet->Send( &num, 4 );
	m_pDGameUI->m_pGameUINet->Receive( &result, 4 );
	m_bNetFree=true;
	if(result!=OK)
		return(false);
	return(true);

}

// 退出游戏室
bool CTankGame::ExitRoom()
{
	if(!m_bConnected)
		return(false);
	int OpNum = EXIT_ROOM;
	int result;
	m_bNetFree=false;
	m_pDGameUI->m_pGameUINet->Send( &OpNum, 4 );
	m_pDGameUI->m_pGameUINet->Receive( &result, 4 );
	m_bNetFree=true;
	return( result == OK );
}

//返回在线用户数
int CTankGame::GetUserCount()const
{
	return m_UserNum;
}

//返回在线用户信息
CTankGameUserInfo CTankGame::GetUserInfo( const int num )const
{
	return m_info[num];
}

//注销用户
bool CTankGame::Logout()
{
	if(!m_bConnected)
		return(false);
	int OpNum=LOGOUT;
	m_pDGameUI->m_pGameUINet->Send(&OpNum,4);
	return(true);
}

//退出游戏
bool CTankGame::ExitGame()
{
	if(!m_bConnected)
		return(false);
	int OpNum=EXIT_GAME;
	m_pDGameUI->m_pGameUINet->Send(&OpNum,4);
	return(true);
}

//发送移动坦克信息
bool CTankGame::MoveTank(int direc)
{
	if(!m_bConnected)
		return(false);
	int opNum=MOVE_TANK;
	int direcs = direc;
	int player1or2=m_gamePlayer1or2;
	int result;
	m_bNetFree=false;
	m_pDGameUI->m_pGameUINet->Send( &opNum, 4 );
	m_pDGameUI->m_pGameUINet->Send( &direcs, 4 );
	m_pDGameUI->m_pGameUINet->Send( &player1or2, 4 );

	m_pDGameUI->m_pGameUINet->Receive( &result, 4 );
	m_bNetFree=true;
	if(result!=OK)
		return(false);

	return(true);
}

	
bool CTankGame::GetTankPos()
{
	if(!m_bConnected)
		return(false);
	int length;
	char player1or2=m_gamePlayer1or2;
	int opNum=GET_TANK_POS;
	
	int result;
	m_bNetFree=false;
	m_pDGameUI->m_pGameUINet->Send( &opNum, 4 );
	//m_pDGameUI->m_pGameUINet->Send( &player1or2, 4 );

	m_pDGameUI->m_pGameUINet->Receive(&length,4);
	m_pDGameUI->m_pGameUINet->Receive( m_player1Pos, length );
	m_pDGameUI->m_pGameUINet->Receive( m_player2Pos, length );

	m_pDGameUI->m_pGameUINet->Receive( &result, 4 );
	m_bNetFree=true;
	if(result!=OK)
		return(false);

	return(true);
}



bool CTankGame::GetAllDatas()
{
	if(!m_bConnected)
		return(false);
	int length;
	int opNum=GET_ALL_DATA;
	int result;
	m_bNetFree=false;
	m_pDGameUI->m_pGameUINet->Send( &opNum, 4 );
	
	m_pDGameUI->m_pGameUINet->Receive(&length,4);
	m_pDGameUI->m_pGameUINet->Receive(&m_stuMapData, length );
	m_pDGameUI->m_pGameUINet->Receive( &result, 4 );
	m_bNetFree=true;
	if(result!=OK)
		return(false);

	return(true);
}


bool CTankGame::IsGameStart()
{
	if(!m_bConnected)
		return(false);
	int OpNum = IS_GAME_START;
	int result;
	m_bNetFree=false;
	m_pDGameUI->m_pGameUINet->Send( &OpNum, 4 );

	m_pDGameUI->m_pGameUINet->Receive( &result, 4 );
	m_bNetFree=true;
	return( result == OK );
}

