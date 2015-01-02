#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet(void)
{
    m_nDir = 1;
    m_nType = 3;
    m_nFirePage = 0;

    m_nBoomPage = 0;
    m_isBoom = TRUE;
}


CBullet::~CBullet(void)
{
}

void CBullet::Draw()
{
    if (m_isBoom)
    {
        if (7 == ++m_nBoomPage)
        {
            m_nBoomPage = 0;
        }
        //爆炸火花
        m_pscMem->BitBlt(m_rcXy.left-12,m_rcXy.top-12,m_rcXy.Width()+24,m_rcXy.Height()+24,
            m_pscBoom,66*m_nBoomPage,66,SRCPAINT);

        m_pscMem->BitBlt(m_rcXy.left-12,m_rcXy.top-12,m_rcXy.Width()+24,m_rcXy.Height()+24,
            m_pscBoom,66*m_nBoomPage,0,SRCAND);

        //return;
    }

    m_pscMem->BitBlt(m_rcXy.left,m_rcXy.top,m_rcXy.Width(),m_rcXy.Height(),
        m_pscBullet,40*m_nDir,40,SRCPAINT);

    m_pscMem->BitBlt(m_rcXy.left,m_rcXy.top,m_rcXy.Width(),m_rcXy.Height(),
        m_pscBullet,40*m_nDir,40*(m_nType+1),SRCAND);

    if (0 == m_nFirePage--)
    {
        m_nFirePage = 2;
    }

    CRect rcFire = m_rcXy;
    switch (m_nDir)
    {
    case 0:
        rcFire -= CSize(m_nFirePage%2?m_nFirePage:-m_nFirePage,36-m_nFirePage);
        break;
    case 1:
        rcFire += CSize(36-m_nFirePage,m_nFirePage%2?m_nFirePage:-m_nFirePage);
        break;
    case 2:
        rcFire += CSize(m_nFirePage%2?m_nFirePage:-m_nFirePage,36-m_nFirePage);
        break;
    case 3:
        rcFire -= CSize(36-m_nFirePage,m_nFirePage%2?m_nFirePage:-m_nFirePage);
        break;
    }

    m_pscMem->BitBlt(rcFire.left,rcFire.top,rcFire.Width(),rcFire.Height(),
        m_pscBullet,40*m_nDir,40*9,SRCPAINT);

    m_pscMem->BitBlt(rcFire.left,rcFire.top,rcFire.Width(),rcFire.Height(),
        m_pscBullet,40*m_nDir,40*8,SRCAND);
}

void CBullet::Move(CRect ptMove,int nDir)
{

}


void CBullet::MoveOneStep()
{
	//这里要判定下要移动的坐标是否有效否则取消 待写
	if (!MoveIsValid(m_rcXy,m_nDir))
		return;

	switch (m_nDir)
	{
		//上下左右 2 0 1 3
	case 0:
		//m_rcXy -= CSize(m_nFirePage%2?m_nFirePage:-m_nFirePage,36-m_nFirePage);
		m_rcXy.top -=40;
		m_rcXy.bottom -=40;
		break;
	case 1:
		//m_rcXy += CSize(36-m_nFirePage,m_nFirePage%2?m_nFirePage:-m_nFirePage);
		m_rcXy.left -=40;
		m_rcXy.right -=40;
		break;
	case 2:
		m_rcXy.top +=40;
		m_rcXy.bottom +=40;
		//m_rcXy += CSize(m_nFirePage%2?m_nFirePage:-m_nFirePage,36-m_nFirePage);
		break;
	case 3:
		//m_rcXy -= CSize(36-m_nFirePage,m_nFirePage%2?m_nFirePage:-m_nFirePage);
		m_rcXy.left +=40;
		m_rcXy.right +=40;
		break;
	}
	return;
}

BOOL CBullet::MoveIsValid(CRect ptMove,int nDir)
{
	//上下左右 2 0 1 3
	switch (nDir)
	{
	case 0:
		return (ptMove.bottom+40)>=1200?FALSE:TRUE;
		break;
	case 1:
		return ptMove.left-40<200?FALSE:TRUE;
		break;
	case 2:
		return (ptMove.top-40)<0?FALSE:TRUE;
		break;
	case 3:
		return (ptMove.right+40)>=1200?FALSE:TRUE;
		break;
	}
}