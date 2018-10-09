#pragma once
#include "GameObject.h"

class CBOSSball :public CGameObject
{
public:
	CBOSSball(int x, int y, int nMontion);
	~CBOSSball();

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BOSSball_WIDTH, m_ptPos.y + BOSSball_HEIGHT));
	}
private:
	static const int BOSSball_WIDTH = 40;
	static const int BOSSball_HEIGHT = 53;
	static CImageList m_Images;
	int    m_nMotion;
};


