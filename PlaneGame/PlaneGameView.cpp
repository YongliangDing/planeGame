// PlaneGameView.cpp : CPlaneGameView ���ʵ��
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
//���ùؿ�
int level = 1;
//����л��ĵ÷�
int score = 0;
//ʣ������
int life = 3;
//ʣ������ֵ
int health = 3;
//BOSS����ֵ
int bhealth = 100;
int lhealth = 50;
//����BOSS��
int mBOSS = 0;
//����ʱ��
int t = 0;
//���⵼��
int Lb = 0;
//�޵б�־
int flag = 0;
//BOSS���ֱ�־
int bf = 0;
int lb = 0;
int start = 0;
IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CPlaneGameView ����/����

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: �ڴ˴���ӹ������
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPlaneGameView ��ӡ

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
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

	//�������������
	srand( (unsigned)time( NULL ) );

	//�����豸DC
	m_pDC = new CClientDC(this);

	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
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

	CWzdSplash wndSplash;            //���������������ʵ��  
	wndSplash.Create(IDB_BITMAP15);
	wndSplash.CenterWindow();
	wndSplash.UpdateWindow();       //send WM_PAINT  
	Sleep(2000);
	wndSplash.DestroyWindow();//���ٳ�ʼ���洰�� 

	//��������(ս��)
	m_pMe = new CMyPlane;

	//������Ϸ
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


		//���Ʊ���
		pDoc->b1.Draw(pMemDC, level);

		if (m_pMe != NULL&&mBOSS<6)
		{
			//��ʾս��ʣ����������
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
			str1 = "�÷֣�";
			str2.Format(_T("%d"), score);
			str3 = "�ؿ�:";
			str4.Format(_T("%d"), level);
			//str5 = "ʱ�䣺";
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
			


			//BOSSѪ��
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
            //��ʾս��������ֵ
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



		//�����ҷ�ս��
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
				str = _T("��Ϸͨ��");
			}
			else
				str = _T("��Ϸ����");
			CString str99 = _T("     ��R�����¿�ʼ��Ϸ");
			CString str11, str22;
			str11 = "  ���յ÷֣�";
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

		//���� ��������ը���л����ӵ���BOSS��BOSS�ӵ�
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
		

		//�����ڴ�DC���豸DC
		m_pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, m_pMemDC, 0, 0, SRCCOPY);
	
}
void CPlaneGameView::AI()
{


	static int nCreator = rand() % 5 + 5;//�л�
	static int qCreator = rand() % 5 + 500;//��Ч
	static int lCreator = rand() % 5 + 350;//СBOSS


	//����boss
	if (t%(1800-level*300)==0&&t!=0)
	{
		m_ObjList[enBOSS].AddTail(new CBOSS);
		bhealth = 100;
		bf = 1;
	}
	

	//��������л�
	if(nCreator<=0)
	{
		nCreator = rand()%5+30-level*5;
		m_ObjList[enEnemy].AddTail(new CEnemy(level-1));
	}
	nCreator--;
	if(m_pMe==NULL)
		return;

	//�������СBoss
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


	//�����������ը��
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


	//����ĸ���������ƶ�ս��
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
	

	//����ս������
	if(GetKey(VK_SPACE)==1)//�����˿ո��
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



	//�л������ӵ�
	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();

		  BOOL by=FALSE;

		  //�л���ս��ǰ��
		  if(pEnemy->GetMontion()==1 && ePt.y<PlanePt.y)
		         by=  TRUE;
		  //�л���ս������
		  if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
				 by=  TRUE;	

		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x+25,ePt.y+10, pEnemy->GetMontion()));
		  }
	}


	//СBOSS�����ӵ�
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

	//BOSS�����ӵ�
	for (POSITION e1Pos = m_ObjList[enBOSS].GetHeadPosition(); e1Pos != NULL;)
	{
		CBOSS* pBOSS = (CBOSS*)m_ObjList[enBOSS].GetNext(e1Pos);
		if (!pBOSS->Fired())
			continue;
		CPoint  ePt = pBOSS->GetPoint();

		BOOL by = FALSE;

		//�л���ս��ǰ��
		if (pBOSS->GetMontion() == 1 && ePt.y<PlanePt.y)
			by = TRUE;
		//�л���ս������
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


	//�л��ӵ�ը��ս��
	POSITION bPos1=NULL,bPos2=NULL;
	CRect mRect = m_pMe->GetRect();
	for(bPos1=m_ObjList[enBall].GetHeadPosition();( bPos2 = bPos1 ) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(&bRect,mRect))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left,mRect.top)
				);
			
			//ɾ���ӵ�
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;
			if (flag == 0)
			{
            //����ֵ����
			health--;
			//���ⵯ��ʧ
			Lb = 0;
			//����
			if (health == 0 && life > 0)
			{
				life--;
				health = 3;
			}
			//ɾ��ս��
			if (life<= 0)
			{
			delete m_pMe;
			m_pMe=NULL;

			}
			}
			
			
			break;
		}
	}


	//BOSS�ӵ�ը��ս��
	POSITION bossPos1 = NULL, bossPos2 = NULL;
	for (bossPos1 = m_ObjList[enBOSSball].GetHeadPosition(); (bossPos2 = bossPos1) != NULL;)
	{
		CBOSSball* pBOSSball = (CBOSSball*)m_ObjList[enBOSSball].GetNext(bossPos1);
		CRect bRect = pBOSSball->GetRect();
		CRect mpRect;
		if (mpRect.IntersectRect(&bRect, mRect))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);
			//ɾ���ӵ�
			m_ObjList[enBOSSball].RemoveAt(bossPos2);
			delete pBOSSball;

			if (flag==0)
			{
			//����ֵ����
			health-=3;
			//���ⵯ��ʧ
			Lb = 0;
			
			//����
			if (health <= 0 && life > 0)
			{
				life--;
				health = 3;
			}
			//ɾ��ս��
			if (life <= 0)
			{
				delete m_pMe;
				m_pMe = NULL;
			}
			}
			
			break;
		}
	}

	//СBOSS�ӵ�ը��ս��
	POSITION lbossPos1 = NULL, lbossPos2 = NULL;
	for (lbossPos1 = m_ObjList[enBall1].GetHeadPosition(); (lbossPos2 = lbossPos1) != NULL;)
	{
		CLBoss* pBOSSball = (CLBoss*)m_ObjList[enBall1].GetNext(lbossPos1);
		CRect bRect = pBOSSball->GetRect();
		CRect mpRect;
		if (mpRect.IntersectRect(&bRect, mRect))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);
			//ɾ���ӵ�
			m_ObjList[enBall1].RemoveAt(lbossPos2);
			delete pBOSSball;
			if (flag == 0)
			{
			//����ֵ����
			health --;
			//���ⵯ��ʧ
			Lb = 0;
			
			//����
			if (health <= 0 && life > 0)
			{
				life--;
				health = 3;
			}
			//ɾ��ս��
			if (life <= 0)
			{
				delete m_pMe;
				m_pMe = NULL;
			}
			}
			
			break;
		}
	}


	//�ɻ������⵼��
	POSITION qPos1 = NULL, qPos2 = NULL;
	for (qPos1 = m_ObjList[enLbomb].GetHeadPosition(); (qPos2 = qPos1) != NULL;)
	{
		CLbomb* bomb = (CLbomb*)m_ObjList[enLbomb].GetNext(qPos1);
		CRect bRect = bomb->GetRect();
		CRect mpRect;
		if (mpRect.IntersectRect(&bRect, mRect))
		{
			//ɾ������
			m_ObjList[enLbomb].RemoveAt(qPos2);
			delete bomb;
			//�ӵ��ı��־
			Lb++;
			break;
		}
	}

	//�ɻ������⵼��2
	POSITION pqPos1 = NULL, pqPos2 = NULL;
	for (pqPos1 = m_ObjList[enlb].GetHeadPosition(); (pqPos2 = pqPos1) != NULL;)
	{
		lbomb2* bomb = (lbomb2*)m_ObjList[enlb].GetNext(pqPos1);
		CRect bRect = bomb->GetRect();
		CRect mpRect;
		if (mpRect.IntersectRect(&bRect, mRect))
		{
			//ɾ������
			m_ObjList[enlb].RemoveAt(pqPos2);
			delete bomb;
			

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
				CRect m2Rect = pEnemy->GetRect();
				CRect tmpRect;
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(m2Rect.left, m2Rect.top)
					);

			}

			//�ӵ�Ч��

			m_ObjList[enEnemy].RemoveAll();
			m_ObjList[enBall].RemoveAll();
			m_ObjList[enBOSSball].RemoveAll();
			m_ObjList[enBall1].RemoveAll();

			score += 50;
			break;
		}
	}


	//�ɻ��Լ�Ѫ��
	POSITION qhPos1 = NULL, qhPos2 = NULL;
	for (qhPos1 = m_ObjList[enPhea].GetHeadPosition(); (qhPos2 = qhPos1) != NULL;)
	{
		CPhea* bomb = (CPhea*)m_ObjList[enPhea].GetNext(qhPos1);
		CRect bRect = bomb->GetRect();
		CRect mpRect;
		if (mpRect.IntersectRect(&bRect, mRect))
		{
			//ɾ����Ѫ��
			m_ObjList[enPhea].RemoveAt(qhPos2);
			delete bomb;
			//��Ѫ
			health++;
			if (health >= 3)
				health = 3;
			break;
		}
	}


		//ս���л���ײ
        POSITION kPos1 = NULL, kPos2 = NULL;
		for (kPos1 = m_ObjList[enEnemy].GetHeadPosition(); (kPos2 = kPos1) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(kPos1);
			CRect bRect = pEnemy->GetRect();
			CRect mpRect;
			if (mpRect.IntersectRect(&bRect, mRect))
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);

				//ɾ���л�
				m_ObjList[enEnemy].RemoveAt(kPos2);
				delete pEnemy;
				
				
				//���ӵ÷�
				score +=10;

				if (flag == 0)
				{
				//����ֵ����
				health--;
				//���ⵯ��ʧ
				Lb = 0;
				//����
				if (health == 0 && life > 0)
				{
					life--;
					health = 3;
				}
				//ɾ��ս��
				if (life <= 0)
				{
					delete m_pMe;
					m_pMe = NULL;
				}
				}
				
				break;
			}
		}


		

		//ս��BOSS��ײ
			POSITION kbPos1 = NULL, kbPos2 = NULL;
			for (kbPos1 = m_ObjList[enBOSS].GetHeadPosition(); (kbPos2 = kbPos1) != NULL;)
			{
				CBOSS* pBOSS = (CBOSS*)m_ObjList[enBOSS].GetNext(kbPos1);
				CRect bbbRect = pBOSS->GetRect();
				CRect tttmpRect;
				if (tttmpRect.IntersectRect(&bbbRect, mRect))
				{
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
					);

					//ɾ��BOSS
						m_ObjList[enBOSS].RemoveAt(kbPos2);
						delete pBOSS;
						score += 500;
						bf = 0;
						mBOSS++;
					//����ֵ����
						if (flag == 0)
						{
							health-=3;
							//���ⵯ��ʧ
							Lb = 0;
						if (health <= 0 && life > 0)
						{
							life--;
							health = 3;
						}

							//ɾ��ս��
						if (life <= 0)
						{
							delete m_pMe;
							m_pMe = NULL;
						}
				        }
					
					break;
				}
			}

			//ս����СBOSS��ײ
			POSITION kblPos1 = NULL, kblPos2 = NULL;
			for (kblPos1 = m_ObjList[enLBoss].GetHeadPosition(); (kblPos2 = kblPos1) != NULL;)
			{
				CLBoss* pBOSS = (CLBoss*)m_ObjList[enLBoss].GetNext(kblPos1);
				CRect bbbRect = pBOSS->GetRect();
				CRect tttmpRect;
				if (tttmpRect.IntersectRect(&bbbRect, mRect))
				{
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
					);

					//ɾ��BOSS
					m_ObjList[enLBoss].RemoveAt(kblPos2);
					delete pBOSS;
					score += 200;
					lb = 0;
					if (flag == 0)
					{

					//����ֵ����
					health --;
					//���ⵯ��ʧ
					Lb = 0;
					if (health <= 0 && life > 0)
					{
						life--;
						health = 3;
					}

					//ɾ��ս��
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
		

	

	//ս������ը���л�
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
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(m2Rect.left,m2Rect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//ɾ���л�
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
				score+=10;
				break;

			}
		}
	}
	//ս������ը��BOSS
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
				//���BOSS�˺�
				bhealth--;

				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(b2Rect.left, b2Rect.top)
				);

				//ɾ������
				m_ObjList[enBomb].RemoveAt(mmmPos2);
				delete pBomb;
				
				//ɾ��BOSS
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


	//ս������ը��СBOSS
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

				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(m3Rect.left, m3Rect.top)
				);
				//���BOSS�˺�
				lhealth--;
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mmmlPos2);
				delete pBomb;


				//ɾ��BOSS
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



	//ս�����⵼��ը���л�
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
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(m2Rect.left, m2Rect.top)
				);
				//ɾ������
				m_ObjList[enBomb1].RemoveAt(mPost2);
				delete pBomb;

				//ɾ���л�
				m_ObjList[enEnemy].RemoveAt(ePost2);
				delete pEnemy;
				score+=10;
				break;
			}
		}
	}
	//ս�����⵼��ը��BOSS
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
				//���BOSS�˺�
				bhealth--;

				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(b2Rect.left, b2Rect.top)
				);

				//ɾ������
				m_ObjList[enBomb1].RemoveAt(mmmtPos2);
				delete pBomb;

				//ɾ��BOSS
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

	//ս�����⵼��ը��СBOSS
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
				//���BOSS�˺�
				lhealth--;
				
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(m3Rect.left, m3Rect.top)
				);

				//ɾ������
				m_ObjList[enBomb1].RemoveAt(mmmltPos2);
				delete pBomb;
				if (lhealth <= 0)
				{
					//ɾ��BOSS
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
	//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
	UpdateFrame(m_pMemDC);
	AI();
	t++;
	CView::OnTimer(nIDEvent);
}



void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();
	this->StopGame();
	// TODO: �ڴ˴������Ϣ����������

}

void CPlaneGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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

	//��������(ս��)
	m_pMe = new CMyPlane;
	m_pMe->Draw(m_pMemDC, TRUE);
	//����
	//���ùؿ�
	 level = 1;
	//����л��ĵ÷�
	 score = 0;
	//ʣ������
	 life = 3;
	//ʣ������ֵ
	 health = 3;
	//BOSS����ֵ
	 bhealth = 100;
	lhealth = 50;
	//����BOSS��
	 mBOSS = 0;
	//����ʱ��
	 t = 0;
	//���⵼��
	 Lb = 0;
	 bf = 0;
	 lb = 0;
	 flag = 0;
	//������Ϸ
	
	SetTimer(1, 30, NULL);
}
