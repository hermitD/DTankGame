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

	//��static��Ա�⣬ÿ�������඼�����˻����һ������������������
	//���ܷ��ʵ� private��Ա��static�������̳в���ֻ��һ������������Ը�������Աһ����

    static CDC *m_pscMem;
    static CDC *m_pscView;

    static CDC *m_pscBullet;
    static CDC *m_pscGrass;
    static CDC *m_pscHardWall;
    static CDC *m_pscSoftWall;
	static CDC *m_pscTank;

    static CDC *m_pscBoom;
};

