#pragma once
#include <winsock2.h>
#include <string>

class CDGameUINet
{
protected:
	unsigned short m_nPortNum;
	sockaddr_in m_ClientAddress;
	sockaddr_in m_ServerAddress;
	SOCKET m_sctClientSocket;
	bool m_bConnected;

	bool Initialize(unsigned short nPortNum = 5530);

public:
	CDGameUINet(unsigned short nPortNum=5530);
	~CDGameUINet();

	virtual bool IsOK() const;
	//连接到服务器
	virtual bool Connect(std::string strServerAddress, unsigned short nServerPort=5530);
	//断开与服务器的连接
	virtual bool Disconnect();
	//发送数据
	virtual bool Send(const void*  pDataToSend, unsigned int nLength);
	//接收数据
	virtual bool Receive(void*  pDataReceived, unsigned int nLeng);
};
