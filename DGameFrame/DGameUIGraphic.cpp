#include "stdafx.h"
#include "DGameUIGraphic.h"


CDGameUIGraphic::CDGameUIGraphic(void)
{

	m_pMemDC = NULL;


	m_cameraX = 0;
	m_cameraY = 0;
	m_cameraW = GAME_SCREEN_W;
	m_cameraH = GAME_SCREEN_H;

}


CDGameUIGraphic::~CDGameUIGraphic(void)
{
	m_pMemDC = NULL;

}

int CDGameUIGraphic::GetCameraX( void )
{
	return m_cameraX;
}

int CDGameUIGraphic::GetCameraY( void )
{
	return m_cameraY;
}

int CDGameUIGraphic::GetCameraW( void )
{
	return  m_cameraW;//GAME_SCREEN_W;
}

int CDGameUIGraphic::GetCameraH( void )
{
	return m_cameraH;
}



void CDGameUIGraphic::DrawLine( int nXBegin, int nYBegin, int nXEnd, int nYEnd, int nWidth /*= 2*/, COLORREF crColor /*= RGB(100, 100, 100)*/, int nPenStyle /*= PS_SOLID*/ )
{
	if (m_pMemDC != NULL)
	{
		CPen pen;
		pen.CreatePen(nPenStyle, nWidth, crColor);
		CPen *pOldpen = NULL;
		pOldpen = m_pMemDC->SelectObject(&pen);
		// begin draw
		m_pMemDC->MoveTo(nXBegin, nYBegin);
		m_pMemDC->LineTo(nXEnd, nYEnd);
		// end draw
		m_pMemDC->SelectObject(pOldpen);
		pOldpen = NULL;
		pen.DeleteObject();
	}
}

void CDGameUIGraphic::LoadBMPfile( HBITMAP &hbitmap_s, LPWSTR filename )
{
	hbitmap_s = (HBITMAP)LoadImage(NULL, filename,
		/*MAKEINTRESOURCE(IDB_BITMAP),*/IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CDGameUIGraphic::FreeBMPHandle( HBITMAP hbitmap_s )
{
	DeleteObject(hbitmap_s);
}

void CDGameUIGraphic::DrawBMP( HBITMAP hbitmap_source, int x, int y, COLORREF trans_color, int turnWSign /*= 0*/, int turnHSign /*= 0*/ )
{
	if (m_pMemDC != NULL)
	{
		CDC memDC_unit; // ����һ���豸��������豸�л���unit��Ȼ���Ƶ���Ϊ�ڶ�������豸MemDC��
		CDC memDC_black; // ����豸���ڴ�memDC_unitת����λͼ
		HBITMAP	hbmpTrans, holdbmpTrans; // holdbmpTrans=(HBITMAP)SelectObject(memDC_black,   hbmpTrans);
		HBITMAP	phOldbmp = NULL; // phOldbmp=(HBITMAP)memDC_unit.SelectObject(hbitmap_source);
		COLORREF oldbkcolor, oldmembkcolor;
		COLORREF oldtextcolor, oldmemtextcolor;
		BITMAP bitmap_source;
		int width = 0, height = 0;
		int turnWSignTemp = 1;
		int turnHSignTemp = 1;

		if (turnWSign != 0)
		{
			turnWSign = 1;
			turnWSignTemp = -1;
		}
		if (turnHSign != 0)
		{
			turnHSign = 1;
			turnHSignTemp = -1;
		}

		memDC_unit.CreateCompatibleDC(m_pMemDC); // ʹ��memDC_bmp��memDC_second����
		memDC_black.CreateCompatibleDC(m_pMemDC); //

		GetObject((HGDIOBJ)hbitmap_source, sizeof(bitmap_source), &bitmap_source); //bitmap_source.bmWidth,bitmap_source.bmHeight

		width = bitmap_source.bmWidth;
		height = bitmap_source.bmHeight;

		//------
		//-- �����ɫͼƬ
		phOldbmp = (HBITMAP)memDC_unit.SelectObject(hbitmap_source);

		/*
		���һ����ɫλͼ���ɫλͼת������ô��ɫλͼΪ1�Ĳ��֣�Ҳ���ǰ�ɫ���֣�����ת��Ϊ��ɫλͼ�ı���ɫ��
		��ɫλͼΪ0�Ĳ��֣���ɫ���֣�����ת��Ϊ��ɫλͼ�ı���ɫ�����һ����ɫλͼ��ɫλͼת����
		��ô��ɫλͼ�ı���ɫת������ɫλͼ����Ϊ1(��ɫ)����������ת��Ϊ0����ɫ����
		*/
		// �����ڰ�ͼƬ//����ɫͼƬת���ɺڰ�ͼƬ //�Ժ����ʹ��TransparentBlt()ʵ��͸��ɫ�����ҿ���ָ�����͸��ɫ���������ô�ͳ�ķ�����ָ��͸��ɫʵ�������Ƚ�͸��ɫ��ɺ�ɫȻ������������
		hbmpTrans = CreateBitmap(width, height, 1, 1, NULL); 
		if   (hbmpTrans == NULL) 
		{
			MessageBox(NULL, _T("����ͼƬʧ��!"), _T("Sorry"), MB_OK | MB_ICONWARNING);
			exit(0);
		}
		holdbmpTrans = (HBITMAP)SelectObject(memDC_black, hbmpTrans); 
		oldbkcolor = SetBkColor(memDC_unit, trans_color); //����ɫ
		oldtextcolor = SetTextColor(memDC_unit, RGB(255, 255, 255)); // ǰ��ɫ
		BitBlt(memDC_black, 0, 0, width, height, memDC_unit, 0, 0, SRCCOPY);
		//------

		oldmembkcolor = SetBkColor(*m_pMemDC, RGB(255, 255, 255)); // ����ɫ
		oldmemtextcolor = SetTextColor(*m_pMemDC, RGB(0, 0, 0)); // ǰ��ɫ 
		//-- ��ʼ����
		// ��ɫͼ �������
		m_pMemDC->StretchBlt((int)(x + width * turnWSign),
			(int)(y + height * turnHSign),
			(int)(width * turnWSignTemp),(int)(height * turnHSignTemp),
			&memDC_unit, 0, 0,
			width, height,
			SRCINVERT);			
		// �ڰ�ͼ ������
		m_pMemDC->StretchBlt((int)(x + width * turnWSign),
			(int)(y + height * turnHSign),
			(int)(width * turnWSignTemp),(int)(height * turnHSignTemp),
			&memDC_black, 0, 0,
			width, height,
			SRCAND);
		m_pMemDC->StretchBlt((int)(x + width * turnWSign),
			(int)(y + height * turnHSign),
			(int)(width * turnWSignTemp),(int)(height * turnHSignTemp),
			&memDC_unit, 0, 0,
			width, height,
			SRCINVERT);	
		//--end ��ʼ����

		//-- ���ü���й����
		SetBkColor(memDC_unit, oldbkcolor); 
		SetTextColor(memDC_unit, oldtextcolor);

		SetBkColor(*m_pMemDC, oldmembkcolor); 
		SetTextColor(*m_pMemDC, oldmemtextcolor);

		memDC_black.SelectObject(holdbmpTrans);
		memDC_black.DeleteDC();
		DeleteObject(hbmpTrans);

		memDC_unit.SelectObject(phOldbmp);
		memDC_unit.DeleteDC();
	}
}

void CDGameUIGraphic::DrawBMP( HBITMAP hbitmap_source, int x, int y, int turnWSign /*= 0*/, int turnHSign /*= 0*/ )
{
	if (m_pMemDC != NULL)
	{
		CDC memDC_unit;//--����һ���豸��������豸�л���unit��Ȼ���Ƶ���Ϊ�ڶ�������豸MemDC��
		HBITMAP	phOldbmp = NULL;// phOldbmp = (HBITMAP)memDC_unit.SelectObject(hbitmap_source);
		BITMAP bitmap_source;
		int width = 0, height = 0;

		int turnWSignTemp = 1;
		int turnHSignTemp = 1;

		if (turnWSign != 0)
		{
			turnWSign = 1;
			turnWSignTemp = -1;
		}
		if (turnHSign != 0)
		{
			turnHSign = 1;
			turnHSignTemp = -1;
		}

		memDC_unit.CreateCompatibleDC(m_pMemDC); // ʹ��memDC_bmp��memDC_second����

		GetObject((HGDIOBJ)hbitmap_source, sizeof(bitmap_source), &bitmap_source); // bitmap_source.bmWidth,bitmap_source.bmHeight

		width = bitmap_source.bmWidth;
		height = bitmap_source.bmHeight;

		//------
		//-- �����ɫͼƬ
		phOldbmp = (HBITMAP)memDC_unit.SelectObject(hbitmap_source);

		//-- ��ʼ����			
		// ��ɫͼ
		m_pMemDC->StretchBlt((int)(x + width * turnWSign),
			(int)(y + height * turnHSign),
			(int)(width * turnWSignTemp),(int)(height * turnHSignTemp),
			&memDC_unit, 0, 0,
			width, height,
			SRCCOPY);
		//--end ��ʼ����

		//--���ü���й����
		memDC_unit.SelectObject(phOldbmp);
		memDC_unit.DeleteDC();
	}
}

void CDGameUIGraphic::DrawTextWM( int nPointSize, LPCTSTR lpszFaceName, COLORREF color, int x, int y, CString text )
{
	if (m_pMemDC != NULL)
	{
		m_pMemDC->SetBkMode(TRANSPARENT); // ȥ����ɫ
		CFont Font;
		CFont *pOldFont = NULL;
		Font.CreatePointFont(nPointSize, lpszFaceName, m_pMemDC); // �Ժ�������������ʾҪ����߿�����CreateFont���� // nPointSizeΪ�����С
		pOldFont = m_pMemDC->SelectObject(&Font);
		m_pMemDC->SetTextColor(color);
		m_pMemDC->TextOut(x, y, text);
		m_pMemDC->SetTextColor(RGB(0, 0, 0)); // ����ֻ��Ϊ�������ı���ɫ
		m_pMemDC->SetBkMode(OPAQUE); // �ָ���ɫ
		m_pMemDC->SelectObject(pOldFont);
		Font.DeleteObject();
		pOldFont = NULL;
	}
}

void CDGameUIGraphic::DrawRect( int nX, int nY, int nW, int nH, COLORREF color )
{
	if (m_pMemDC != NULL)
	{
		CPen pen;
		CPen* pOldPen = NULL;
		CBrush brush;
		CBrush* pOldBrush = NULL;

		pen.CreatePen(PS_SOLID, 1, color);
		pOldPen = m_pMemDC->SelectObject(&pen);
		brush.CreateSolidBrush(color);
		pOldBrush = m_pMemDC->SelectObject(&brush);
		m_pMemDC->Rectangle(nX, nY, nX + nW, nY + nH);
		m_pMemDC->SelectObject(pOldPen);
		m_pMemDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		pen.DeleteObject();
		pOldPen = NULL;
		pOldBrush = NULL;
	}
}

void CDGameUIGraphic::DrawPolygon(const POINT* lpPoints, int nCount, COLORREF color)
{
	if (m_pMemDC != NULL)
	{
		CPen pen;
		CPen* pOldPen = NULL;
		CBrush brush;
		CBrush* pOldBrush = NULL;

		pen.CreatePen(PS_SOLID, 1, color);
		pOldPen = m_pMemDC->SelectObject(&pen);
		brush.CreateSolidBrush(color);
		pOldBrush = m_pMemDC->SelectObject(&brush);
		m_pMemDC->Polygon(lpPoints, nCount);
		m_pMemDC->SelectObject(pOldPen);
		m_pMemDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		pen.DeleteObject();
		pOldPen = NULL;
		pOldBrush = NULL;
	}
}

void CDGameUIGraphic::DrawEllipse( int nX, int nY, int nW, int nH, COLORREF color )
{
	if (m_pMemDC != NULL)
	{
		CPen pen;
		CPen* pOldPen = NULL;
		CBrush brush;
		CBrush* pOldBrush = NULL;

		pen.CreatePen(PS_SOLID, 1, color);
		pOldPen = m_pMemDC->SelectObject(&pen);
		brush.CreateSolidBrush(color);
		pOldBrush = m_pMemDC->SelectObject(&brush);
		m_pMemDC->Ellipse(nX, nY, nX + nW, nY + nH);
		m_pMemDC->SelectObject(pOldPen);
		m_pMemDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		pen.DeleteObject();
		pOldPen = NULL;
		pOldBrush = NULL;
	}
}



void CDGameUIGraphic::SetCamera( int x, int y, int w, int h )
{
	m_cameraX = x;
	m_cameraY = y;
	if (w > MAX_SCREEN_W)
	{
		w = MAX_SCREEN_W;
	}
	else if (w <= 0)
	{
		w = 1;
	}
	if (h > MAX_SCREEN_H)
	{
		h = MAX_SCREEN_H;
	}
	else if (h <= 0)
	{
		h = 1;
	}
	m_cameraW = w;
	m_cameraH = h;
}

int CDGameUIGraphic::GetBMPWidth( HBITMAP hbitmap )
{
	BITMAP bitmap_source;

	GetObject((HGDIOBJ)hbitmap, sizeof(bitmap_source), &bitmap_source); // bitmap_source.bmWidth,bitmap_source.bmHeight
	return bitmap_source.bmWidth;
}

int CDGameUIGraphic::GetBMPHeight( HBITMAP hbitmap )
{
	BITMAP bitmap_source;

	GetObject((HGDIOBJ)hbitmap, sizeof(bitmap_source), &bitmap_source); // bitmap_source.bmWidth,bitmap_source.bmHeight
	return bitmap_source.bmHeight;
}





CDC* CDGameUIGraphic::GetCDC( void )
{
	return m_pMemDC;
}


void CDGameUIGraphic::SetMemDc(CDC * pMemDc)
{
	m_pMemDC = pMemDc;
}

void CDGameUIGraphic::SetNullMemDC( void )
{
	m_pMemDC = NULL;
}



