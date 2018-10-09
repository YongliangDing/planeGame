#include "stdafx.h"
#include "lbomb2.h"
#include "resource.h"
CImageList lbomb2::m_Images;

lbomb2::lbomb2(void)

{

	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - LB_WIDTH) + 1;

	//���ȷ��ͼ������
	m_nImgIndex = rand() % 2;

	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -LB_HEIGHT;
	if (m_nImgIndex % 2 != 0)//�����ͼ��������ż��
	{
		m_nMotion = 1;
		m_ptPos.y = GAME_HEIGHT + LB_HEIGHT;
	}
	//���ȷ���ٶ�
	m_V = rand() % 6 + 3;

	m_nWait = 0;

}

lbomb2::~lbomb2(void)
{
}

BOOL lbomb2::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + LB_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -LB_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL lbomb2::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP19, RGB(0, 0, 0), 40, 38, 1);
}

