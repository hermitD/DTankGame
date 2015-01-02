

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
	unsigned short m_nPortNum;	//�˿ں�
	bool m_bInitSuccess;		//��ʼ���ɹ���־
	sockaddr_in m_ServerAddress;//��������ַ
	SOCKET m_sctListenSocket;	//�����׽���

	//bool m_bClientIsWork;		//����ĳһ�ͻ����Ƿ���(�Ƿ�Ӧ���˳���������߳�)
								//�����˷���,�߼��ϲ�����
	

	

	bool Initialize(USHORT iPortNum);	//��ʼ��

public:
	virtual bool IsOK() const;	//�Ƿ�����������
	virtual bool TurnOn();		//�򿪷�����
	virtual bool TurnOff();		//�رշ�����

	//���ýӴ����������������յ��ͻ����������ǣ����Զ����ýӴ�����
	bool  SetReceptionist(bool (*pFunc)(SOCKET sct));

	//���ط�������IP��ַ
	std::string GetIPAddr() const;

	//ָ���˿ںŵĹ��캯����Ĭ�϶˿ں�Ϊ5530
	CTCPServer(unsigned short nPortNum=5530);

	~CTCPServer();
};

#endif