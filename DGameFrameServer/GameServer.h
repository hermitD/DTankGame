

#ifndef __GAMESERVER__
#define __GAMESERVER__

#include "TCPServer.h"

class CGameServer: protected CTCPServer
{
private:
	

public:
	CGameServer(unsigned short nPortNum=5530);//指定端口号的构造函数
	virtual bool IsOK() const;	//判断服务器是否正常
	virtual bool TurnOn();		//打开服务器
	virtual bool TurnOff();		//关闭服务器
	std::string GetServerIP();	//返回服务器的IP地址
		
	//bool m_bIsInRoom;	//是否在房间当中
	

};

#endif