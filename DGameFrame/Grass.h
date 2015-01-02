#pragma once
#include "DrawObj.h"

class CGrass : public CDrawObj
{
public:
    CGrass(void);
    ~CGrass(void);
    
    virtual void Draw();    
    virtual void Move(CRect ptMove,int nDir);
};

