#pragma once
#include "DrawObj.h"

class CSoftWall : public CDrawObj
{
public:
    CSoftWall(void);
    ~CSoftWall(void);
    
    virtual void Draw();
    virtual void Move(CRect ptMove,int nDir);

    int m_nLife;
    int m_nPage;
};

