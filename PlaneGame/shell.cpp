#include "StdAfx.h"
#include "shell.h"
#include"resource.h"
shell::shell(void)
: x(0)
, y(0)
{
}

shell::~shell(void)
{
}

void shell::draw(CDC* pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmpDraw;
	bmpDraw.LoadBitmapW(IDB_BITMAP1);
	CBitmap* pbmpOld=memDC.SelectObject(&bmpDraw);
	pDC->TransparentBlt(x,y,10,20,&memDC,0,0,10,20,RGB(0,0,0));
}
