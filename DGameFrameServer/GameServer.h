

#ifndef __GAMESERVER__
#define __GAMESERVER__

#include "TCPServer.h"

class CGameServer: protected CTCPServer
{
private:
	

public:
	CGameServer(unsigned short nPortNum=5530);//ָ���˿ںŵĹ��캯��
	virtual bool IsOK() const;	//�жϷ������Ƿ�����
	virtual bool TurnOn();		//�򿪷�����
	virtual bool TurnOff();		//�رշ�����
	std::string GetServerIP();	//���ط�������IP��ַ
		
	//bool m_bIsInRoom;	//�Ƿ��ڷ��䵱��
	

};

#endif