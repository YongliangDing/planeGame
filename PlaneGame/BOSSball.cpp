#include "StdAfx.h"
#include "BOSSball.h"
#include "resource.h"

CImageList CBOSSball::m_Images;

CBOSSball::CBOSSball(int x, int y, int nMontion) :CGameObject(x, y), m_nMotion(nMontion)
{

}

CBOSSball::~CBOSSball()
{
}
BOOL CBOSSball::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * 8;
	}

	if (m_ptPos.y > GAME_HEIGHT + BOSSball_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOSSball_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CBOSSball::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP7, RGB(0, 0, 0), 40, 53, 1);
}