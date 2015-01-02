// DGameFrameServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include "GameServer.h"

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned short port=5530;

	cout << "\n\n\t(\\~~/) (\\~*/) °"<<endl;//  (\~~/)(\~*/)@^
	cout <<		"\t(~'.'~)('.'~ )"<<endl;
	
	cout<<""<<endl<<endl;
	cout<<"Initializing......";

	CGameServer GameServer(port);
	if(GameServer.IsOK())
	{
		cout << "Successed :) " <<endl;
		cout<<"Server IP: "<<GameServer.GetServerIP().c_str()<<endl;
		cout<<"Port number: "<<port<<endl;
		cout<<"Server Turning on......";
		if(GameServer.TurnOn())
		{
			cout<<"OK."<<endl;
			cout<<"Press ENTER to turn off server......"<<endl;
			getchar();
			cout<<"Turning off......";
			cout<<(GameServer.TurnOff()?"OK.":"Failed.")<<endl;
		}
		else
			cout<<"Failed."<<endl;
	}
	else
		cout<<"Failed."<<endl;
	cout<<"Press ENTER to end"<<endl;
	getchar();
//	return(0);
	return 0;
}

