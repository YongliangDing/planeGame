#include "stdafx.h"
#include "Phea.h"
#include "resource.h"

CImageList CPhea::m_Images;
CPhea::CPhea()
{
	//随机确定X位置
	m_ptPos.x = rand() % (GAME_WIDTH - H_WIDTH) + 1;

	//随机确定图像索引
	m_nImgIndex = rand() % 2;

	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = -H_HEIGHT;
	if (m_nImgIndex % 2 != 0)//如果是图像索引是偶数
	{
		m_nMotion = 1;
		m_ptPos.y = GAME_HEIGHT + H_HEIGHT;
	}
	//随机确定速度
	m_V = rand() % 6 + 3;

	m_nWait = 0;
}


CPhea::~CPhea()
{
}


BOOL CPhea::LoadImage(void)
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP17, RGB(0, 0, 0), 40, 35, 1);
}

BOOL CPhea::Draw(CDC* pDC, BOOL bPause)
{


	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + H_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -H_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}


