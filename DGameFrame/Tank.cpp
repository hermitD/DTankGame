#include "stdafx.h"
#include "Tank.h"


CTank::CTank(void)
{
    m_nPage = 0;
    m_nCannon = 0;
    m_nDir = 2;
    m_nBoomPage = 0;
    m_nTankType = 1;
    m_nFirePage = 0;

    m_isBoom = FALSE;
    m_isFire = TRUE;
}


CTank::~CTank(void)
{
}

void CTank::Draw()
{
    if (m_isMove)
    {
        int nMove = 0;

        m_f10 += 0.1f;

        if (m_f10>=1.0)
        {
            m_f10 = 0.0;
            m_isMove = FALSE;
        }

        nMove = (int)m_f10*m_nMove;

        switch (m_nDir)
        {
        case 0:
            m_rcXy += CSize(0,nMove);
            break;
        case 1:
            m_rcXy += CSize(nMove,0);
            break;
        case 2:
            m_rcXy += CSize(0,nMove);
            break;
        case 3:
            m_rcXy += CSize(nMove,0);
            break;
        }
    }

    if (3 == ++m_nPage)
    {
        m_nPage = 0;
    }

    if (5 == ++m_nCannon)
    {
        m_nCannon = 0;
    }

    if (m_isBoom)
    {
        if (7 == ++m_nBoomPage)
        {
            m_nBoomPage = 0;
        }
        //爆炸火花
        m_pscMem->BitBlt(m_rcXy.left,m_rcXy.top,m_rcXy.Width(),m_rcXy.Height(),
            m_pscBoom,66*m_nBoomPage,66,SRCPAINT);

        m_pscMem->BitBlt(m_rcXy.left,m_rcXy.top,m_rcXy.Width(),m_rcXy.Height(),
            m_pscBoom,66*m_nBoomPage,0,SRCAND);

        return;
    }

    //坦克地盘
    m_pscMem->BitBlt(m_rcXy.left,m_rcXy.top,m_rcXy.Width(),m_rcXy.Height(),
        m_pscTank,64*m_nDir,64*(m_nPage*2+1)+m_nTankType*20*64,SRCPAINT);

    m_pscMem->BitBlt(m_rcXy.left,m_rcXy.top,m_rcXy.Width(),m_rcXy.Height(),
        m_pscTank,64*m_nDir,64*m_nPage*2+m_nTankType*20*64,SRCAND);

    //坦克炮台
    m_pscMem->BitBlt(m_rcXy.left,m_rcXy.top,m_rcXy.Width(),m_rcXy.Height(),
        m_pscTank,64*m_nDir,64*(m_nCannon*2+7)+m_nTankType*20*64,SRCPAINT);

    m_pscMem->BitBlt(m_rcXy.left,m_rcXy.top,m_rcXy.Width(),m_rcXy.Height(),
        m_pscTank,64*m_nDir,64*(m_nCannon*2+6)+m_nTankType*20*64,SRCAND);

    if (m_isFire)
    {
        //发射炮弹火花
        if (8 == m_nFirePage++)
        {
            m_nFirePage = 0;
            m_isFire = FALSE;
        }

        CRect rcFire = m_rcXy;
        switch (m_nDir)
        {
        case 0:
            rcFire += CSize(0,64+m_nFirePage);
            break;
        case 1:
            rcFire -= CSize(64+m_nFirePage,0);
            break;
        case 2:
            rcFire -= CSize(0,64+m_nFirePage);
            break;
        case 3:
            rcFire += CSize(64+m_nFirePage,0);
            break;
        }

		//Copies a bitmap from the source device context to this current device context.

        m_pscMem->BitBlt(rcFire.left,rcFire.top,rcFire.Width(),rcFire.Height(),
            m_pscTank,64*m_nDir,64*19,SRCPAINT);

        m_pscMem->BitBlt(rcFire.left,rcFire.top,rcFire.Width(),rcFire.Height(),
            m_pscTank,64*m_nDir,64*18,SRCAND);
    }
}

void CTank::Move(CRect ptMove,int nDir)
{
	//改变方向移动的时候存在bug

    m_rcXy = m_oldrcXy;
    m_oldrcXy = ptMove;
    m_nDir = nDir;
    m_isMove = TRUE;
    switch (m_nDir)
    {
    case 0:
        m_nMove = ptMove.bottom - m_rcXy.bottom;
        break;
    case 1:
        m_nMove = ptMove.left - m_rcXy.left;
        break;
    case 2:
        m_nMove = ptMove.top - m_rcXy.top;
        break;
    case 3:
        m_nMove = ptMove.right - m_rcXy.right;
        break;
    }
 }

void CTank::Fire()
{
    m_isFire = TRUE;
}