#pragma once
#include "DrawObj.h"

class CTank : public CDrawObj
{
public:
    CTank(void);
    ~CTank(void);

    virtual void Draw();
    virtual void Move(CRect ptMove,int nDir);
    void Fire();

    int m_nPage;
    int m_nCannon;
    int m_nDir;
    int m_nTankType;

    int m_nBoomPage;
    BOOL m_isBoom;

    int m_nFirePage;
    BOOL m_isFire;
};

