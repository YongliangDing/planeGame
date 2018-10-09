#include "stdafx.h"
#include "BG.h"
#include "resource.h"

BG::BG():move(0)
{
}


BG::~BG()
{
}


void BG::Draw(CDC* pBGDC,int s)
{
	move++;
	if (move > 700)
		move = 0;
	CDC memDC;
	memDC.CreateCompatibleDC(pBGDC);
	CBitmap bmpDraw;
    if(s==1)
		bmpDraw.LoadBitmapW(IDB_BITMAP1);
	else if(s==2)
		bmpDraw.LoadBitmapW(IDB_BITMAP2);
	else if(s==3)
		bmpDraw.LoadBitmapW(IDB_BITMAP3);
	CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
	pBGDC->BitBlt(0, move, 512, 768 - move, &memDC, 0, 0, SRCCOPY);
	pBGDC->BitBlt(0, 0, 512, move, &memDC, 0, 768 - move, SRCCOPY);
	
}
