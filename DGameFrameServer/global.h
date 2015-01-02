//	global file
//	declaration of user-defined types and defination of constants

#ifndef __GLOBAL__
#define __GLOBAL__


typedef struct //_pos
{
	int left;
	int top;
	int right;
	int bottom;
}pos;
typedef struct //_mapData
{
	int bulletNum;
	pos bullet[50];
	int grassNum;
	pos grass[50];
	int hardWallNum;
	pos hardWall[50];
	int softWallNum;
	pos softWall[50];
	int tankNum;
	pos tank[50];

}mapData;


typedef  enum { PLAY, RESTART, EXIT ,MOVETANK} ACTIONTYPE;


typedef  struct {	
					unsigned int UserID; 
					ACTIONTYPE  Action; 
					unsigned int  ActionInfo;
				} ACTION;
typedef  struct { 
					bool GameEnd;  
					unsigned int NextPlayerID;
				} GAMERESULT;



// communication language between server and client
const int OK=0;
const int FAILED=1;

const int QUERY_USERS=100;
const int ENTER_ROOM=101;
const int EXIT_ROOM=102;
const int USER_ACTION=103;
const int REGISTER_USER=104;
const int QUERY_BOARD=105;
const int LOGOUT=106;
const int EXIT_GAME=107;
const int GET_TANK_POS=108;
const int IS_GAME_START=109;
const int GET_ALL_DATA=110;

const int MOVE_TANK = 200;


const int TANK_DIREC_TOP=30;
const int TANK_DIREC_DOWN=31;
const int TANK_DIREC_LEFT=32;
const int TANK_DIREC_RIGHT=33;
#endif
									