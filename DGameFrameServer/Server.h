
#ifndef __CSERVER__
#define __CSERVER__

#include "NetAgent.h"

class CServer:public CNetAgent
{
protected:
	
public:
	virtual bool TurnOn()=0;	//�򿪷�����
	virtual bool TurnOff()=0;	//�رշ�����
	
};

#endif
