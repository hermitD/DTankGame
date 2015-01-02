#pragma  once

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
//4020  4kb 貌似可以接受。。





typedef  enum { PLAY, RESTART, EXIT,MOVETANK} ACTIONTYPE;
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
const int YES=2;
const int NO=3;
const int YOUR_TURN=4;
const int YOU_WIN=5;
const int YOU_LOSE=6;
const int DO_YOU_AGREE_RESTART=7;
const int GAME_OVER=8;
const int I_KNOW=9;
const int I_WANT_TO_RESTART=10;
const int I_WANT_TO_EXIT=11;
const int AGREE=12;
const int DISAGREE=13;


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