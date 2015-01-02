#include "stdafx.h"
#include "DrawObj.h"
CDC *CDrawObj::m_pscMem = nullptr; 
CDC *CDrawObj::m_pscView = nullptr; 
CDC *CDrawObj::m_pscBullet = nullptr; 
CDC *CDrawObj::m_pscGrass = nullptr; 
CDC *CDrawObj::m_pscHardWall = nullptr; 
CDC *CDrawObj::m_pscSoftWall = nullptr; 
CDC *CDrawObj::m_pscTank = nullptr; 
CDC *CDrawObj::m_pscBoom = nullptr;

CDrawObj::CDrawObj(void)
{
    m_nMove = 0;
    m_f10 = 0.0f;
    m_isMove = FALSE;
}


CDrawObj::~CDrawObj(void)
{
}

CPoint CDrawObj::GetPt()
{
    return m_rcXy.CenterPoint();
}