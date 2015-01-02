#pragma once
class CDrawObj
{
public:
    CDrawObj(void);
    ~CDrawObj(void);

    virtual void Draw() = 0;
    virtual void Move(CRect ptMove,int nDir){};
    CPoint GetPt();

public:
    CRect  m_rcXy;
    CRect  m_oldrcXy;

    BOOL   m_isMove;
    int    m_nMove;
    float  m_f10;

	//除static成员外，每个派生类都保存了基类的一个副本，包括派生类
	//不能访问的 private成员；static在整个继承层中只有一个，其访问属性跟其他成员一样。

    static CDC *m_pscMem;
    static CDC *m_pscView;

    static CDC *m_pscBullet;
    static CDC *m_pscGrass;
    static CDC *m_pscHardWall;
    static CDC *m_pscSoftWall;
	static CDC *m_pscTank;

    static CDC *m_pscBoom;
};

