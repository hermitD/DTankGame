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
	//���ӵ�������
	virtual bool Connect(std::string strServerAddress, unsigned short nServerPort=5530);
	//�Ͽ��������������
	virtual bool Disconnect();
	//��������
	virtual bool Send(const void*  pDataToSend, unsigned int nLength);
	//��������
	virtual bool Receive(void*  pDataReceived, unsigned int nLeng);
};
