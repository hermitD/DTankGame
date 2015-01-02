#pragma once
#include "DrawObj.h"

class CHardWall : public CDrawObj
{
public:
    CHardWall(void);
    ~CHardWall(void);
    
    virtual void Draw();
    virtual void Move(CRect ptMove,int nDir);
};

