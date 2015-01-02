#pragma once
#include "Bullet.h"
#include "Grass.h"
#include "HardWall.h"
#include "SoftWall.h"
#include "Tank.h"

//#include "TankWarView.h"

//#include "TankGame.h"




#include "DGameFrameDlg.h"

#include <vector>
using namespace std;


struct StuDrawObj
{
    int       nId;
    CDrawObj *pDrawObj;
};
enum stuCMD
{
    CREATE,
    DEL,
    MOVE,
    FIRE
};

enum stuType
{
    TANK,
    BULLET,
    GRASS,
    HARDWALL,
    SOFTWALL
};

struct stuCmdObj
{
    stuCMD cmd;
    stuType type;
    int nId;
    CRect rcXy;
    int nDir;
};

class CTankWarView;

class CDrawGame
{
public:
    CDrawGame(void);
    ~CDrawGame(void);

    void Init(CDGameFrameDlg *View);
    void DrawGame();
	void DrawGameInit();
    void EditDrawGameObj(const vector<stuCmdObj> &CmdObj);
	
    CDC m_cMem;
    CDC m_cBackGround;

    CDC m_cView;
    CDC m_cBullet;
    CDC m_cGrass;
    CDC m_cHardWall;
    CDC m_cSoftWall;
    CDC m_cTank;
    CDC m_cBoom;

    CBitmap m_bitBackGround;
    CBitmap m_bitMem;
    CBitmap m_bitView;
    CBitmap m_bitBullet;
    CBitmap m_bitGrass;
    CBitmap m_bitHardWall;
    CBitmap m_bitSoftWall;
    CBitmap m_bitTank;
    CBitmap m_bitBoom;

    vector<StuDrawObj> m_vBullet;
    vector<StuDrawObj> m_vGrass;
    vector<StuDrawObj> m_vHardWall;
    vector<StuDrawObj> m_vSoftWall;
    vector<StuDrawObj> m_vTank;

    BOOL m_isExit;

    CDGameFrameDlg *m_pView;
	
};

