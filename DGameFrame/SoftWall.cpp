#include "stdafx.h"
#include "SoftWall.h"


CSoftWall::CSoftWall(void)
{
    m_nLife = 1;
    m_nPage = 0;
}


CSoftWall::~CSoftWall(void)
{
}

void CSoftWall::Draw()
{
    if (2 == m_nLife)
    {
        m_pscMem->BitBlt(m_rcXy.left,m_rcXy.top,m_rcXy.Width(),m_rcXy.Height(),
            m_pscSoftWall,64,64,SRCPAINT);

        m_pscMem->BitBlt(m_rcXy.left,m_rcXy.top,m_rcXy.Width(),m_rcXy.Height(),
            m_pscSoftWall,64,0,SRCAND);
    }
    else if(1 == m_nLife)
    {
        m_pscMem->BitBlt(m_rcXy.left,m_rcXy.top,m_rcXy.Width(),m_rcXy.Height(),
            m_pscSoftWall,64*m_nPage,64*3,SRCPAINT);

        m_pscMem->BitBlt(m_rcXy.left,m_rcXy.top,m_rcXy.Width(),m_rcXy.Height(),
            m_pscSoftWall,64*m_nPage,64*2,SRCAND);

        if (2 == m_nPage++)
        {
            m_nPage = 0;
        }
    }
}

void CSoftWall::Move(CRect ptMove,int nDir)
{

}