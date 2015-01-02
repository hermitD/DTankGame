#include "stdafx.h"


#include"GameRoom.h"

bool CGameRoom::SetRoomNum(int RoomNum)//设定游戏室编号
{
	room_num=RoomNum;
    return(true);

}
int CGameRoom::GetRoomNum( )//返回游戏室编号。 
{
	return(room_num);
}

