#include "stdafx.h"
#include <cstring>


#include"TankGameRoom.h"

CTankGameRoom::CTankGameRoom()
{
	num_user=0;
	succ=false;
	user_black=user_white=nextplayer_id=winner_id=0;
	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
			board[i][j]=0;

	for (int i = 0; i < 9; i++)
	{
		player1Pos[i] = 0;
		player2Pos[i] = 0;
	}
	gamestart = false;
	//结构体请0操作
	memset(&strMapdata,0,sizeof(strMapdata));

}
bool CTankGameRoom::success(int row,int column)
{
	int consist=1;
	char value=board[row][column];

	////////to compare in the same row
	for(int left=1;left<5;left++)
	{
		if((column-left)>=0)
		{
			if(board[row][column-left]==value)
           		consist++;
			else break;
		}
		else break;
	}
	
	for(int right=1;right<5;right++)
	{
		if((column+right)<=14)
		{
			if(board[row][column+right]==value)
			{
				consist++;
				if(consist==5)
					return(true);
			}
			else break;
		}
		else break;
	}
	if(consist==5)
		return(true);
	
/////////to compare in the same column
	consist=1;
    for(int up=1;up<5;up++)
	{
		if((row-up)>=0)
		{
			if(board[row-up][column]==value)
           		consist++;
			else break;
		}
		else break;
	}
	
	for(int down=1;down<5;down++)
	{
		if((row+down)<=14)
		{
			if(board[row+down][column]==value)
			{
				consist++;
				if(consist==5)
					return(true);
			}
			else break;
		}
		else break;
	}
	if(consist==5)
		return(true);
 ////////////在反斜对角线上比较 
    consist=1;
    for(int up=1,left=1;up<5;up++,left++)
	{
		if( row-up>=0 && column-left>=0)
		{
			if(board[row-up][column-left]==value)
           		consist++;
			else break;
		}
		else break;
	}
	
	for(int down=1,right=1;down<5;down++,right++)
	{
		if(row+down<=14 && column+right<=14)
		{
			if(board[row+down][column+right]==value)
			{
				consist++;
				if(consist==5)
					return(true);
			}
			else break;
		}
		else break;
	}
	if(consist==5)
		return(true);
////////////在顺斜对角线上比较
    consist=1;
    for(int up=1,right=1;up<5;up++,right++)
	{
		if(row-up>=0 && column+right<=14)
		{
			if(board[row-up][column+right]==value)
           		consist++;
			else break;
		}
		else break;
	}
	for(int down=1,left=1;down<5;down++,left++)
	{
		if(row+down<=14 && column-left>=0)
		{
			if(board[row+down][column-left]==value)
			{
				consist++;
				if(consist==5)
					return(true);
			}
			else break;
		}
		else break;
	}
	if(consist==5)
		return(true);


	//if the situation is not successful
	return(false);
}

unsigned int CTankGameRoom::GetCoplayerID(unsigned int UserID)
{
	if(user_black==UserID)
		return(user_white);
	else 
		return(user_black);
}
bool CTankGameRoom::AddUser(unsigned int UserID)  //to add a user 
{
	if(num_user>=2)
		return(false);
	
	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
			board[i][j]=0;
	switch(++num_user)
	{
	case 1:					//第一个用户 作为黑方
		{
			user_black=UserID;
			user_white=0;
			nextplayer_id=0;
            return(true);
		}
	case 2:					//第二个用户 作为白方
		{
			if(user_black==0)		//如果黑方还等于0 黑方就是白方
				user_black=user_white;

			user_white=UserID;
			nextplayer_id=user_black;
			return(true);
		}
	default: 
		return(false);
    }
	
}
bool CTankGameRoom::DeleteUser(unsigned int UserID) //to delete a user
{
	switch(num_user)
	{
	case 2:
		{
			num_user--;
			nextplayer_id=winner_id=0;
			if(user_black==UserID)
			{
				user_black=0;
				return(true);
			}
			if(user_white==UserID)
			{
				user_white=0;
				return(true);
			}
			return(false);
		}
	case 1:
		{
			num_user--;
			user_black=user_white=0;
			nextplayer_id=winner_id=0;
			return(true);
		}
	default: return(false);  // there is no user in the room
	}

}
 
bool CTankGameRoom::IsReady( )      // if it is can start the game
{

	if(num_user==2)
	{
		// to initial the board of the game 
	//	for(int i=0;i<15;i++)
	//		for(int j=0;j<15;j++)
	//			board[i][j]|=0x00;  
    //  0x00 stands for the empty space.
    //  when it has begun,0x01 for the black gobang,
    //	0x02 for the white gobang.
		
		//初始化信息
		//200,100,264,164
		player1Pos[0]=2;
		player1Pos[1]=0;
		player1Pos[2]=1;
		player1Pos[3]=0;
		player1Pos[4]=2;
		player1Pos[5]=64;
		player1Pos[6]=1;
		player1Pos[7]=64;
		player1Pos[8]=TANK_DIREC_TOP;

		//900,100,964,164
		player2Pos[0]=9;
		player2Pos[1]=0;
		player2Pos[2]=1;
		player2Pos[3]=0;
		player2Pos[4]=9;
		player2Pos[5]=64;
		player2Pos[6]=1;
		player2Pos[7]=64;
		player2Pos[8]=TANK_DIREC_TOP;
		gamestart =true;
		return(true);
	}
    //finish
	else return(false);
}
bool CTankGameRoom::Restart()         //  to restart the game
{
	// to initial the board of the game 
	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
			board[i][j]=0;  
    //  0x00 stands for the empty space.
    //  when it has begun,0x01 for the black gobang,
    //	0x02 for the white gobang.
    unsigned int temp;
	temp=user_black;
	user_black=user_white;
	user_white=temp;
	nextplayer_id=user_black;
	winner_id=0;
	return(true);
}
bool CTankGameRoom::IsUserIn(unsigned int UserID)  //this user is in the game
{
	if((user_black==UserID)||(user_white==UserID))
		return(true);
	else 
		return(false);
  
}
GAMERESULT CTankGameRoom::UserPlay(ACTION  action)
{   
	char row_info,column_info; 
	int row,column;
	GAMERESULT result;
	switch(action.Action)
	{
	case MOVETANK:
		{
			int direc = action.ActionInfo;
			//


			break;
		}




//  one user plays a piece of his gabang.
	case PLAY:
		{
			column_info=(action.ActionInfo>>8)&0xff;   //x 
            row_info=action.ActionInfo&0xff;           //y
		    column=column_info;
            row=row_info;
			if(board[row][column]!=0)
			{
				result.GameEnd=false;
				result.NextPlayerID=nextplayer_id;
				return(result);
			}
			if(nextplayer_id!=action.UserID)
			{
				result.GameEnd=false;
				result.NextPlayerID=nextplayer_id;
				return(result);
			}
			if(nextplayer_id==user_black)
				nextplayer_id=user_white;
			else 
				nextplayer_id=user_black;
		
			if(action.UserID==user_black)	
			{
				board[row][column]=0x01;
			}
			else
			{
				board[row][column]=0x02;
			}
			if(success(row,column))
			{
				succ=true;
				winner_id=action.UserID;
				result.GameEnd=true;
			}
			else 
			{
				result.GameEnd=false;
			}
			result.NextPlayerID=nextplayer_id;
			return result;
		}

//to restart the game;it will exchange the colors of users' gabang. 
	case RESTART:
		{
			Restart();
			nextplayer_id=user_black;
			result.GameEnd=false;
			result.NextPlayerID=user_black;
			return result;
		}
// to exit the GameRoom
/*********************************************************
		it need to modify    : if there is no user ,the room will vanish
		and then I shuold use the function Delete(),what is the return,and 
		*/
	case EXIT:
		{
			
		   switch(num_user)
		   {
		   case 2:
			   {
				   num_user--;
				   if(user_black==action.UserID)
				  	   user_black=user_white;
				   result.GameEnd=true;
				   result.NextPlayerID=user_black;
			   }
		   case 1:
			   {
				   num_user--;
				   result.GameEnd=true;
				   result.NextPlayerID=0;
			   }
		   } 
		   
          return result;
		}
	default:
		{
			result.GameEnd=false;
			result.NextPlayerID=action.UserID;
			return result;
		}
	}
    
}                
const char* CTankGameRoom::GetGameInfo()
{
	return(&board[0][0]);
}
unsigned int CTankGameRoom::GetWinnerID()
{
	if(succ==true)
		return(winner_id);
	else 
		return(0);
}
unsigned int CTankGameRoom::GetNextPlayerID()
{
	return(nextplayer_id);
}

//void CTankGameRoom::ConvertboardToPos()
//{
//	//board[0][0]~[3] player1; black
//	//board[1][0]~[3] player2; white
//	player1Pos[0]=board[0][0]*10;
//	player1Pos[1]=board[0][1]*10;
//	player1Pos[2]=board[0][2]*10;
//	player1Pos[3]=board[0][3]*10;
//
//	player2Pos[0]=board[1][0]*10;
//	player2Pos[1]=board[1][1]*10;
//	player2Pos[2]=board[1][2]*10;
//	player2Pos[3]=board[1][3]*10;
//
//}