#pragma once
#include "GameObject.h"
class lbomb2 :
	public CGameObject
{
public:
	lbomb2(void);
	~lbomb2(void);
private:

	static const int LB_HEIGHT = 38;
	static const int LB_WIDTH = 40;
	static CImageList m_Images;
	int m_nImgIndex;
	int m_V;
	int m_nWait;
	int m_nMotion;
public:
	BOOL Draw(CDC* pDC, BOOL bPause);
	static BOOL LoadImage();
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + LB_WIDTH, m_ptPos.y + LB_HEIGHT));
	}
	int GetMontion()const
	{

		return m_nMotion;
	}
};

