#include "stdafx.h"
#include "Phea.h"
#include "resource.h"

CImageList CPhea::m_Images;
CPhea::CPhea()
{
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - H_WIDTH) + 1;

	//���ȷ��ͼ������
	m_nImgIndex = rand() % 2;

	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -H_HEIGHT;
	if (m_nImgIndex % 2 != 0)//�����ͼ��������ż��
	{
		m_nMotion = 1;
		m_ptPos.y = GAME_HEIGHT + H_HEIGHT;
	}
	//���ȷ���ٶ�
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


