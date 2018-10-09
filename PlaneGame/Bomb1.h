#pragma once
#include "GameObject.h"

class CBomb1 :
	public CGameObject
{
public:
	CBomb1(int x, int y);
	~CBomb1(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BOMB1_WIDTH, m_ptPos.y + BOMB1_HEIGHT));
	}
private:
	static const int BOMB1_WIDTH = 23;
	static const int BOMB1_HEIGHT = 29;
	static CImageList m_Images;

};
