#pragma once
#include "GameObject.h"

class CBomb :
	public CGameObject
{
public:
	CBomb(int x,int y);
	~CBomb(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+ BOMB_WIDTH,m_ptPos.y+BOMB_HEIGHT));
	}
private:
	static const int BOMB_WIDTH = 10;
	static const int BOMB_HEIGHT = 25;
	static CImageList m_Images;

};
