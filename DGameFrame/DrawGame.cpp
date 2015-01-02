#include "stdafx.h"
#include "DrawGame.h"
#include "resource.h"

CDrawGame::CDrawGame(void)
{
    m_isExit = FALSE;
}


CDrawGame::~CDrawGame(void)
{
    m_cBullet.DeleteDC();
    m_cGrass.DeleteDC();
    m_cHardWall.DeleteDC();
    m_cSoftWall.DeleteDC();
    m_cTank.DeleteDC();
    m_cBoom.DeleteDC();

    unsigned long i = 0;
    unsigned long nCount = m_vTank.size();
    for (i=0; i<nCount; i++)
    {
		
        delete m_vTank[i].pDrawObj;
    }

    nCount = m_vBullet.size();
    for (i=0; i<nCount; i++)
    {
        delete m_vBullet[i].pDrawObj;
    }

    nCount = m_vHardWall.size();
    for (i=0; i<nCount; i++)
    {
        delete m_vHardWall[i].pDrawObj;
    }

    nCount = m_vSoftWall.size();
    for (i=0; i<nCount; i++)
    {
        delete m_vSoftWall[i].pDrawObj; 
    }

    nCount = m_vGrass.size();
    for (i=0; i<nCount; i++)
    {
        delete m_vGrass[i].pDrawObj;
    }
}

void CDrawGame::Init(CDGameFrameDlg *View)
{
    //m_cView.Attach(GetDC(View->m_hWnd));
	//m_cView.Attach(GetDC(View->m_hWnd));//CDGameFrameDlg


	//m_pcView = View->m_pDGameUI->m_pGameUIGraphic->m_pMemDC;

	//m_cView = *(View->GetDC());
	m_cView.Attach(GetDC(View->m_hWnd));

  /*  m_bitView.CreateCompatibleBitmap(&m_cView,650,650);
    m_cView.SelectObject(m_bitView);*/

    m_cMem.CreateCompatibleDC(&m_cView);
    m_bitMem.CreateCompatibleBitmap(&m_cView,1200,1200);
    m_cMem.SelectObject(m_bitMem);


    m_cBackGround.CreateCompatibleDC(NULL);
    m_cBullet.CreateCompatibleDC(NULL);
    m_cGrass.CreateCompatibleDC(NULL);
    m_cHardWall.CreateCompatibleDC(NULL);
    m_cSoftWall.CreateCompatibleDC(NULL);
    m_cTank.CreateCompatibleDC(NULL);
    m_cBoom.CreateCompatibleDC(NULL);


	//m_cView.Attach(GetDC(View->m_hWnd));
	//m_bitView.CreateCompatibleBitmap(&m_cView,683,683);
	//m_cView.SelectObject(m_bitView);

	//m_cMem.CreateCompatibleDC(&m_cView);
	//m_bitMem.CreateCompatibleBitmap(&m_cView,1200,1200);
	//m_cMem.SelectObject(m_bitMem);

	//m_cBackGround.CreateCompatibleDC(&m_cView);
	//m_cBullet.CreateCompatibleDC(&m_cView);
	//m_cGrass.CreateCompatibleDC(&m_cView);
	//m_cHardWall.CreateCompatibleDC(&m_cView);
	//m_cSoftWall.CreateCompatibleDC(&m_cView);
	//m_cTank.CreateCompatibleDC(&m_cView);
	//m_cBoom.CreateCompatibleDC(&m_cView);


    m_bitBackGround.LoadBitmap(BITMAP_BACKGROUND);
    m_bitBullet.LoadBitmap(BITMAP_BULLET);
    m_bitGrass.LoadBitmap(BITMAP_WALL);
    m_bitHardWall.LoadBitmap(BITMAP_WALL);
    m_bitSoftWall.LoadBitmap(BITMAP_WALL);
    m_bitTank.LoadBitmap(BITMAP_TANK);
    m_bitBoom.LoadBitmap(BITMAP_FIRE);

    m_cBackGround.SelectObject(m_bitBackGround);
    m_cBullet.SelectObject(m_bitBullet);
    m_cGrass.SelectObject(m_bitGrass);
    m_cHardWall.SelectObject(m_bitHardWall);
    m_cSoftWall.SelectObject(m_bitSoftWall);
    m_cTank.SelectObject(m_bitTank);
    m_cBoom.SelectObject(m_bitBoom);

    CDrawObj::m_pscBullet = &m_cBullet;
    CDrawObj::m_pscGrass = &m_cGrass;
    CDrawObj::m_pscHardWall = &m_cHardWall;
    CDrawObj::m_pscSoftWall = &m_cSoftWall;
    CDrawObj::m_pscMem = &m_cMem;
    CDrawObj::m_pscTank = &m_cTank;
    CDrawObj::m_pscBoom = &m_cBoom;

    //m_pView = View;
}

void CDrawGame::DrawGameInit()
{
	StuDrawObj obj;
	//obj.nId = 1;
	//obj.pDrawObj = new CHardWall;
	//obj.pDrawObj->m_rcXy = CRect(64,64,128,128); 	//64 64
	//m_vHardWall.push_back(obj);

	//obj.nId = 2;
	//obj.pDrawObj = new CHardWall;
	//obj.pDrawObj->m_rcXy = CRect(180,180,244,244); //64 64
	//m_vHardWall.push_back(obj);

	obj.nId = 1;
	obj.pDrawObj = new CHardWall;
	obj.pDrawObj->m_rcXy = CRect(1136,64,1200,128); 	//64 64
	m_vHardWall.push_back(obj);

	
	obj.nId = 1;
	obj.pDrawObj = new CTank;
	obj.pDrawObj->m_rcXy = obj.pDrawObj->m_oldrcXy = CRect(200,100,264,164); // 64 64
	m_vTank.push_back(obj);

	obj.nId = 2;
	obj.pDrawObj = new CTank;
	obj.pDrawObj->m_rcXy = obj.pDrawObj->m_oldrcXy = CRect(900,100,964,164); // 64 64
	m_vTank.push_back(obj);

	obj.nId = 1;
	obj.pDrawObj = new CBullet;
	obj.pDrawObj->m_rcXy = CRect(580,100,620,140);//40,40
	m_vBullet.push_back(obj);

	obj.nId = 1;
	obj.pDrawObj = new CBullet;
	obj.pDrawObj->m_rcXy = CRect(1180,100,1220,140);//40,40
	m_vBullet.push_back(obj);

//	delete obj.pDrawObj;

	//obj.nId = 1;
	//obj.pDrawObj = new CTank;
	//obj.pDrawObj->m_rcXy = obj.pDrawObj->m_oldrcXy = CRect(400,300,464,364); // 64 64
	//m_vTank.push_back(obj);


	//obj.nId = 1;
	//obj.pDrawObj = new CBullet;
	//obj.pDrawObj->m_rcXy = CRect(280,100,320,140);//40,40
	//m_vBullet.push_back(obj);

	//obj.nId = 2;
	//obj.pDrawObj = new CSoftWall;
	//obj.pDrawObj->m_rcXy = CRect(64,0,128,64);
	//m_vBullet.push_back(obj);
}
void CDrawGame::DrawGame()
{
    unsigned long nCount = 0;
    unsigned long i = 0;


    


    //while (TRUE)
    //{
    //    if (m_isExit)
    //    {
    //        break;
    //    }

    //    Sleep(10);
        m_cMem.BitBlt(0,0,1200,1200,&m_cBackGround,0,0,SRCCOPY);

        nCount = m_vTank.size();
        for (i=0; i<nCount; i++)
        {
            m_vTank[i].pDrawObj->Draw();
        }

        nCount = m_vBullet.size();
        for (i=0; i<nCount; i++)
        {
            m_vBullet[i].pDrawObj->Draw();
        }

        nCount = m_vHardWall.size();
        for (i=0; i<nCount; i++)
        {
            m_vHardWall[i].pDrawObj->Draw();
        }

        nCount = m_vSoftWall.size();
        for (i=0; i<nCount; i++)
        {
            m_vSoftWall[i].pDrawObj->Draw(); 
        }

        nCount = m_vGrass.size();
        for (i=0; i<nCount; i++)
        {
            m_vGrass[i].pDrawObj->Draw();
        }

        //m_cView.BitBlt(0,0,m_nViewW,m_nViewV,&m_cMem,0,0,SRCCOPY);
        SetStretchBltMode((m_cView),STRETCH_HALFTONE);
        (m_cView).StretchBlt(0,0,650,650,&m_cMem,0,0,1200,1200,SRCCOPY);
   /* }*/
}

void CDrawGame::EditDrawGameObj(const vector<stuCmdObj> &CmdObj)
{
    unsigned long i = 0;
    unsigned long j = 0;
    StuDrawObj DrawObj;
    for (i=0; i<CmdObj.size(); i++)
    {
        if (MOVE == CmdObj[i].cmd)
        {
            if (TANK == CmdObj[i].type)
            {
                for (j=0; j<m_vTank.size(); j++)
                {
                    if (CmdObj[i].nId == m_vTank[j].nId)
                    {
                        m_vTank[j].pDrawObj->Move(CmdObj[i].rcXy,CmdObj[i].nDir);
                    }
                }
            }
            else if (BULLET == CmdObj[i].type)
            {
                for (j=0; j<m_vBullet.size(); j++)
                {
                    if (CmdObj[i].nId == m_vBullet[j].nId)
                    {
                       // m_vBullet[j].pDrawObj->Move();
                    }
                }
            }
        }
        else if (FIRE == CmdObj[i].cmd)
        {
            if (TANK == CmdObj[i].type)
            {
                for (j=0; j<m_vTank.size(); j++)
                {
                    if (CmdObj[i].nId == m_vTank[j].nId)
                    {
                        ((CTank*)m_vTank[j].pDrawObj)->Fire();
                    }
                }
            }
        }
        else if (CREATE == CmdObj[i].cmd)
        {              
            DrawObj.nId = CmdObj[i].nId;

            switch (CmdObj[i].type)
            {
            case TANK:
                DrawObj.pDrawObj =  new CTank();
                break;
            case BULLET:
                DrawObj.pDrawObj =  new CBullet();
                break;
            case GRASS:
                DrawObj.pDrawObj =  new CGrass();
                break;
            case HARDWALL:
                DrawObj.pDrawObj =  new CHardWall();
                break;
            case SOFTWALL:
                DrawObj.pDrawObj =  new CSoftWall();
                break;
            default:
                MessageBox(0,0,_T("创建对象时错误"),0);
                break;
            }

            m_vTank.push_back( DrawObj );
        }
        else if (DEL == CmdObj[i].cmd)
        {
            switch (CmdObj[i].type)
            {
            case TANK:
                for (j=0; j<m_vTank.size(); j++)
                {
                    if (CmdObj[i].nId == m_vTank[j].nId)
                    {
                        delete m_vTank[j].pDrawObj;
                        m_vTank.erase(m_vTank.begin()+j);
                        break;
                    }
                }
                break;
            case BULLET:
                for (j=0; j<m_vBullet.size(); j++)
                {
                    if (CmdObj[i].nId == m_vBullet[j].nId)
                    {
                        delete m_vBullet[j].pDrawObj;
                        m_vBullet.erase(m_vBullet.begin()+j);
                        break;
                    }
                }
                break;
            case GRASS:
                for (j=0; j<m_vGrass.size(); j++)
                {
                    if (CmdObj[i].nId == m_vGrass[j].nId)
                    {
                        delete m_vGrass[j].pDrawObj;
                        m_vGrass.erase(m_vGrass.begin()+j);
                        break;
                    }
                }
                break;
            case HARDWALL:
                for (j=0; j<m_vHardWall.size(); j++)
                {
                    if (CmdObj[i].nId == m_vHardWall[j].nId)
                    {
                        delete m_vHardWall[j].pDrawObj;
                        m_vHardWall.erase(m_vHardWall.begin()+j);
                        break;
                    }
                }
                break;
            case SOFTWALL:
                for (j=0; j<m_vSoftWall.size(); j++)
                {
                    if (CmdObj[i].nId == m_vSoftWall[j].nId)
                    {
                        delete m_vSoftWall[j].pDrawObj;
                        m_vSoftWall.erase(m_vSoftWall.begin()+j);
                        break;
                    }
                }
                break;
            default:
                MessageBox(0,0,_T("删除对象时错误"),0);
                break;
            }
        }
    }
}