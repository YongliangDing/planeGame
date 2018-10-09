#include "stdafx.h"
#include "BOSS.h"
#include "resource.h"

CImageList CBOSS::BOSSm_Images;
CBOSS::CBOSS()
{
	//随机确定X位置
	m_ptPos.x = rand() % (GAME_WIDTH - BOSS_HEIGHT) + 1;

	//随机确定图像索引
	 BOSSm_nImagIndex = 0;

	//根据图像索引确定方向
	BOSSm_nMotion = 1;
	m_ptPos.y = -BOSS_HEIGHT;

	//随机确定速度
	BOSSm_V = rand() % 3 + 2;

	BOSSm_nWait = 0;
}


CBOSS::~CBOSS()
{
}

int i = 1;
int j = 1;
BOOL CBOSS::Draw(CDC* pDC, BOOL bPause)
{
	BOSSm_nWait ++;
	if (BOSSm_nWait>20)
		BOSSm_nWait = 0;

	if (m_ptPos.y > GAME_HEIGHT + BOSS_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOSS_HEIGHT)
		return FALSE;


	if (m_ptPos.x >= GAME_WIDTH - BOSS_WIDTH )
		m_ptPos.x = GAME_WIDTH - BOSS_WIDTH ;
	if (m_ptPos.x <= 0)
		m_ptPos.x = 0;
	if (m_ptPos.y <= 0)
		m_ptPos.y = 0;

	if (m_ptPos.y >= GAME_HEIGHT - BOSS_HEIGHT)
		m_ptPos.y = GAME_HEIGHT - BOSS_HEIGHT;


if (!bPause)
{
	if (m_ptPos.x == 0)
		i = 1;
	if (m_ptPos.y == 0)
		j = 1;
	if (m_ptPos.x == GAME_WIDTH - BOSS_WIDTH )
		i = -1;
	if (m_ptPos.y == GAME_HEIGHT - BOSS_HEIGHT)
		j = -1;
	m_ptPos.y = m_ptPos.y + BOSSm_nMotion * BOSSm_V*j;
	m_ptPos.x = m_ptPos.x + BOSSm_nMotion * BOSSm_V*i;
			
	}

	BOSSm_Images.Draw(pDC, BOSSm_nImagIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}


BOOL CBOSS::LoadImage()
{
	return CGameObject::LoadImage(BOSSm_Images, IDB_BITMAP8, RGB(0, 0, 0), 200, 130, 1);
}


CRect CBOSS::GetRect()
{
	return CRect(m_ptPos,CPoint(m_ptPos.x+BOSS_WIDTH,m_ptPos.y+BOSS_HEIGHT));
}


int CBOSS::GetMontion()const
{
	return BOSSm_nMotion;
}


BOOL CBOSS::Fired()
{
	if (BOSSm_nWait == 0)
		return TRUE;
	else
		return FALSE;
}
