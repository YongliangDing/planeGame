#include "StdAfx.h"
#include "plane.h"
#include "resource.h"
plane::plane(void)
: x(450)
, y(450)
{
}

plane::~plane(void)
{
}

void plane::draw(CDC* pDC)
{
	//pDC->Rectangle(x,y,x+100,y+100);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmpDraw;
	bmpDraw.LoadBitmapW(IDB_BITMAP2);
	CBitmap* pbmpOld=memDC.SelectObject(&bmpDraw);
	pDC->TransparentBlt(x,y,50,60,&memDC,0,0,50,60,RGB(0,0,0));
	//pDC->BitBlt(x,y,50,60,&memDC,0,0,SRCCOPY);
}
