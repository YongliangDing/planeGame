#pragma once
#include "Enemy.h"
#include "GameObject.h"
#include "afxwin.h"
class CBOSS :
	public CEnemy
{
public:
	CBOSS();
	~CBOSS();
	BOOL Draw(CDC* pDC, BOOL bPause);
	static BOOL LoadImage();

	CRect GetRect();
	int GetMontion()const;
	BOOL Fired();
private:
	static const int BOSS_WIDTH = 200;
	static const int BOSS_HEIGHT=130;
	static CImageList BOSSm_Images;
	int    BOSSm_nMotion;
	//ͼ������
	int BOSSm_nImagIndex;
	//BOSS�ٶ�
	int BOSSm_V;
	//������ʱ
	int BOSSm_nWait;
};

