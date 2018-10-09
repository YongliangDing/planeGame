#include "StdAfx.h"
#include "Bomb1.h"
#include "resource.h"


CImageList CBomb1::m_Images;


CBomb1::CBomb1(int x, int y) :CGameObject(x, y)
{

}

CBomb1::~CBomb1()
{
}
BOOL CBomb1::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP11, RGB(0, 0, 0), 23, 29, 1);
}
BOOL CBomb1::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y - 16;
	}

	if (m_ptPos.y < -BOMB1_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}