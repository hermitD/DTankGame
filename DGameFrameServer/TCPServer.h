

#ifndef __TCPSERVER__
#define __TCPSERVER__

#include <winsock2.h>
#include <string>
#include "Server.h"
#pragma comment( lib, "wsock32.lib" )

//used to be class CTCPServer: public CServer
class CTCPServer
{
private:
	unsigned short m_nPortNum;	//端口号
	bool m_bInitSuccess;		//初始化成功标志
	sockaddr_in m_ServerAddress;//服务器地址
	SOCKET m_sctListenSocket;	//侦听套接字

	//bool m_bClientIsWork;		//具体某一客户端是否工作(是否应该退出这个工作线程)
								//放弃此方案,逻辑上不合理。
	

	

	bool Initialize(USHORT iPortNum);	//初始化

public:
	virtual bool IsOK() const;	//是否能正常工作
	virtual bool TurnOn();		//打开服务器
	virtual bool TurnOff();		//关闭服务器

	//设置接待函数，当服务器收到客户机的数据是，会自动调用接待函数
	bool  SetReceptionist(bool (*pFunc)(SOCKET sct));

	//返回服务器的IP地址
	std::string GetIPAddr() const;

	//指定端口号的构造函数，默认端口号为5530
	CTCPServer(unsigned short nPortNum=5530);

	~CTCPServer();
};

#endif