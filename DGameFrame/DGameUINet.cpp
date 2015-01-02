#include "stdafx.h"
#include "DGameUINet.h"
using namespace std;

ULONG iTCPClient_ServerAddr=0;

CDGameUINet::CDGameUINet(unsigned short nPortNum)
{
	WSADATA data;
	WSAStartup(MAKEWORD(2,2),&data);
	Initialize(nPortNum);
}

CDGameUINet::~CDGameUINet()
{
	WSACleanup();
}

bool CDGameUINet::Initialize(unsigned short nPortNum)
{
	m_bConnected=false;
	m_nPortNum=nPortNum;
	m_ClientAddress.sin_family=AF_INET;
	m_ClientAddress.sin_port=htons(nPortNum);
	m_ClientAddress.sin_addr.s_addr=htonl(INADDR_ANY);
	m_sctClientSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	return(m_sctClientSocket!=INVALID_SOCKET);
}




bool CDGameUINet::IsOK() const
{
	return(m_bConnected);
}

bool CDGameUINet::Connect(string strServerAddress, unsigned short nServerPort)
{	int ret;
	int bReuse=true;
	if(m_bConnected)
		return(false);
	m_ServerAddress.sin_addr.s_addr=inet_addr(strServerAddress.c_str());
	m_ServerAddress.sin_family=AF_INET;
	m_ServerAddress.sin_port=htons(nServerPort);
	setsockopt(m_sctClientSocket,SOL_SOCKET,SO_REUSEADDR,(char *)&bReuse,sizeof(bReuse));
	if((ret=connect(m_sctClientSocket,(sockaddr*)&m_ServerAddress,sizeof(m_ServerAddress)))==SOCKET_ERROR)
	{	
		ret=WSAGetLastError();
		printf("Ê§°Ü£¡£¡%d",ret);
		return(false);
	}
	m_bConnected=true;

	printf("³É¹¦£¡£¡");
	return(true);
}

bool CDGameUINet::Disconnect()
{
	if(!m_bConnected)
		return(false);
	m_bConnected=false;
	closesocket(m_sctClientSocket);
	return(true);
}

bool CDGameUINet::Send(const void*  pDataToSend, unsigned int nLength)
{
	int ret;
	if(!m_bConnected)
	{
		return(false);
	}
	else
	{
		ret=send(m_sctClientSocket,(char*)pDataToSend,nLength,0);
		return(true);
	}

}

bool CDGameUINet::Receive(void*  pDataReceived, unsigned int nLength)
{
	if(!m_bConnected)
	{
		return(false);
	}
	else
	{
		recv(m_sctClientSocket,(char*)pDataReceived,nLength,0);
		return(true);
	}
}