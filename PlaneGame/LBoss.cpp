#include "stdafx.h"
#include "LBoss.h"
#include "resource.h"

CImageList CLBoss::BOSSm_Images;
CLBoss::CLBoss()
{
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - BOSS_HEIGHT) + 1;

	//���ȷ��ͼ������
	BOSSm_nImagIndex = 0;

	//����ͼ������ȷ������
	BOSSm_nMotion = 1;
	m_ptPos.y = -BOSS_HEIGHT;

	//���ȷ���ٶ�
	BOSSm_V = rand() % 3 + 2;

	BOSSm_nWait = 0;
}


CLBoss::~CLBoss()
{
}

int ii = 1;
int jj = 1;
BOOL CLBoss::Draw(CDC* pDC, BOOL bPause)
{
	BOSSm_nWait++;
	if (BOSSm_nWait>20)
		BOSSm_nWait = 0;

	if (m_ptPos.y > GAME_HEIGHT + BOSS_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOSS_HEIGHT)
		return FALSE;


	if (m_ptPos.x >= GAME_WIDTH - BOSS_WIDTH)
		m_ptPos.x = GAME_WIDTH - BOSS_WIDTH;
	if (m_ptPos.x <= 0)
		m_ptPos.x = 0;
	if (m_ptPos.y <= 0)
		m_ptPos.y = 0;

	if (m_ptPos.y >= GAME_HEIGHT - BOSS_HEIGHT)
		m_ptPos.y = GAME_HEIGHT - BOSS_HEIGHT;


	if (!bPause)
	{
		if (m_ptPos.x == 0)
			ii = 1;
		if (m_ptPos.y == 0)
			jj = 1;
		if (m_ptPos.x == GAME_WIDTH - BOSS_WIDTH)
			ii = -1;
		if (m_ptPos.y == GAME_HEIGHT - BOSS_HEIGHT)
			jj = -1;
		m_ptPos.y = m_ptPos.y + BOSSm_nMotion * BOSSm_V*jj;
		m_ptPos.x = m_ptPos.x + BOSSm_nMotion * BOSSm_V*ii;

	}

	BOSSm_Images.Draw(pDC, BOSSm_nImagIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}


BOOL CLBoss::LoadImage()
{
	return CGameObject::LoadImage(BOSSm_Images, IDB_BITMAP14, RGB(0, 0, 0), 100, 75, 1);
}


CRect CLBoss::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + BOSS_WIDTH, m_ptPos.y + BOSS_HEIGHT));
}


int CLBoss::GetMontion()const
{
	return BOSSm_nMotion;
}


BOOL CLBoss::Fired()
{
	if (BOSSm_nWait == 0)
		return TRUE;
	else
		return FALSE;
}
