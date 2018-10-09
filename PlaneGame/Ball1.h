#pragma once
#include "GameObject.h"

class CBall1 :public CGameObject
{
public:
	CBall1(int x, int y, int nMontion);
	~CBall1();

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BALL_HEIGHT, m_ptPos.y + BALL_HEIGHT));
	}
private:
	static const int BALL_HEIGHT = 29;
	static CImageList m_Images;
	int    m_nMotion;
};