#include "stdafx.h"


#include"GameRoom.h"

bool CGameRoom::SetRoomNum(int RoomNum)//�趨��Ϸ�ұ��
{
	room_num=RoomNum;
    return(true);

}
int CGameRoom::GetRoomNum( )//������Ϸ�ұ�š� 
{
	return(room_num);
}

