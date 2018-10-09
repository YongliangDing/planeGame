#pragma once
#include "stdafx.h"
#include "GameObject.h"

class CLbomb :
	public CGameObject
{
public:
	CLbomb(void);
	~CLbomb(void);
private:

	static const int LB_HEIGHT = 47;
	static const int LB_WIDTH = 60;
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
