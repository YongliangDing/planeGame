#pragma once
#include "Enemy.h"
#include "GameObject.h"
#include "afxwin.h"
class CLBoss :
	public CEnemy
{
public:
	CLBoss();
	~CLBoss();
	BOOL Draw(CDC* pDC, BOOL bPause);
	static BOOL LoadImage();

	CRect GetRect();
	int GetMontion()const;
	BOOL Fired();
private:
	static const int BOSS_WIDTH = 100;
	static const int BOSS_HEIGHT = 75;
	static CImageList BOSSm_Images;
	int    BOSSm_nMotion;
	//图像索引
	int BOSSm_nImagIndex;
	//BOSS速度
	int BOSSm_V;
	//发射延时
	int BOSSm_nWait;
};

