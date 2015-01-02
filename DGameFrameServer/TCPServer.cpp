
#include "stdafx.h"
#include <string>
#include "TCPServer.h"

using namespace std;

const int g_nBufSize=10240;	// buffer size = 10 KB

bool g_bStopWorking;	//ֹͣ�����ı�־
bool g_bTurnOn;			//�������Ѵ򿪵ı�־
bool  (*g_pReceptionist)(SOCKET sct);	//��Ӧ�ͻ�������ĺ�����ָ��
DWORD WINAPI g_AcceptClient(LPVOID lpParam);	//���տͻ������ӵĺ���
DWORD WINAPI g_ProcessClientRequest(LPVOID lpParam);	//��Ӧ�ͻ�������ĺ���


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

	  // 2. ��������˵�socket
	//�����׽���
	if((m_sctListenSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_IP))==INVALID_SOCKET)
		return(false);
	//���׽���
	if(bind(m_sctListenSocket,(sockaddr*)&m_ServerAddress,sizeof(m_ServerAddress))==SOCKET_ERROR)
		return(false);

	
	//���˿���Ϊ������ģʽ  -- �������⡣ Ӧ��������������һֱ��,���յ���������new��ʧ��
	// 5. ����socket
	//pConnectSocket=new SOCKET  --> malloc error 

	/*DWORD nonBlocking = 1;
	if ( ioctlsocket( m_sctListenSocket, FIONBIO, &nonBlocking ) != 0 )
	{
		printf( "failed to set non-blocking socket/n" );
		return false;
	}*/

	//����
	listen(m_sctListenSocket,SOMAXCONN);
	return(true);
}

CTCPServer::CTCPServer(unsigned short nPortNum)
{
	m_bInitSuccess=false;
	 // 1. ��ʼ��socket��
	WSADATA data;
	if(WSAStartup(MAKEWORD(2,2),&data)!=0)
		return;
	if(!Initialize(nPortNum))
		return;
	DWORD dwThreadID;
	
	//�������տͻ������ӵ��߳�
	
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
//����߳�Ӧ����һֱ���ŵ� 
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
		 // 5. ����socket
		pConnectSocket=new SOCKET;
											//�ò��������������������ĵ�ַ //�ò������� SOCKADDR_IN �ṹ�ĳ���
		*pConnectSocket=accept(sctListenSocket,(sockaddr*)&ClientAddress,&iAddressSize);
		setsockopt(*pConnectSocket,SOL_SOCKET,SO_REUSEADDR,(char *)&bReuse,sizeof(bReuse));
		
		//�����Ͼ�����һ����һ���߳�
		 // 6. �������������߳�
		if(*pConnectSocket!=INVALID_SOCKET)
			CreateThread(NULL,0,g_ProcessClientRequest,(LPVOID)*pConnectSocket,0,&dwThreadID);
	}
	return(0);
}

DWORD WINAPI g_ProcessClientRequest(LPVOID lpParam)
{
	SOCKET sctClientSocket=(SOCKET)lpParam;
	//��Լ�����ﲻ�������stopworking�˲�Ȼ����ѭ������û���� 
	//���������������־������������������Ӧ��������ֵ��ʵ���˳��̷߳���ѭ��
	while(!g_bStopWorking)
	{
		if(!g_bTurnOn)	//������δ��
			continue;
		if(g_pReceptionist==NULL)	//δ���ýӴ�����
			continue;
		if(!g_pReceptionist(sctClientSocket))	//�������Ϊ��������Ӧ�ͻ�������
			return 0;
			//break
	}
	return(0);
}

