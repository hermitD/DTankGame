#pragma once
#include "DrawObj.h"

class CBullet : public CDrawObj
{
public:
    CBullet(void);
    ~CBullet(void);

    virtual void Draw();
    virtual void Move(CRect ptMove,int nDir);
	virtual void MoveOneStep();
	virtual BOOL MoveIsValid(CRect ptMove,int nDir);

    int m_nDir;
    int m_nType;
    int m_nFirePage;

    int m_nBoomPage;
    BOOL m_isBoom;
};

