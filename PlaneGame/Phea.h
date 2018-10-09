#pragma once
#include "stdafx.h"
#include "GameObject.h"
class CPhea :
	public CGameObject
{
public:
	CPhea(void);
	~CPhea(void);
	BOOL Draw(CDC* pDC, BOOL bPause);
	static BOOL LoadImage();
	CRect GetRect()
	{

		return CRect(m_ptPos, CPoint(m_ptPos.x + H_WIDTH, m_ptPos.y + H_HEIGHT));

	}
	int GetMontion()const
	{

		return m_nMotion;

	}

private:
	static const int H_WIDTH = 40;
	static const int H_HEIGHT = 35;
	static CImageList m_Images;
	int m_nImgIndex;
	int m_V;
	int m_nWait;
	int m_nMotion;

};
