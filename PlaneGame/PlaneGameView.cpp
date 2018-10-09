// PlaneGameView.cpp : CPlaneGameView 类的实现
//

#include "stdafx.h"
#include "PlaneGame.h"

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"
#include <atlimage.h>
#include "resource.h"
#include "BOSS.h"
#include "LBoss.h"
#include "BOSSball.h"
#include "Lbomb.h"
#include "Bomb1.h"
#include "Ball1.h"
#include "WzdSplash.h"
#include "Phea.h"
#include "lbomb2.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//设置关卡
int level = 1;
//消灭敌机的得分
int score = 0;
//剩余命数
int life = 3;
//剩余生命值
int health = 3;
//BOSS生命值
int bhealth = 100;
int lhealth = 50;
//消灭BOSS数
int mBOSS = 0;
//设置时间
int t = 0;
//特殊导弹
int Lb = 0;
//无敌标志
int flag = 0;
//BOSS出现标志
int bf = 0;
int lb = 0;
int start = 0;
IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CPlaneGameView 构造/析构

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: 在此处添加构造代码
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘制

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CPlaneGameView 打印

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneGameView 诊断

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView 消息处理程序
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//初始化游戏
	InitGame();
}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}
BOOL CPlaneGameView::InitGame()
{
	CRect rc;
	GetClientRect(rc);

	//产生随机数种子
	srand( (unsigned)time( NULL ) );

	//建立设备DC
	m_pDC = new CClientDC(this);

	//建立内存DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//建立内存位图
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//将位图选入内存DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();
	CBOSS::LoadImage();
	CLBoss::LoadImage();
	CBOSSball::LoadImage();
	CLbomb::LoadImage();
	CBomb1::LoadImage();
	CBall1::LoadImage();
	CPhea::LoadImage();
	lbomb2::LoadImage();

	CWzdSplash wndSplash;            //创建启动窗口类的实例  
	wndSplash.Create(IDB_BITMAP15);
	wndSplash.CenterWindow();
	wndSplash.UpdateWindow();       //send WM_PAINT  
	Sleep(2000);
	wndSplash.DestroyWindow();//销毁初始画面窗口 

	//产生主角(战机)
	m_pMe = new CMyPlane;

	//启动游戏
	SetTimer(1,30,NULL);

	return TRUE;
}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	if (start== 0)
	{
		CDC memDC;
		memDC.CreateCompatibleDC(m_pMemDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmapW(IDB_BITMAP16);
		CBitmap*pbmpOld = memDC.SelectObject(&bmpDraw);
		m_pMemDC->TransparentBlt(0, 0, 500, 700, &memDC, 0, 0, 500, 700, RGB(0, 0, 0));
		memDC.SelectObject(pbmpOld);
		if (GetKey(VK_SPACE) == 1)
		{
			RestartGame();
			start = 1;
		}
		
	}

	else
	{
		CPlaneGameDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		/*CDC memDC;
		memDC.CreateCompatibleDC(pMemDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmapW(IDB_BITMAP18);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pMemDC->TransparentBlt(0, 0, 100, 15, &memDC, 0, 0, 100, 15, RGB(0, 0, 0));*/


		if (mBOSS >= 1)
		{
			level = 2;
		}

		if (mBOSS >= 3)
		{
			level = 3;
		}


		//绘制背景
		pDoc->b1.Draw(pMemDC, level);

		if (m_pMe != NULL&&mBOSS<6)
		{
			//显示战机剩余生命数量
			int x = 5;
			int y = 10;
			for (int i = 1; i <= life; i++)
			{
				CDC memDC;
				memDC.CreateCompatibleDC(m_pMemDC);
				CBitmap bmpDraw;
				bmpDraw.LoadBitmapW(IDB_BITMAP9);
				CBitmap*pbmpOld = memDC.SelectObject(&bmpDraw);
				m_pMemDC->TransparentBlt(x, y, 35, 33, &memDC, 0, 0, 35, 33, RGB(0, 0, 0));
				memDC.SelectObject(pbmpOld);
				x += 40;
			}
			CString str1, str2, str3, str4, str5, str6;
			str1 = "得分：";
			str2.Format(_T("%d"), score);
			str3 = "关卡:";
			str4.Format(_T("%d"), level);
			//str5 = "时间：";
			//str6.Format(_T("%d"), t);

			pMemDC->SetBkMode(TRANSPARENT);
			pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetTextColor(RGB(0, 255, 255));
			pMemDC->TextOutW(380, 10, str1);
			pMemDC->TextOutW(430, 10, str2);
			pMemDC->SetTextColor(RGB(255, 0, 255));
			pMemDC->TextOutW(380, 35, str3);
			pMemDC->TextOutW(430, 35, str4);
			//pMemDC->SetTextColor(RGB(255, 0, 255));
			//pMemDC->TextOutW(380, 60, str5);
			//pMemDC->TextOutW(430, 60, str6);
			


			//BOSS血量
			if (bf == 1)
			{
				CBrush bru;
				bru.CreateSolidBrush(RGB(255, 0, 0));
				pMemDC->SelectObject(bru);
				pMemDC->Rectangle(5, 100, 5 + bhealth * 2, 110);
			}
			if (lb == 1)
			{
				CBrush bru2;
				bru2.CreateSolidBrush(RGB(0, 0, 255));
				pMemDC->SelectObject(bru2);
				pMemDC->Rectangle(5, 115, 5 + lhealth * 2, 125);
			}
            //显示战机的生命值
			int x1 = 5;
			int y1 = 50;
			for (int i = 1; i <= health; i++)
			{
				CDC memDC;
				memDC.CreateCompatibleDC(m_pMemDC);
				CBitmap bmpDraw;
				bmpDraw.LoadBitmapW(IDB_BITMAP10);
				CBitmap*pbmpOld = memDC.SelectObject(&bmpDraw);
				m_pMemDC->TransparentBlt(x1, y1, 35, 39, &memDC, 0, 0, 35, 39, RGB(0, 0, 0));
				memDC.SelectObject(pbmpOld);
				x1 += 40;
			}
		}



		//绘制我方战机
		if (m_pMe != NULL&&mBOSS<6)
		{
			m_pMe->Draw(m_pMemDC, FALSE);
		}

		else
		{


			m_ObjList[enEnemy].RemoveAll();
			m_ObjList[enBomb].RemoveAll();
			m_ObjList[enBall].RemoveAll();
			m_ObjList[enExplosion].RemoveAll();
			m_ObjList[enBOSSball].RemoveAll();
			m_ObjList[enBOSS].RemoveAll();
			m_ObjList[enBomb1].RemoveAll();
			m_ObjList[enLbomb].RemoveAll();
			m_ObjList[enBall1].RemoveAll();
			m_ObjList[enLBoss].RemoveAll();
			m_ObjList[enPhea].RemoveAll();
			m_ObjList[enlb].RemoveAll();

			//Game Over
			CString str;
			if (mBOSS >= 6)
			{
				str = _T("游戏通关");
			}
			else
				str = _T("游戏结束");
			CString str99 = _T("     按R键重新开始游戏");
			CString str11, str22;
			str11 = "  最终得分：";
			str22.Format(_T("%d"), score);
			pMemDC->SetBkMode(TRANSPARENT);
			pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetTextColor(RGB(255, 0, 0));
			pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);

			pMemDC->SetTextColor(RGB(0, 255, 255));
			pMemDC->TextOutW(GAME_WIDTH / 2, GAME_HEIGHT / 2 + 25, str11);
			pMemDC->TextOutW(GAME_WIDTH / 2 + 50, GAME_HEIGHT / 2 + 25, str22);

			pMemDC->SetTextColor(RGB(255, 255, 0));
			pMemDC->TextOutW(GAME_WIDTH / 2, GAME_HEIGHT / 2 + 50, str99);
			this->KillTimer(1);
		}

		//绘制 导弹、爆炸、敌机、子弹、BOSS、BOSS子弹
		for (int i = 0; i<12; i++)
		{
			POSITION pos1, pos2;
			for (pos1 = m_ObjList[i].GetHeadPosition(); (pos2 = pos1) != NULL; )
			{
				CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext(pos1);
				if (!pObj->Draw(pMemDC, FALSE))
				{
					m_ObjList[i].RemoveAt(pos2);
					delete pObj;
				}
			}
		}

	}
		

		//复制内存DC到设备DC
		m_pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, m_pMemDC, 0, 0, SRCCOPY);
	
}
void CPlaneGameView::AI()
{


	static int nCreator = rand() % 5 + 5;//敌机
	static int qCreator = rand() % 5 + 500;//特效
	static int lCreator = rand() % 5 + 350;//小BOSS


	//产生boss
	if (t%(1800-level*300)==0&&t!=0)
	{
		m_ObjList[enBOSS].AddTail(new CBOSS);
		bhealth = 100;
		bf = 1;
	}
	

	//随机产生敌机
	if(nCreator<=0)
	{
		nCreator = rand()%5+30-level*5;
		m_ObjList[enEnemy].AddTail(new CEnemy(level-1));
	}
	nCreator--;
	if(m_pMe==NULL)
		return;

	//随机产生小Boss
	if (lCreator <= 0)
	{
		lCreator = rand() % 10 + 800-level*30;
		m_ObjList[enLBoss].AddTail(new CLBoss);
		lhealth = 50;
		lb = 1;
	}
	lCreator--;
	if (m_pMe == NULL)
		return;


	//随机产生特殊炸弹
		if (qCreator <= 0)
		{
			qCreator = rand() % 5 + 200;
			m_ObjList[enLbomb].AddTail(new CLbomb);
			m_ObjList[enPhea].AddTail(new CPhea);
			m_ObjList[enlb].AddTail(new lbomb2);
		}	
	qCreator--;
		if (m_pMe == NULL)
			return;


	//检测四个方向键，移动战机
	for(int i=0;i<4;i++)
	{
		int nMeMotion=0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(VK_UP);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(1);
		    
		nMeMotion = GetKey(VK_DOWN);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(-1);

		nMeMotion = GetKey(VK_RIGHT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(1);

		nMeMotion = GetKey(VK_LEFT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(-1);
	}
	

	//产生战机导弹
	if(GetKey(VK_SPACE)==1)//按下了空格键
	{
		if(m_pMe!=NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			if(Lb==1)
			{
			m_ObjList[enBomb1].AddTail(new CBomb1(pt.x - 10, pt.y + 10));
			m_ObjList[enBomb1].AddTail(new CBomb1(pt.x + 40, pt.y + 10));
			}
			else if(Lb>=2)
			{
				m_ObjList[enBomb1].AddTail(new CBomb1(pt.x - 10, pt.y + 10));
				m_ObjList[enBomb1].AddTail(new CBomb1(pt.x + 15, pt.y + 10));
				m_ObjList[enBomb1].AddTail(new CBomb1(pt.x + 40, pt.y + 10));
			}
			else
		   {
			m_ObjList[enBomb].AddTail(new CBomb(pt.x+15,pt.y+10));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x+40,pt.y+10));
		   }	
		} 
	}



	//敌机发射子弹
	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();

		  BOOL by=FALSE;

		  //敌机在战机前面
		  if(pEnemy->GetMontion()==1 && ePt.y<PlanePt.y)
		         by=  TRUE;
		  //敌机在战机后面
		  if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
				 by=  TRUE;	

		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x+25,ePt.y+10, pEnemy->GetMontion()));
		  }
	}


	//小BOSS发射子弹
	for (POSITION ePostt = m_ObjList[enLBoss].GetHeadPosition(); ePostt != NULL;)
	{
		CLBoss* pLBoss = (CLBoss*)m_ObjList[enLBoss].GetNext(ePostt);
		if (!pLBoss->Fired())
			continue;
		CPoint  ePt = pLBoss->GetPoint();

			m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 40, ePt.y + 37, 1));
			m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 40, ePt.y + 37, 2));
			m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 40, ePt.y + 37, 3));
			m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 40, ePt.y + 37, 4));
			if (level >= 2)
			{
				m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 40, ePt.y + 37, 5));
				m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 40, ePt.y + 37, 6));
				m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 40, ePt.y + 37, 7));
				m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 40, ePt.y + 37, 8));
			}
			
	}

	//BOSS发射子弹
	for (POSITION e1Pos = m_ObjList[enBOSS].GetHeadPosition(); e1Pos != NULL;)
	{
		CBOSS* pBOSS = (CBOSS*)m_ObjList[enBOSS].GetNext(e1Pos);
		if (!pBOSS->Fired())
			continue;
		CPoint  ePt = pBOSS->GetPoint();

		BOOL by = FALSE;

		//敌机在战机前面
		if (pBOSS->GetMontion() == 1 && ePt.y<PlanePt.y)
			by = TRUE;
		//敌机在战机后面
		if (pBOSS->GetMontion() == -1 && ePt.y>PlanePt.y)
			by = TRUE;

		if (by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x + CMyPlane::PLANE_WIDTH)
		{
			m_ObjList[enBOSSball].AddTail(new CBOSSball(ePt.x +10, ePt.y + 10, pBOSS->GetMontion()));
			m_ObjList[enBOSSball].AddTail(new CBOSSball(ePt.x + 85, ePt.y + 10, pBOSS->GetMontion()));
			m_ObjList[enBOSSball].AddTail(new CBOSSball(ePt.x + 160, ePt.y + 10, pBOSS->GetMontion()));
			if (level == 3)
			{
				m_ObjList[enBOSSball].AddTail(new CBOSSball(ePt.x + 47, ePt.y + 10, pBOSS->GetMontion()));
				m_ObjList[enBOSSball].AddTail(new CBOSSball(ePt.x + 123, ePt.y + 10, pBOSS->GetMontion()));
			}
				
		}
	}
	

if (m_pMe != NULL)
{


	//敌机子弹炸掉战机
	POSITION bPos1=NULL,bPos2=NULL;
	CRect mRect = m_pMe->GetRect();
	for(bPos1=m_ObjList[enBall].GetHeadPosition();( bPos2 = bPos1 ) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(&bRect,mRect))
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left,mRect.top)
				);
			
			//删除子弹
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;
			if (flag == 0)
			{
            //生命值削减
			health--;
			//特殊弹消失
			Lb = 0;
			//减命
			if (health == 0 && life > 0)
			{
				life--;
				health = 3;
			}
			//删除战机
			if (life<= 0)
			{
			delete m_pMe;
			m_pMe=NULL;

			}
			}
			
			
			break;
		}
	}


	//BOSS子弹炸掉战机
	POSITION bossPos1 = NULL, bossPos2 = NULL;
	for (bossPos1 = m_ObjList[enBOSSball].GetHeadPosition(); (bossPos2 = bossPos1) != NULL;)
	{
		CBOSSball* pBOSSball = (CBOSSball*)m_ObjList[enBOSSball].GetNext(bossPos1);
		CRect bRect = pBOSSball->GetRect();
		CRect mpRect;
		if (mpRect.IntersectRect(&bRect, mRect))
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);
			//删除子弹
			m_ObjList[enBOSSball].RemoveAt(bossPos2);
			delete pBOSSball;

			if (flag==0)
			{
			//生命值削减
			health-=3;
			//特殊弹消失
			Lb = 0;
			
			//减命
			if (health <= 0 && life > 0)
			{
				life--;
				health = 3;
			}
			//删除战机
			if (life <= 0)
			{
				delete m_pMe;
				m_pMe = NULL;
			}
			}
			
			break;
		}
	}

	//小BOSS子弹炸掉战机
	POSITION lbossPos1 = NULL, lbossPos2 = NULL;
	for (lbossPos1 = m_ObjList[enBall1].GetHeadPosition(); (lbossPos2 = lbossPos1) != NULL;)
	{
		CLBoss* pBOSSball = (CLBoss*)m_ObjList[enBall1].GetNext(lbossPos1);
		CRect bRect = pBOSSball->GetRect();
		CRect mpRect;
		if (mpRect.IntersectRect(&bRect, mRect))
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);
			//删除子弹
			m_ObjList[enBall1].RemoveAt(lbossPos2);
			delete pBOSSball;
			if (flag == 0)
			{
			//生命值削减
			health --;
			//特殊弹消失
			Lb = 0;
			
			//减命
			if (health <= 0 && life > 0)
			{
				life--;
				health = 3;
			}
			//删除战机
			if (life <= 0)
			{
				delete m_pMe;
				m_pMe = NULL;
			}
			}
			
			break;
		}
	}


	//飞机吃特殊导弹
	POSITION qPos1 = NULL, qPos2 = NULL;
	for (qPos1 = m_ObjList[enLbomb].GetHeadPosition(); (qPos2 = qPos1) != NULL;)
	{
		CLbomb* bomb = (CLbomb*)m_ObjList[enLbomb].GetNext(qPos1);
		CRect bRect = bomb->GetRect();
		CRect mpRect;
		if (mpRect.IntersectRect(&bRect, mRect))
		{
			//删除导弹
			m_ObjList[enLbomb].RemoveAt(qPos2);
			delete bomb;
			//子弹改变标志
			Lb++;
			break;
		}
	}

	//飞机吃特殊导弹2
	POSITION pqPos1 = NULL, pqPos2 = NULL;
	for (pqPos1 = m_ObjList[enlb].GetHeadPosition(); (pqPos2 = pqPos1) != NULL;)
	{
		lbomb2* bomb = (lbomb2*)m_ObjList[enlb].GetNext(pqPos1);
		CRect bRect = bomb->GetRect();
		CRect mpRect;
		if (mpRect.IntersectRect(&bRect, mRect))
		{
			//删除导弹
			m_ObjList[enlb].RemoveAt(pqPos2);
			delete bomb;
			

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
				CRect m2Rect = pEnemy->GetRect();
				CRect tmpRect;
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(m2Rect.left, m2Rect.top)
					);

			}

			//子弹效果

			m_ObjList[enEnemy].RemoveAll();
			m_ObjList[enBall].RemoveAll();
			m_ObjList[enBOSSball].RemoveAll();
			m_ObjList[enBall1].RemoveAll();

			score += 50;
			break;
		}
	}


	//飞机吃加血包
	POSITION qhPos1 = NULL, qhPos2 = NULL;
	for (qhPos1 = m_ObjList[enPhea].GetHeadPosition(); (qhPos2 = qhPos1) != NULL;)
	{
		CPhea* bomb = (CPhea*)m_ObjList[enPhea].GetNext(qhPos1);
		CRect bRect = bomb->GetRect();
		CRect mpRect;
		if (mpRect.IntersectRect(&bRect, mRect))
		{
			//删除加血包
			m_ObjList[enPhea].RemoveAt(qhPos2);
			delete bomb;
			//加血
			health++;
			if (health >= 3)
				health = 3;
			break;
		}
	}


		//战机敌机相撞
        POSITION kPos1 = NULL, kPos2 = NULL;
		for (kPos1 = m_ObjList[enEnemy].GetHeadPosition(); (kPos2 = kPos1) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(kPos1);
			CRect bRect = pEnemy->GetRect();
			CRect mpRect;
			if (mpRect.IntersectRect(&bRect, mRect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);

				//删除敌机
				m_ObjList[enEnemy].RemoveAt(kPos2);
				delete pEnemy;
				
				
				//增加得分
				score +=10;

				if (flag == 0)
				{
				//生命值削减
				health--;
				//特殊弹消失
				Lb = 0;
				//减命
				if (health == 0 && life > 0)
				{
					life--;
					health = 3;
				}
				//删除战机
				if (life <= 0)
				{
					delete m_pMe;
					m_pMe = NULL;
				}
				}
				
				break;
			}
		}


		

		//战机BOSS相撞
			POSITION kbPos1 = NULL, kbPos2 = NULL;
			for (kbPos1 = m_ObjList[enBOSS].GetHeadPosition(); (kbPos2 = kbPos1) != NULL;)
			{
				CBOSS* pBOSS = (CBOSS*)m_ObjList[enBOSS].GetNext(kbPos1);
				CRect bbbRect = pBOSS->GetRect();
				CRect tttmpRect;
				if (tttmpRect.IntersectRect(&bbbRect, mRect))
				{
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
					);

					//删除BOSS
						m_ObjList[enBOSS].RemoveAt(kbPos2);
						delete pBOSS;
						score += 500;
						bf = 0;
						mBOSS++;
					//生命值削减
						if (flag == 0)
						{
							health-=3;
							//特殊弹消失
							Lb = 0;
						if (health <= 0 && life > 0)
						{
							life--;
							health = 3;
						}

							//删除战机
						if (life <= 0)
						{
							delete m_pMe;
							m_pMe = NULL;
						}
				        }
					
					break;
				}
			}

			//战机和小BOSS相撞
			POSITION kblPos1 = NULL, kblPos2 = NULL;
			for (kblPos1 = m_ObjList[enLBoss].GetHeadPosition(); (kblPos2 = kblPos1) != NULL;)
			{
				CLBoss* pBOSS = (CLBoss*)m_ObjList[enLBoss].GetNext(kblPos1);
				CRect bbbRect = pBOSS->GetRect();
				CRect tttmpRect;
				if (tttmpRect.IntersectRect(&bbbRect, mRect))
				{
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
					);

					//删除BOSS
					m_ObjList[enLBoss].RemoveAt(kblPos2);
					delete pBOSS;
					score += 200;
					lb = 0;
					if (flag == 0)
					{

					//生命值削减
					health --;
					//特殊弹消失
					Lb = 0;
					if (health <= 0 && life > 0)
					{
						life--;
						health = 3;
					}

					//删除战机
					if (life <= 0)
					{
						delete m_pMe;
						m_pMe = NULL;
					}
					}
				
					break;
				}
			}

	}
		

	

	//战机导弹炸掉敌机
	POSITION mPos1=NULL,mPos2=NULL;
	for(mPos1=m_ObjList[enBomb].GetHeadPosition();(mPos2=mPos1)!=NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1=NULL,ePos2=NULL;
		for(ePos1=m_ObjList[enEnemy].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect m2Rect = pEnemy->GetRect();
			CRect tmpRect;
			if(tmpRect.IntersectRect(&bRect,m2Rect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(m2Rect.left,m2Rect.top)
					);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//删除敌机
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
				score+=10;
				break;

			}
		}
	}
	//战机导弹炸掉BOSS
	POSITION mmmPos1 = NULL, mmmPos2 = NULL;
	for (mmmPos1 = m_ObjList[enBomb].GetHeadPosition(); (mmmPos2 = mmmPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mmmPos1);
		CRect b2Rect = pBomb->GetRect();

		POSITION emPos1 = NULL, emPos2 = NULL;
		for (emPos1 = m_ObjList[enBOSS].GetHeadPosition(); (emPos2 = emPos1) != NULL;)
		{
			CBOSS* pBOSS = (CBOSS*)m_ObjList[enBOSS].GetNext(emPos1);
			CRect m3Rect = pBOSS->GetRect();
			CRect tmpRect1;
			if (tmpRect1.IntersectRect(&b2Rect, m3Rect))
			{
				//造成BOSS伤害
				bhealth--;

				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(b2Rect.left, b2Rect.top)
				);

				//删除导弹
				m_ObjList[enBomb].RemoveAt(mmmPos2);
				delete pBomb;
				
				//删除BOSS
				if (bhealth <= 0)
				{
                m_ObjList[enBOSS].RemoveAt(emPos2);
				delete pBOSS;
				score+=500;
				mBOSS++;
				bf = 0;
				}
				break;

			}
		}
	}


	//战机导弹炸掉小BOSS
	POSITION mmmlPos1 = NULL, mmmlPos2 = NULL;
	for (mmmlPos1 = m_ObjList[enBomb].GetHeadPosition(); (mmmlPos2 = mmmlPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mmmlPos1);
		CRect b2Rect = pBomb->GetRect();

		POSITION emPos1 = NULL, emPos2 = NULL;
		for (emPos1 = m_ObjList[enLBoss].GetHeadPosition(); (emPos2 = emPos1) != NULL;)
		{
			CLBoss* pBOSS = (CLBoss*)m_ObjList[enLBoss].GetNext(emPos1);
			CRect m3Rect = pBOSS->GetRect();
			CRect tmpRect1;
			if (tmpRect1.IntersectRect(&b2Rect, m3Rect))
			{

				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(m3Rect.left, m3Rect.top)
				);
				//造成BOSS伤害
				lhealth--;
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mmmlPos2);
				delete pBomb;


				//删除BOSS
				if (lhealth <= 0)
				{
					m_ObjList[enLBoss].RemoveAt(emPos2);
					delete pBOSS;
					score += 200;
					lb = 0;
				}
				break;

			}
		}
	}



	//战机特殊导弹炸掉敌机
	POSITION mPost1 = NULL, mPost2 = NULL;
	for (mPost1 = m_ObjList[enBomb1].GetHeadPosition(); (mPost2 = mPost1) != NULL;)
	{
		CBomb1* pBomb = (CBomb1*)m_ObjList[enBomb1].GetNext(mPost1);
		CRect bRect = pBomb->GetRect();

		POSITION ePost1 = NULL, ePost2 = NULL;
		for (ePost1 = m_ObjList[enEnemy].GetHeadPosition(); (ePost2 = ePost1) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePost1);
			CRect m2Rect = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, m2Rect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(m2Rect.left, m2Rect.top)
				);
				//删除导弹
				m_ObjList[enBomb1].RemoveAt(mPost2);
				delete pBomb;

				//删除敌机
				m_ObjList[enEnemy].RemoveAt(ePost2);
				delete pEnemy;
				score+=10;
				break;
			}
		}
	}
	//战机特殊导弹炸掉BOSS
	POSITION mmmtPos1 = NULL, mmmtPos2 = NULL;
	for (mmmtPos1 = m_ObjList[enBomb1].GetHeadPosition(); (mmmtPos2 = mmmtPos1) != NULL;)
	{
		CBomb1* pBomb = (CBomb1*)m_ObjList[enBomb1].GetNext(mmmtPos1);
		CRect b2Rect = pBomb->GetRect();

		POSITION emPos1 = NULL, emPos2 = NULL;
		for (emPos1 = m_ObjList[enBOSS].GetHeadPosition(); (emPos2 = emPos1) != NULL;)
		{
			CBOSS* pBOSS = (CBOSS*)m_ObjList[enBOSS].GetNext(emPos1);
			CRect m3Rect = pBOSS->GetRect();
			CRect tmpRect1;
			if (tmpRect1.IntersectRect(&b2Rect, m3Rect))
			{
				//造成BOSS伤害
				bhealth--;

				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(b2Rect.left, b2Rect.top)
				);

				//删除导弹
				m_ObjList[enBomb1].RemoveAt(mmmtPos2);
				delete pBomb;

				//删除BOSS
				if (bhealth <= 0)
				{
					m_ObjList[enBOSS].RemoveAt(emPos2);
					delete pBOSS;
					score += 500;
					mBOSS++;
				}
				break;

			}
		}
	}

	//战机特殊导弹炸掉小BOSS
	POSITION mmmltPos1 = NULL, mmmltPos2 = NULL;
	for (mmmltPos1 = m_ObjList[enBomb1].GetHeadPosition(); (mmmltPos2 = mmmltPos1) != NULL;)
	{
		CBomb1* pBomb = (CBomb1*)m_ObjList[enBomb1].GetNext(mmmltPos1);
		CRect b2Rect = pBomb->GetRect();

		POSITION emPos1 = NULL, emPos2 = NULL;
		for (emPos1 = m_ObjList[enLBoss].GetHeadPosition(); (emPos2 = emPos1) != NULL;)
		{
			CLBoss* pBOSS = (CLBoss*)m_ObjList[enLBoss].GetNext(emPos1);
			CRect m3Rect = pBOSS->GetRect();
			CRect tmpRect1;
			if (tmpRect1.IntersectRect(&b2Rect, m3Rect))
			{
				//造成BOSS伤害
				lhealth--;
				
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(m3Rect.left, m3Rect.top)
				);

				//删除导弹
				m_ObjList[enBomb1].RemoveAt(mmmltPos2);
				delete pBomb;
				if (lhealth <= 0)
				{
					//删除BOSS
					m_ObjList[enLBoss].RemoveAt(emPos2);
					delete pBOSS;
					score += 200;
					lb = 0;
				}
			
				break;

			}
		}
	}
}
void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	//刷新游戏帧画面: 在内存DC上绘图
	UpdateFrame(m_pMemDC);
	AI();
	t++;
	CView::OnTimer(nIDEvent);
}



void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();
	this->StopGame();
	// TODO: 在此处添加消息处理程序代码

}

void CPlaneGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	switch (nChar)
	{
	case 'P':
		this->KillTimer(1); break;
	case 'C':
		SetTimer(1, 30, NULL); break;
	case 'R':
		RestartGame(); break;
	case 'W':
		flag = 1; break;
	case 'Q':
		flag = 0; break;

	}

}

void CPlaneGameView::RestartGame()
{
	m_ObjList[enEnemy].RemoveAll();
	m_ObjList[enBomb].RemoveAll();
	m_ObjList[enBall].RemoveAll();
	m_ObjList[enExplosion].RemoveAll();
	m_ObjList[enBOSSball].RemoveAll();
	m_ObjList[enBOSS].RemoveAll();
	m_ObjList[enBomb1].RemoveAll();
	m_ObjList[enLbomb].RemoveAll();
	m_ObjList[enBall1].RemoveAll();
	m_ObjList[enLBoss].RemoveAll();
	m_ObjList[enPhea].RemoveAll();
	m_ObjList[enlb].RemoveAll();

	//产生主角(战机)
	m_pMe = new CMyPlane;
	m_pMe->Draw(m_pMemDC, TRUE);
	//清零
	//设置关卡
	 level = 1;
	//消灭敌机的得分
	 score = 0;
	//剩余命数
	 life = 3;
	//剩余生命值
	 health = 3;
	//BOSS生命值
	 bhealth = 100;
	lhealth = 50;
	//消灭BOSS数
	 mBOSS = 0;
	//设置时间
	 t = 0;
	//特殊导弹
	 Lb = 0;
	 bf = 0;
	 lb = 0;
	 flag = 0;
	//启动游戏
	
	SetTimer(1, 30, NULL);
}
