#pragma once
class CDGameUIGraphic
{
public:
	CDGameUIGraphic(void);
	~CDGameUIGraphic(void);


	int GetCameraX(void);
	int GetCameraY(void);
	int GetCameraW(void);
	int GetCameraH(void);
	void SetCamera(int x, int y, int w, int h);

	void LoadBMPfile(HBITMAP &hbitmap_s, LPWSTR filename); // for example, LoadBMPfile(GameIndex0, "res\\start\\starting.bmp");
	void FreeBMPHandle(HBITMAP hbitmap_s);
	int GetBMPWidth(HBITMAP hbitmap);
	int GetBMPHeight(HBITMAP hbitmap);

	void DrawBMP(HBITMAP hbitmap_source, int x, int y, COLORREF trans_color, int turnWSign = 0, int turnHSign = 0);
	void DrawBMP(HBITMAP hbitmap_source, int x, int y, int turnWSign = 0, int turnHSign = 0); // 没有透明色 not have transparent color
	void DrawLine(int nXBegin, int nYBegin, int nXEnd, int nYEnd, int nWidth = 2, COLORREF crColor = RGB(100, 100, 100), int nPenStyle = PS_SOLID);
	void DrawTextWM(int nPointSize, LPCTSTR lpszFaceName, COLORREF color, int x, int y, CString text); // for example, DrawText(100, "宋体", RGB(255, 255, 255), 320, 0, "Hello world!");
	void DrawRect(int nX, int nY, int nW, int nH, COLORREF color);
	void DrawPolygon(const POINT* lpPoints, int nCount, COLORREF color);
	void DrawEllipse(int nX, int nY, int nW, int nH, COLORREF color);



	void SetMemDc(CDC * pMemDc);
	CDC* GetCDC(void);
	void SetNullMemDC( void );

public:

	CDC *m_pMemDC;

	int m_cameraX;
	int m_cameraY;
	int m_cameraW;
	int m_cameraH;

};

