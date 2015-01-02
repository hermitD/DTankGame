#include "stdafx.h"
#include "HardWall.h"


CHardWall::CHardWall(void)
{
}


CHardWall::~CHardWall(void)
{
}

void CHardWall::Draw()
{
    m_pscMem->BitBlt(m_rcXy.left,m_rcXy.top,m_rcXy.Width(),m_rcXy.Height(),
        m_pscHardWall,128,256,SRCCOPY);
}

void CHardWall::Move(CRect ptMove,int nDir)
{

}