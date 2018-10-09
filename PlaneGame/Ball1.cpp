#include "StdAfx.h"
#include "Ball1.h"
#include "resource.h"

CImageList CBall1::m_Images;

CBall1::CBall1(int x, int y, int nMontion) :CGameObject(x, y), m_nMotion(nMontion)
{

}

CBall1::~CBall1()
{
}
BOOL CBall1::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		switch (m_nMotion)
		{
		case 1:
			m_ptPos.x = m_ptPos.x + 8;
			m_ptPos.y = m_ptPos.y + 8;
			break;
		case 2:
			m_ptPos.x = m_ptPos.x + 8;
			m_ptPos.y = m_ptPos.y - 8;
			break;
		case 3:
			m_ptPos.x = m_ptPos.x - 8;
			m_ptPos.y = m_ptPos.y + 8;
			break;
		case 4:
			m_ptPos.x = m_ptPos.x - 8;
			m_ptPos.y = m_ptPos.y - 8;
			break;
		case 5:
			m_ptPos.x = m_ptPos.x + 8;
			break;
		case 6:
			m_ptPos.y = m_ptPos.y - 8;
			break;
		case 7:
			m_ptPos.x = m_ptPos.x - 8;
			break;
		case 8:
			m_ptPos.y = m_ptPos.y + 8;
			break;
		}
	}

	if (m_ptPos.y > GAME_HEIGHT + BALL_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BALL_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CBall1::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP13, RGB(0, 0, 0),29 , 29, 1);
}