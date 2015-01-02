
#include "stdafx.h"
#include <string>
#include "TCPServer.h"

using namespace std;

const int g_nBufSize=10240;	// buffer size = 10 KB

bool g_bStopWorking;	//停止工作的标志
bool g_bTurnOn;			//服务器已打开的标志
bool  (*g_pReceptionist)(SOCKET sct);	//相应客户端请求的函数的指针
DWORD WINAPI g_AcceptClient(LPVOID lpParam);	//接收客户端连接的函数
DWORD WINAPI g_ProcessClientRequest(LPVOID lpParam);	//响应客户端请求的函数


bool CTCPServer::Initialize(unsigned short nPortNum)
{
	g_bStopWorking=false;
	g_bTurnOn=false;
	//m_bClientIsWork=false;

	g_pReceptionist=NULL;

	m_nPortNum=nPortNum;
	m_ServerAddress.sin_family=AF_INET;
	m_ServerAddress.sin_port=htons(nPortNum);
	m_ServerAddress.sin_addr.s_addr=htonl(INADDR_ANY);

	  // 2. 创建服务端的socket
	//建立套接字
	if((m_sctListenSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_IP))==INVALID_SOCKET)
		return(false);
	//绑定套接字
	if(bind(m_sctListenSocket,(sockaddr*)&m_ServerAddress,sizeof(m_ServerAddress))==SOCKET_ERROR)
		return(false);

	
	//将端口设为非阻塞模式  -- 会有问题。 应该是无阻塞导致一直收,最终导致了这里new的失败
	// 5. 连接socket
	//pConnectSocket=new SOCKET  --> malloc error 

	/*DWORD nonBlocking = 1;
	if ( ioctlsocket( m_sctListenSocket, FIONBIO, &nonBlocking ) != 0 )
	{
		printf( "failed to set non-blocking socket/n" );
		return false;
	}*/

	//侦听
	listen(m_sctListenSocket,SOMAXCONN);
	return(true);
}

CTCPServer::CTCPServer(unsigned short nPortNum)
{
	m_bInitSuccess=false;
	 // 1. 初始化socket库
	WSADATA data;
	if(WSAStartup(MAKEWORD(2,2),&data)!=0)
		return;
	if(!Initialize(nPortNum))
		return;
	DWORD dwThreadID;
	
	//建立接收客户端连接的线程
	
	if(CreateThread(NULL,0,g_AcceptClient,(LPVOID)m_sctListenSocket,0,&dwThreadID)==NULL)
		return;
	m_bInitSuccess=true;
	return;
}

CTCPServer::~CTCPServer()
{
	g_bStopWorking=true;
	WSACleanup();
}


bool CTCPServer::SetReceptionist(bool (*pFunc)(SOCKET sct))
{
	g_pReceptionist=pFunc;
	return(true);
}


bool CTCPServer::IsOK() const
{
	return(m_bInitSuccess&&(g_pReceptionist!=NULL));
}

string CTCPServer::GetIPAddr() const
{
	char szHostName[128];
	struct hostent * pHost;
	int i; 

	if(gethostname(szHostName,128)==0)
	{
		pHost = gethostbyname(szHostName);
		for(i=0; (pHost!= NULL) && (pHost->h_addr_list[i]!= NULL); i++ )
		{
			return(string(inet_ntoa (*(struct in_addr *)pHost->h_addr_list[i])));
		}
	}
	return(string(""));
}

bool CTCPServer::TurnOn()
{
	g_bTurnOn=true;
	return(true);
}

bool CTCPServer::TurnOff()
{
	g_bTurnOn=false;
	return(true);
}
//这个线程应该是一直开着的 
DWORD WINAPI g_AcceptClient(LPVOID lpParam)
{
	SOCKET sctListenSocket=(SOCKET)lpParam;
	SOCKET *pConnectSocket;
	sockaddr_in ClientAddress;
	int iAddressSize=sizeof(ClientAddress);
	int bReuse=true;
	DWORD dwThreadID;
	while(!g_bStopWorking)
	{	
		if(!g_bTurnOn)
			continue;
		 // 5. 连接socket
		pConnectSocket=new SOCKET;
											//该参数返回请求连接主机的地址 //该参数返回 SOCKADDR_IN 结构的长度
		*pConnectSocket=accept(sctListenSocket,(sockaddr*)&ClientAddress,&iAddressSize);
		setsockopt(*pConnectSocket,SOL_SOCKET,SO_REUSEADDR,(char *)&bReuse,sizeof(bReuse));
		
		//基本上就是来一个建一个线程
		 // 6. 创建接受数据线程
		if(*pConnectSocket!=INVALID_SOCKET)
			CreateThread(NULL,0,g_ProcessClientRequest,(LPVOID)*pConnectSocket,0,&dwThreadID);
	}
	return(0);
}

DWORD WINAPI g_ProcessClientRequest(LPVOID lpParam)
{
	SOCKET sctClientSocket=(SOCKET)lpParam;
	//大约在这里不能用这个stopworking了不然会死循环。且没出口 
	//已修正不用这个标志做这个功能用下面的相应函数返回值来实现退出线程防死循环
	while(!g_bStopWorking)
	{
		if(!g_bTurnOn)	//服务器未打开
			continue;
		if(g_pReceptionist==NULL)	//未设置接待函数
			continue;
		if(!g_pReceptionist(sctClientSocket))	//如果返回为否则不再响应客户端请求
			return 0;
			//break
	}
	return(0);
}

